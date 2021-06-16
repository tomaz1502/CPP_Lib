#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class EdmondsKarp {
public:
  int V, s, t;

  struct edge {
    int id, c, f;

    edge(int id_, int c_, int f_) : id(id_), c(c_), f(f_) {}
  };

  struct resEdge {
    int id, c;
    bool good;

    resEdge(int id_, int c_, bool good_) : id(id_), c(c_), good(good_) {}
  };

  vector<vector<edge>> G;
  vector<vector<resEdge>> R;

  vector<resEdge> bfs() {

    queue<int> q;
    vector<resEdge> parent(V, resEdge(-1, -1, false));
    bool achei = false;

    q.push(s);

    while (!q.empty()) {
      int at = q.front();
      q.pop();
      if (at == t) {
        achei = true;
        break;
      }

      for (auto P : R[at]) {
        int v = P.id, w = P.c;
        if (parent[v].id != -1)
          continue;

        parent[v].id = at;
        parent[v].c = w;
        parent[v].good = P.good;
        q.push(v);
      }
    }

    if (!achei)
      return vector<resEdge>();

    vector<resEdge> path;
    int v = t;
    while (v != s) {

      path.push_back(resEdge(v, parent[v].c, parent[v].good));
      v = parent[v].id;
    }

    reverse(path.begin(), path.end());

    return path;
  }

  void rebuildRes() {
    R.clear();
    R.resize(V);

    for (int i = 0; i < G.size(); i++) {

      for (edge v : G[i]) {
        if (v.c - v.f)
          R[i].push_back(resEdge(v.id, v.c - v.f, true));
        if (v.f)
          R[v.id].push_back(resEdge(i, v.f, false));
      }
    }
  }

  int computeFlow() {
    int r = 0;
    for (edge e : G[s])
      r += e.f;
    return r;
  }

  void printRes() {

    for (int i = 0; i < V; i++) {
      cout << i << ": \n";
      for (resEdge er : R[i]) {
        cout << "adj: " << er.id << "  capacity: " << er.c << '\n';
      }
    }
    cout << "\n\n\n";
  }

  EdmondsKarp(const vector<vector<pair<int, int>>> &H, int s_, int t_) {

    V = H.size();
    s = s_;
    t = t_;

    for (int i = 0; i < V; i++) {
      G.push_back(vector<edge>());
      for (auto P : H[i]) {
        int u = P.first, w = P.second;
        G[i].push_back(edge(u, w, 0));
      }
    }

    while (1) {
      rebuildRes();
      // printRes();
      // break;

      vector<resEdge> path = bfs();
      if (path.empty())
        break;

      int flow = 1e8;
      for (resEdge e : path)
        flow = min(flow, e.c);

      int v = s;
      for (resEdge u : path) {
        for (int i = 0; i < G[v].size(); i++) {
          if (G[v][i].id == u.id) {
            if (u.good)
              G[v][i].f += flow;
            else
              G[v][i].f -= flow;
            break;
          }
        }

        v = u.id;
      }
    }
  }
};

int main() {
  ios::sync_with_stdio(false);

  vector<vector<pair<int, int>>> G;
  int n, m;
  cin >> n >> m;
  G.resize(n);
  for (int i = 0; i < m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    u--;
    v--;
    G[u].push_back({v, w});
    G[v].push_back({u, w});
  }

  EdmondsKarp EK(G, 0, n - 1);
  cout << EK.computeFlow() << '\n';
  return 0;
}
