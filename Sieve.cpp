#include <iostream>
#include <vector>
using namespace std;

vector<int> is_composite;

vector<long long> sieve(long long n) {
	vector<long long> primes;
    is_composite = vector<int>(n + 1, -1);

	for(int i = 2; i < n; ++i) {
        if(!is_composite[i]) {
            primes.push_back(i);
            for(int j = 2 * i; j < n; j += i) {
                is_composite[j] = i;
            }
        }

	}

	return primes;
}

