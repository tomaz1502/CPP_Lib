#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

struct SuffixArray {

  vector<int> sa, ra;
  vector<int> lcp; // lcp[i] = lcp(sa[i], sa[i + 1])
  string S;
  int n, maxc;

  vector<int> countingSort(int k) {
    vector<int> sorted(n), count(maxc, 0);
    for (int i = 0; i < n; i++)
      count[ra[i + k]]++;

    int sum = 0;
    transform(count.begin(), count.end(), count.begin(), [&](int x) {
      sum += x;
      return sum - x;
    });

    for (int i = 0; i < n; i++) {
      sorted[count[ra[sa[i] + k]]] = sa[i];
      count[ra[sa[i] + k]]++;
    }
    return sorted;
  }

  SuffixArray(const string &&_S) {
    SuffixArray(static_cast<const string &>(_S));
  }

  SuffixArray(const string &_S) : S(_S) {
    S += "$";
    n = S.size();
    maxc = max(n, 260);

    ra = vector<int>(S.begin(), S.end());
    ra.insert(ra.end(), n, 0);

    sa.resize(n);
    iota(sa.begin(), sa.end(), 0);
    for (int k = 1; k < n; k <<= 1) {
      sa = countingSort(k);
      sa = countingSort(0);

      vector<int> newRa(n);
      newRa[sa[0]] = 0;
      for (int i = 1; i < n; i++) {
        newRa[sa[i]] = newRa[sa[i - 1]];
        bool diff = ra[sa[i]]     != ra[sa[i - 1]] ||
                    ra[sa[i] + k] != ra[sa[i - 1] + k];
        if (diff)
          newRa[sa[i]]++;
      }

      ra = newRa;
      if (ra[sa[n - 1]] == n - 1)
        break;
    }
  }

  void buildLCP() {
    lcp.resize(n);
    int h = 0;
    for (int i = 0; i < n; ++i) {
      if (ra[i] == n - 1) {
        lcp[ra[i]] = 0;
        h = 0;
        continue;
      }
      int j = sa[ra[i] + 1];
      while (i + h < n && j + h < n && S[i + h] == S[j + h])
        h++;
      lcp[ra[i]] = h;
      if (h > 0)
        --h;
    }
  }
};

int main() {
  ios::sync_with_stdio(false);

  string s;
  cin >> s;
  SuffixArray Suff(s);
  for (int i : Suff.sa)
    cout << i << " ";
  cout << "\n";

  Suff.buildLCP();
  for (int i : Suff.lcp)
    cout << i << " ";
  cout << "\n";

  return 0;
}
