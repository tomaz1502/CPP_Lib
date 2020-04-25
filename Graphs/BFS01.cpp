#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
const int inf = 1e8;

vector<pair<int, int>> G[N];

int bfs01(int s, int t) {

    vector<bool> seen(N, false);

    deque<pair<int, int>> q;
    q.emplace_back(s,0);

    int ans = inf;

    while(!q.empty()) {
        pair<int, int> at = q.front(); q.pop_front();
        int v, dep;
        tie(v, dep) = at;
        
        if(v == t) {
            ans = min(ans, dep);
            continue;
        }

        seen[v] = true;

        for(auto [u, w] : G[v]) {
            if(!seen[u]) {
                seen[u] = true;
                if(w == 1) q.emplace_back(u, dep + 1);
                else q.emplace_front(u, dep);
            }
        }

    }

    return ans;
}

int main() {

    int n, m; cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }

    int s, t; cin >> s >> t;

    cout << bfs01(s, t);

    return 0;
}
