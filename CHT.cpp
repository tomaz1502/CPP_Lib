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

    Line(ll m_, ll c_) : m(m_) , c(c_) {} 

};

struct CHT { // assume queries and insertions on descending order of x
    
    deque< Line > dq;

    ll query(ll x) {
        while(dq.size() > 1) {
            Line L1 = dq.back(), L2 = dq[dq.size() - 2];
            if(L1.eval(x) < L2.eval(x)) dq.pop_back();
            else break;
        }
        return dq.back().eval(x);
    }

    void insert(ll m, ll c) {
        Line in(m,c);
        while(dq.size() > 1) {
            Line L1 = dq.front(), L2 = dq[1];
            long double x1 = in.intersectX(L1), x2 = L1.intersectX(L2);
            if(x1 < x2) break;
            dq.pop_front();
        }
        dq.push_front(in);
    }

};


