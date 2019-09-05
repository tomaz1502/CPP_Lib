#include <iostream>
#include <vector>
using namespace std;

struct LCA_DS {
    int tam, t, lg;
    vector< vector< int > > G, lift;
    vector< int > disc, fin;

    void dfs(int v, int p) {
        disc[v] = t++;
        for(int u : G[v]) {
            if(u == p) continue;
            dfs(u,v);
            lift[u][0] = v;
        }
        fin[v] = t++;
    }

    LCA_DS(const vector< vector< int > > &G_, int lg_ = 20, int root = 0) {
        G = G_;
        tam = G.size(); lg = lg_;
        t = 0;
        lift = vector< vector< int > >(tam, vector<int>(lg));
        disc = fin = vector< int >(tam);

        dfs(root,-1);
        lift[root][0] = root;

        for(int i = 1; i < lg; ++i) {
            for(int v = 0; v < tam; ++v) {
                lift[v][i] = lift[lift[v][i-1]][i-1];
            }
        }
    }

    bool isAncestor(int u, int v) { return disc[u] < disc[v] and fin[u] > fin[v]; }

    int lca(int u, int v) {
        
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
    vector< vector< int > > G(n);
    
    for(int i = 0; i<n-1; i++) {
        int u, v; cin >> u >> v; --u; --v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    LCA_DS L(G);

    int q; cin >> q;
    while(q--) {
        int u, v; cin >> u >> v; u--; v--;
        cout << L.lca(u,v) + 1 << '\n';  
    }



    return 0;
}
