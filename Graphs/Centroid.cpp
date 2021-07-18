#include <iostream>
#include <vector>
using namespace std;

namespace Centroid {
  vector<vector<int>> G;
  vector<vector<int>> CTree;
  vector<int> parCTree, deep, sz;
  vector<bool> gone;
  int n;

  void getSize(int v, int p) {
    sz[v] = 1;
    for (int u: G[v]) if (u != p && !gone[u]) {
      getSize(u, v);
      sz[v] += sz[u];
    }
  }

  int getCentroid(int v, int p, int tot) {
    for (int u: G[v]) if (u != p && !gone[u])
      if (sz[u] > tot / 2)
        return getCentroid(u, v, tot);
    return v;
  }

  void recBuild(int v, int d) {
    deep[v] = d;
    for (int u: G[v]) if (!gone[u]) {
      getSize(u, v);
      int newRoot = getCentroid(u, v, sz[u]);
      CTree[v].push_back(newRoot);
      parCTree[newRoot] = v;
      gone[newRoot] = true;
      recBuild(newRoot, d + 1);
    }
  }

  void buildCTree() {
    gone.assign(n, false);
    sz.resize(n);
    CTree.resize(n);
    deep.resize(n);
    parCTree.resize(n);
    getSize(0, 0);
    int root = getCentroid(0, 0, n);
    gone[root] = true;
    parCTree[root] = root;
    recBuild(root, 0);
  }
}
