#include <algorithm>
#include <numeric>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

struct SA {
    
    vector<int> sa, ra;
    vector<int> lcp; // lcp[i] = lcp(sa[i], sa[i + 1])
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
            newSa[count[rank(sa[i] + k)]] = sa[i]; // quantos caras tem rank menor que eu?
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
            countingSort(k);
            countingSort(0);

            vector<int> newRa(n);
            newRa[sa[0]] = 0;
            for(int i = 1; i < n; i++) {
                newRa[sa[i]] = newRa[sa[i - 1]];
                bool diff = make_pair(rank(sa[i]), rank(sa[i] + k)) != make_pair(rank(sa[i - 1]), rank(sa[i - 1] + k));
                if(diff) newRa[sa[i]]++;
            }
            
            ra = newRa;
            if(ra[sa[n - 1]] == n - 1) break;
        }

    }

    void buildLCP() {
        lcp.resize(n);
        int h = 0;
        for (int i = 0; i < n; ++i) {
            // calculate lcp[ra[i]]
            if (ra[i] == n - 1) {
                lcp[ra[i]] = 0;
                h = 0;
                continue;
            }
            int j = sa[ra[i] + 1];
            while (i + h < n && j + h < n && S[i + h] == S[j + h]) h++;
            lcp[ra[i]] = h;
            if (h > 0) --h;
        }
    }

};

int main() {
    ios::sync_with_stdio(false);

    string s; cin >> s;
    SA Suff(s);
    for (int i : Suff.sa) cout << i << " ";
    cout << "\n";

    Suff.buildLCP();
    for (int i : Suff.lcp) cout << i << " ";
    cout << "\n";

    return 0;
}
