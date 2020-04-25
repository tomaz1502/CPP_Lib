#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

vector<int> is_composite;

vector<ll> sieve(ll n) {
	vector<ll> primes;
    is_composite = vector<int>(n + 1, -1);

	for(int i = 2; i < n; ++i) {
        if(is_composite[i] == -1) {
            primes.push_back(i);
            for(int j = 2 * i; j < n; j += i) {
                is_composite[j] = i;
            }
        }
	}

	return primes;
}

