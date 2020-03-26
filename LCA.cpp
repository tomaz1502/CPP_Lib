#include <iostream>
#include <vector>
using namespace std;

const int N = 1e5 + 10;
vector<int> G[N];

struct LCA {
    int tam, t, lg;
    vector< vector< int > > lift;
    vector< int > disc, fin, dep;

    void dfs(int v, int p, int d = 0) {
        dep[v] = d;
        disc[v] = t++;
        for(int u : G[v]) {
            if(u == p) continue;
            dfs(u, v, d + 1);
            lift[u][0] = v;
        }
        fin[v] = t++;
    }

    LCA(int tam_, int lg_ = 20, int root = 0) {
        tam = tam_; lg = lg_;
        t = 0;
        lift = vector< vector< int > >(tam, vector<int>(lg));
        disc = fin = dep = vector< int >(tam);

        dfs(root,-1);
        lift[root][0] = root;

        for(int i = 1; i < lg; ++i) {
            for(int v = 0; v < tam; ++v) {
                lift[v][i] = lift[lift[v][i-1]][i-1];
            }
        }
    }

    int dist(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u,v)];
    }

    bool isAncestor(int u, int v) { return disc[u] < disc[v] and fin[u] > fin[v]; }

    int lca(int u, int v) {
        if(u == v) return u;

        if(isAncestor(u,v)) return u;
        if(isAncestor(v,u)) return v;

        for(int x = lg - 1; x >= 0; x--) {
            if(!isAncestor(lift[u][x], v)) {
                u = lift[u][x];
            }
        }
        return lift[u][0];
    }

};

int main() {

    int n; cin >> n;

    for(int i = 0; i<n-1; i++) {
        int u, v; cin >> u >> v; --u; --v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    LCA L(n);

    int q; cin >> q;
    while(q--) {
        int u, v; cin >> u >> v; u--; v--;
        cout << L.lca(u,v) + 1 << '\n';
    }

    return 0;
}
