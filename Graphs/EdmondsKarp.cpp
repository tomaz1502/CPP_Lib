#include <bits/stdc++.h>
using namespace std;

using ll = long long;

class EdmondsKarp {
  int V, s, t;

  struct edge {
    int id, c, f;

    edge(int id_, int c_, int f_) : id(id_), c(c_), f(f_) {}
  };

  struct resEdge {
    int id, c;
    bool real;

    resEdge(int id_, int c_, bool real_) : id(id_), c(c_), real(real_) {}
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
        parent[v].real = P.real;
        q.push(v);
      }
    }

    if (!achei)
      return {};

    vector<resEdge> path;
    int v = t;
    while (v != s) {
      path.emplace_back(v, parent[v].c, parent[v].real);
      v = parent[v].id;
    }

    reverse(path.begin(), path.end());
    return path;
  }

  void rebuildRes() {
    R.clear();
    R.resize(V);

    for (int i = 0; i < V; i++) {
      for (const auto& v : G[i]) {
        if (v.c - v.f)
          R[i].push_back(resEdge(v.id, v.c - v.f, true));
        if (v.f)
          R[v.id].push_back(resEdge(i, v.f, false));
      }
    }
  }

public:
  int computeFlow() {
    int r = 0;
    for (const auto& e : G[s])
      r += e.f;
    return r;
  }

  void printRes() {
    for (int i = 0; i < V; i++) {
      cout << i << ": \n";
      for (const auto& er : R[i]) {
        cout << "  adj: " << er.id << "  capacity: " << er.c << '\n';
      }
    }
    cout << "\n\n\n";
  }

  EdmondsKarp(const vector<vector<pair<int, int>>> &H, int s_, int t_) : V(H.size()), s(s_), t(t_) {
    G.resize(V);
    for (int i = 0; i < V; i++) {
      for (auto P : H[i]) {
        int u = P.first, w = P.second;
        G[i].emplace_back(u, w, 0);
      }
    }

    while (true) {
      rebuildRes();
      auto path = bfs();
      if (path.empty())
        break;

      int flow = INT_MAX;
      for (const auto& e : path)
        flow = min(flow, e.c);

      int v = s;
      for (const auto& u : path) {
        for (int i = 0; i < (int) G[v].size(); i++) {
          if (G[v][i].id == u.id) {
            if (u.real)
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
  cin.tie(nullptr);

  vector<vector<pair<int, int>>> G;
  int n, m;
  cin >> n >> m;
  G.resize(n);
  for (int i = 0; i < m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    u--; v--;
    G[u].emplace_back(v, w);
    G[v].emplace_back(u, w);
  }

  EdmondsKarp EK(G, 0, n - 1);
  cout << EK.computeFlow() << '\n';
  return 0;
}
