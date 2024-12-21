#include <vector>
#include <queue>

using namespace std;
using ll = long long;

const ll inf = 1e18;

const ll N = 2e5 + 10;
vector<pair<ll,ll>> G[N];
int n;

vector<ll> sssp(ll v)
{
  priority_queue<pair<ll,ll>> pq;
  pq.emplace(0,v);
  vector<ll> dist(n, inf);
  dist[v] = 0;

  while (!pq.empty()) {
    auto t = pq.top(); pq.pop();
    ll d = t.first;
    ll u = t.second;
    d = -d;
    if (dist[u] < d)
      continue;
    for (auto neigh: G[u]) {
      ll u2 = neigh.first;
      ll w = neigh.second;
      if (dist[u2] > d + w) {
        pq.emplace(-d-w, u2);
        dist[u2] = d + w;
      }
    }
  }
  return dist;
}
