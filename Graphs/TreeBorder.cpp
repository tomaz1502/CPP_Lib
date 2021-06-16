#include <vector>
using namespace std;

// calculate the maximum distance for a path starting in each one of the
// vertices complexity: O(n) time and space

void calc_depths(int v, int p, vector<int> &dep, vector<vector<int>> &G,
                 int d = 0) {
  dep[v] = d;
  for (const auto &u : G[v])
    if (u != p) {
      calc_depths(u, v, dep, G, d + 1);
      dep[v] = max(dep[v], dep[u] + 1);
    }
}

void calc_border_dist(int v, int p, vector<int> &d, vector<int> &dep,
                      vector<vector<int>> &G, int par_ans = 0) {
  d[v] = max(dep[v], par_ans);
  int m1 = -1, m2 = -1;
  int m1_id;
  for (int u : G[v])
    if (u != p) {
      if (dep[u] + 1 >= m1) {
        m1_id = u;
        m2 = m1;
        m1 = dep[u] + 1;
      } else if (dep[u] + 1 > m2) {
        m2 = dep[u] + 1;
      }
    }
  for (int u : G[v])
    if (u != p) {
      if (u == m1_id)
        calc_border_dist(u, v, d, dep, G, max(par_ans + 1, 1 + m2));
      else
        calc_border_dist(u, v, d, dep, G, max(par_ans + 1, m1 + 1));
    }
}
