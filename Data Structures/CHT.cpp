#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Line {

  ll m, c;
  ll eval(ll x) { return m * x + c; }
  long double intersectX(const Line &L) {
    assert(L.m != m);
    return (long double)(c - L.c) / (long double)(L.m - m);
  }

  Line(ll m_, ll c_) : m(m_), c(c_) {}
};

struct CHT { // queries can be in arbitrary order. insertions must be in
             // decreasing slope

  deque<Line> dq;

  ll query(ll x) {
    if (dq.size() == 1)
      return dq[0].eval(x);

    int sz = (int)dq.size();
    if (dq[sz - 1].intersectX(dq[sz - 2]) <= x)
      return dq.back().eval(x);

    int L = 0, R = (int)dq.size() - 2;
    while (L < R) {
      int M = (L + R) / 2;
      long double y = dq[M].intersectX(dq[M + 1]);
      if (x <= y)
        R = M;
      else
        L = M + 1;
    }
    return dq[L].eval(x);
  }

  void insert(ll m, ll c) {
    Line in(m, c);
    while (dq.size() > 1) {
      Line L1 = dq.back(), L2 = dq[(int)dq.size() - 2];
      long double x1 = in.intersectX(L1), x2 = L1.intersectX(L2);
      if (x1 > x2)
        break;
      dq.pop_back();
    }
    dq.push_back(in);
  }
};
