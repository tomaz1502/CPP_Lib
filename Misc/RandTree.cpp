#include <iostream>
#include <random>
#include <chrono>
#include <vector>

using namespace std;

mt19937 rng((int)chrono::steady_clock::now().time_since_epoch().count());

int gen(int l , int r)
{
  return l + (rng() % (r - l + 1));
}

// Generates a random tree of size n
vector<vector<int>> rand_tree(int n)
{
  vector<vector<int>> G(n);
  vector<int> s(n - 2);
  vector<int> deg(n, 1);
  for (int& i : s) i = gen(0, n - 1);
  for (int i : s) deg[i]++;
  for (int i : s) {
    for (int j = 0; j < n; j++) {
      if (deg[j] == 1) {
        G[i].push_back(j);
        G[j].push_back(i);
        deg[i]--;
        deg[j]--;
        cout << "edge: " << i << " <-> " << j << "\n";
        break;
      }
    }
  }

  int u = -1, v = -1;
  for (int i = 0; i < n; i++) {
    if (deg[i] == 1) {
      if (u == -1)
        u = i;
      else {
        v = i;
        break;
      }
    }
  }
  G[u].push_back(v);
  G[v].push_back(u);
  cout << "edge: " << u << " <-> " << v << "\n";

  return G;
}

int main() { rand_tree(20); }
