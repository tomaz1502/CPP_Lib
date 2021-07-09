// stolen from
// https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Trees%20(10)/HLD%20(10.3).h
#include <algorithm>
#include <functional>
#include <vector>
using namespace std;
using ll = long long;

#define ALL(v) v.begin(), v.end()

template <typename T> struct SegTree { // Array is 0-based, Tree is 1 based
  ll size;
  vector<T> Tree, Lazy;

  T neutral_update;
  T neutral_query;

  function<T(T, T)> op_update;
  function<T(T, T)> op_query;
  function<T(ll, T)> op_range;

  void build(ll idT, ll l, ll r, const vector<T> &base) {
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

  SegTree(const vector<T> &base, T _neutral_update, T _neutral_query,
          function<T(T, T)> _op_update, function<T(T, T)> _op_query,
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
  SegTree() {}
  T query(ll l, ll r) { return query(1, 0, size - 1, l, r); }

  void update(ll idL, ll idR, T value) {
    update(1, 0, size - 1, idL, idR, value);
  }
};

template<typename T> function<T(ll, T)> SegTree<T>::default_op_range =
  [] (ll _, T val) { return val; };

template <int SZ, bool VALS_IN_EDGES, typename T> struct HLD {
  vector<vector<int>> adj;
  int N, par[SZ], root[SZ], depth[SZ], sz[SZ], pos[SZ], ti;
  vector<int> rpos; // rpos not used, but could be useful
  void dfsSz(int x) {
    sz[x] = 1;
    for (auto &y : adj[x]) {
      par[y] = x;
      depth[y] = depth[x] + 1;
      adj[y].erase(find(ALL(adj[y]), x)); // remove parent from adj list
      dfsSz(y);
      sz[x] += sz[y];
      if (sz[y] > sz[adj[x][0]])
        swap(y, adj[x][0]);
    }
  }
  void dfsHld(int x) {
    pos[x] = ti++;
    rpos.push_back(x);
    for (const auto &y : adj[x]) {
      root[y] = (y == adj[x][0] ? root[x] : y);
      dfsHld(y);
    }
  }
  int lca(int x, int y) {
    for (; root[x] != root[y]; y = par[root[y]])
      if (depth[root[x]] > depth[root[y]])
        swap(x, y);
    return depth[x] < depth[y] ? x : y;
  }
  int dist(int x, int y) { // # edges on path
  	return depth[x]+depth[y]-2*depth[lca(x,y)]; }
  SegTree<T> tree; // segtree for sum
  HLD(int _N, int R = 0, vector<vector<int>> _adj = {}, SegTree<T> _tree = {})
      : adj(_adj), N(_N), tree(_tree) {
    par[R] = depth[R] = ti = 0;
    dfsSz(R);
    root[R] = R;
    dfsHld(R);
  }
  template <class BinaryOp> void processPath(int x, int y, BinaryOp op) {
    for (; root[x] != root[y]; y = par[root[y]]) {
      if (depth[root[x]] > depth[root[y]])
        swap(x, y);
      op(pos[root[y]], pos[y]);
    }
    if (depth[x] > depth[y])
      swap(x, y);
    op(pos[x] + VALS_IN_EDGES, pos[y]);
  }
  void modifyPath(int x, int y, T v) {
    processPath(x, y, [this, &v](int l, int r) { tree.update(l, r, v); });
  }
  T queryPath(int x, int y) {
    T res = tree.neutral_query;
    processPath(x, y, [this, &res](int l, int r) { 
        res = tree.op_query(res, tree.query(l, r));
    });
    return res;
  }
};
