#include <vector>
#include <queue>

using namespace std;

const int inf = 1e9;
const int N = 2e5 + 10;

vector<pair<int,int>> G[N];
int n;

vector<int> sssp(int v)
{
  priority_queue<pair<int,int>> pq;
  pq.emplace(0,v);
  vector<int> dist(n, inf);
  dist[v] = 0;

  while (!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    d = -d;
    if (dist[u] < d)
      continue;
    for (auto [u2, w]: G[u]) {
      if (dist[u2] > d + w) {
        pq.emplace(-d-w, u2);
        dist[u2] = d + w;
      }
    }
  }
  return dist;
}
