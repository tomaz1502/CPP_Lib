#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

vector<ll> represent(ll num, ll b) { // representation of num in base b
    vector<ll> ret;
    ll p = b;

    while(num) {
        ll d0 = num % p;
        ll d = d0 / (p / b);
        ret.push_back(d);
        num -= d0;
        p *= b;
    }

    reverse(ret.begin(), ret.end()); // little endian (optional)
    return ret;
}

int main() {

    return 0;
}
