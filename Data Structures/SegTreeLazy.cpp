#include <iostream>
#include <vector>
#include <functional>
using namespace std;
using ll = long long;


template <typename T> class SegTree { // Array is 0-based, Tree is 1 based
  ll size;
  vector<T> Tree, Lazy;

  T neutral_update;
  T neutral_query;

  function<T(T,T)> op_update;
  function<T(T,T)> op_query;
  function<T(ll,T)> op_range;

  void build(ll idT, ll l, ll r, const vector<T>& base) {
    if (l == r)
      Tree[idT] = base[l];
    else {
      ll m = (l + r) / 2;
      build(idT * 2, l, m, base);
      build(idT * 2 + 1, m + 1, r, base);
      Tree[idT] = op_query(Tree[idT * 2], Tree[idT * 2 + 1]);
    }
  }

  void propagate(ll idT, ll l, ll r, bool real = false) {
    if (!real && Lazy[idT] == neutral_update)
      return;
    Tree[idT] = op_update(Tree[idT], op_range(r - l + 1, Lazy[idT]));
    if (r != l) {
      Lazy[2 * idT] = op_update(Lazy[2 * idT], Lazy[idT]);
      Lazy[2 * idT + 1] = op_update(Lazy[2 * idT + 1], Lazy[idT]);
    }
    Lazy[idT] = neutral_update;
  }

  T query(ll idT, ll l, ll r, ll L, ll R) {
    propagate(idT, l, r);

    if (l >= L && r <= R)
      return Tree[idT];
    if (L > r || R < l || l > r)
      return neutral_query;

    ll mid = (l + r) / 2;

    T res_l = query(2 * idT, l, mid, L, R);
    T res_r = query(2 * idT + 1, mid + 1, r, L, R);

    return op_query(res_l, res_r);
  }

  T update(ll idT, ll l, ll r, ll idL, ll idR, T value) {
    if (idL <= l && r <= idR) {
      Lazy[idT] = op_update(Lazy[idT], value);
      propagate(idT, l, r, true);
      return Tree[idT];
    }

    propagate(idT, l, r);
    if (idL > r || idR < l)
      return Tree[idT];

    ll m = (l + r) / 2;

    T res_l = update(2 * idT, l, m, idL, idR, value);
    T res_r = update(2 * idT + 1, m + 1, r, idL, idR, value);

    return Tree[idT] = op_query(res_l, res_r);
  }

  static function<T(ll, T)> default_op_range;
public:

  SegTree(const vector<T>& base,
          T _neutral_update,
          T _neutral_query,
          function<T(T,T)> _op_update,
          function<T(T,T)> _op_query,
          function<T(ll, T)> _op_range = default_op_range) {
    size = base.size();
    neutral_update = _neutral_update;
    neutral_query = _neutral_query;
    op_update = _op_update;
    op_query = _op_query;
    op_range = _op_range;
    Tree = vector<T>(4 * size);
    Lazy = vector<T>(4 * size, neutral_update);
    build(1, 0, size - 1, base);
  }

  T query(ll l, ll r) { return query(1, 0, size - 1, l, r); }

  void update(ll idL, ll idR, T value) {
    update(1, 0, size - 1, idL, idR, value);
  }
};

template<typename T> function<T(ll, T)> SegTree<T>::default_op_range =
  [] (ll _, T val) { return val; };

// solves -> https://codeforces.com/edu/course/2/lesson/5/2/practice/contest/279653/problem/F
int main() {
  ll n, m;
  cin >> n >> m;
  vector<ll> a(n + 1, 0);

  SegTree<ll> S(a, 0, 0, [&] (ll _x, ll y) { return y; },
                   [&] (ll x, ll y) { return x + y; },
                   [&] (ll r, ll val) { return r * val; });
  while (m--) {
    ll t;
    cin >> t;
    if (t == 1) {
      ll l, r, v;
      cin >> l >> r >> v;
      S.update(l, r - 1, v);
    } else {
      ll l, r;
      cin >> l >> r;
      cout << S.query(l, r - 1) << "\n";
    }
  }

  return 0;
}


