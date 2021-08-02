#include <cassert>
#include <functional>
#include <vector>
using namespace std;

template <typename T> class SegTree { // array 0-based

public:
  T query(int l, int r) {
    T res = neutral;
    l += sz;
    r += sz;
    while (l <= r) {
      if (l & 1)
        res = op(res, Tree[l++]);
      if (!(r & 1))
        res = op(res, Tree[r--]);
      r >>= 1;
      l >>= 1;
    }
    return res;
  }

  void update(int id, T value) {
    id += sz;
    Tree[id] = op(Tree[id], value);
    for (int i = id >> 1; i >= 1; i >>= 1)
      Tree[i] = op(Tree[i << 1], Tree[(i << 1) | 1]);
  }

  SegTree(const vector<T> &V, function<T(T, T)> op_, T neutral_)
      : neutral(neutral_), op(op_) {
    sz = V.size();
    Tree = vector<T>(2 * sz);
    for (int i = 0; i < sz; i++)
      Tree[sz + i] = V[i];
    for (int i = sz - 1; i > 0; i--)
      Tree[i] = op(Tree[i << 1], Tree[(i << 1) | 1]);
  }

  SegTree(int sz_, function<T(T, T)> op_, T neutral_)
      : sz(sz_), neutral(neutral_), op(op_) {
    Tree = vector<T>(2 * sz, neutral);
  }

private:
  int sz;
  vector<T> Tree;
  const T neutral;
  function<T(T, T)> op;
};

int main() {

  SegTree<int> ST(
      10, [&](int a, int b) { return a + b; }, 0);
  ST.update(2, 3);
  ST.update(3, 4);
  ST.update(4, 5);
  assert(ST.query(0, 9) == 12);
  assert(ST.query(0, 2) == 3);
  assert(ST.query(3, 4) == 9);

  return 0;
}
