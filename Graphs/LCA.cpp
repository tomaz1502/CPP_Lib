#include <iostream>
#include <vector>
using namespace std;


namespace LCA {
    const int N = 1e5 + 10;

    int sz, t, lg;
    vector<vector<int>> lift;
    vector<int> Lv, Rv, dep;
    vector<int> G[N];

    void dfs(int v, int p, int d = 0) {
        dep[v] = d;
        Lv[v] = t++;
        for (int u : G[v]) if (u != p) {
            dfs(u, v, d + 1);
            lift[u][0] = v;
        }
        Rv[v] = t++;
    }

    void build(int sz_, int lg_ = 20, int root = 0) {
        sz = sz_; lg = lg_;
        t = 0;
        lift = vector< vector< int > >(sz, vector<int>(lg));
        Lv = Rv = dep = vector< int >(sz);

        dfs(root,-1);
        lift[root][0] = root;

        for (int i = 1; i < lg; ++i) {
            for (int v = 0; v < sz; ++v) {
                lift[v][i] = lift[lift[v][i-1]][i-1];
            }
        }
    }

    bool isAncestor(int u, int v) { return Lv[u] <= Lv[v] and Rv[u] >= Rv[v]; }

    int lca(int u, int v) {
        if(u == v) return u;

        if (isAncestor(u,v)) return u;
        if (isAncestor(v,u)) return v;

        for (int x = lg - 1; x >= 0; x--) {
            if(!isAncestor(lift[u][x], v)) {
                u = lift[u][x];
            }
        }
        return lift[u][0];
    }

    int dist(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u,v)];
    }
};

int main() {

    int n; cin >> n;

    for(int i = 0; i<n-1; i++) {
        int u, v; cin >> u >> v; --u; --v;
        LCA::G[u].push_back(v);
        LCA::G[v].push_back(u);
    }

    LCA::build(n);

    int q; cin >> q;
    while(q--) {
        int u, v; cin >> u >> v; u--; v--;
        cout << LCA::lca(u,v) + 1 << '\n';
    }

    return 0;
}
