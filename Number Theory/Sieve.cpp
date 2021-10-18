#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

vector<int> min_factor;

vector<int> sieve(int n) {
  vector<int> primes;
  min_factor = vector(n + 1, -1);

  for (int i = 2; i <= n; ++i) {
    if (min_factor[i] == -1) {
      primes.push_back(i);
      for (int j = 2 * i; j <= n; j += i)
        min_factor[j] = i;
    }
  }

  return primes;
}

