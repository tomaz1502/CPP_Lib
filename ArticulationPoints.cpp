#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;


vector<int> G[N];
vector< pair<int, int> > bridges;
vector<int> low, disc, artc;

int tempo = 1;
int root = 0;

int n, m;

void dfs(int v, int p) {

    int sons = 0;
    bool any = false;
    disc[v] = tempo++;
    low[v] = disc[v];

    for(int u : G[v]) {
        if(!disc[u]) {
            dfs(u, v);

            if(low[u] > disc[v]) bridges.emplace_back(u,v);
            if(low[u] >= disc[v]) any = true;
            low[v] = min(low[v], low[u]);

            sons++;
        }
        else if(u != p) {
            low[v] = min(low[v], disc[u]);
        }
    }

    if(sons >= 2 and v == root) artc.push_back(v);
    else if(v != root and any) artc.push_back(v);

}   

int main() {
    ios::sync_with_stdio(false);

    cin >> n >> m;

    low.assign(n, 0);
    disc.assign(n, 0);

    for(int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        --u; --v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    dfs(root, -1);

    return 0;
}
