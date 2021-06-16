#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

template <typename T> class MergeSortTree {
  int size;
  vector<vector<T>> Tree;

  vector<T> merge(const vector<T> &L, const vector<T> &R) {
    vector<T> answer;

    int pl = 0, pr = 0;
    int size_l = (int)L.size();
    int size_r = (int)R.size();
    while (pl < size_l && pr < size_r) {
      if (pl >= size_l) {
        answer.push_back(R[pr++]);
        continue;
      }
      if (pr >= size_r) {
        answer.push_back(L[pl++]);
        continue;
      }
      if (L[pl] < R[pr])
        answer.push_back(L[pl++]);
      else
        answer.push_back(R[pr++]);
    }

    while (pl < size_l)
      answer.push_back(L[pl++]);
    while (pr < size_r)
      answer.push_back(R[pr++]);

    return answer;
  }

  int query(int idT, int l, int r, int L, int R, T k) {
    if (r < L || l > R)
      return 0;
    if (l >= L && r <= R) {
      int count = (int)(lower_bound(Tree[idT].begin(), Tree[idT].end(), k) -
                        Tree[idT].begin());
      return (int)Tree[idT].size() - count;
    }
    int m = (l + r) / 2;
    int count_left = query(2 * idT, l, m, L, R, k);
    int count_right = query(2 * idT + 1, m + 1, r, L, R, k);
    return count_left + count_right;
  }

  void build(int idT, int l, int r, const vector<T> &base) {
    if (l >= r) {
      Tree[idT] = {base[l]};
    } else {
      int m = (l + r) / 2;
      build(2 * idT, l, m, base);
      build(2 * idT + 1, m + 1, r, base);
      Tree[idT] = merge(Tree[2 * idT], Tree[2 * idT + 1]);
    }
  }

public:
  MergeSortTree(const vector<T> &base) : size((int)base.size()) {
    Tree = vector<vector<T>>(4 * size);
    build(1, 0, size - 1, base);
  }

  // how many elements >= k in [L, R]
  int query(int L, int R, T k) { return query(1, 0, size - 1, L, R, k); }
};

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int &i : a)
    cin >> i;

  MergeSortTree<int> mt(a);
  int q;
  cin >> q;
  while (q--) {
    int l, r, k;
    cin >> l >> r >> k;
    cout << mt.query(l, r, k) << "\n";
  }

  return 0;
}
