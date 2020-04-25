#include <vector>
#include <cassert>
using namespace std;

int LIS(const vector< int > &a) { // Longest non-decreasing: troca lower por upper
    int n = a.size(), lim = 1e8;
    vector<int> d(n+1, lim);
    for (int j = 0; j < n; j++) {
        *lower_bound(d.begin(), d.end(), a[j]) = a[j];
    }
    for(int j = 0; j<=n; j++) {
        if(d[j] == lim) return j;
    }

    assert(false);
    return -1;
}

int main() {

    return 0;
}
