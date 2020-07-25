#include <vector>
#include <cassert>

int LIS(const std::vector< int > &a) { // Longest non-decreasing: troca lower por upper
    int n = a.size(), lim = 1e8;
    std::vector<int> d(n+1, lim);
    for (int j = 0; j < n; j++) {
        *std::lower_bound(d.begin(), d.end(), a[j]) = a[j];
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
