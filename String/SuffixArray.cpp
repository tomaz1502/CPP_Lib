#include <algorithm>
#include <numeric>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

struct SA {
    
    vector<int> sa, ra;
    string S;
    int n, maxc;

    int rank(int suff_index) {
        if(suff_index < n) return ra[suff_index];
        else return 0;
    }

    void countingSort(int k) {
        vector<int> newSa(n), count(maxc, 0);
        for(int i = 0; i < n; i++) count[rank(i + k)]++;

        int sum = 0;
        for(int i = 0; i < maxc; i++) {
            int temp = count[i];
            count[i] = sum;
            sum += temp;
        }

        for(int i = 0; i < n; i++) {
            newSa[count[rank(sa[i] + k)]] = sa[i];
            count[rank(sa[i] + k)]++;
        }

        sa = newSa;
    }
    
    SA(const string &s) {
        S = s;
        S += "$";
        n = S.size();
        maxc = max(n, 300);

        ra.resize(n);
        sa.resize(n);

        for(int i = 0; i < n; i++) ra[i] = (int)S[i];
        iota(sa.begin(), sa.end(), 0);

        for(int k = 1; k < n; k <<= 1) {
            //sort(sa.begin(), sa.end(), [&](int i, int j) { return val(i, k) < val(j, k); } );
            countingSort(k);
            countingSort(0);
         //   cout << "Current k: " << k << " sa:\n";
         //   for(int i : sa) cout << i << "\n";

            vector<int> newRa(n);
            newRa[sa[0]] = 0;
            for(int i = 1; i < n; i++) {
                newRa[sa[i]] = newRa[sa[i - 1]];
                bool diff = make_pair(rank(sa[i]), rank(sa[i] + k)) != make_pair(rank(sa[i - 1]), rank(sa[i - 1] + k));
                if(diff) newRa[sa[i]]++;
            }
            
            ra = newRa;
            if(ra[sa[n - 1]] == n - 1) break;
         //   cout << "Rank:\n";
         //   for(int i = 0; i < n; i++) cout << ra[i] << "\n";
        }

    }

};

int main() {
    ios::sync_with_stdio(false);

    string s; cin >> s;
    SA Sa(s);

    for(int i = 1; i < (int)Sa.sa.size(); i++) cout << Sa.sa[i] << "\n";
    return 0;
}
