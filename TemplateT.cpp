#pragma GCC optimize "-O3"
#pragma GCC optimize "unroll-loops"

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;
using ll = long long;

template <class T>
using ord_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define N ((int)1e5 + 1)
#define forn(i,x,y) for(int i = int(x); i<int(y); i++)
#define debug(x) cerr << #x << " == " << (x) << '\n';

template<typename T> ostream &operator<<(ostream &out, const pair<T, T> &P){ out << P.first << ' ' << P.second; return out; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &V){ for(int i = 0; i<V.size(); ++i) out << V[i] << " ";  return out; }
template<typename T> istream &operator>>(istream &in, vector<T> &V){ for(T &i : V) in >> i; return in; }
template<typename T> istream &operator>>(istream &in, pair<T,T> &P){ in >> P.first >> P.second; return in; }

template<typename T>
class SegTree{ //Tudo 0-based
	int sz;
    T neutral;
	vector<T> Tree;
	function<T(T,T)> op;
public:
 
	T query(int l, int r){
        T res = neutral;
        l += sz; r += sz;
        while(l <= r){
            if(l & 1) res = op(res, Tree[l++]);
            if(!(r & 1)) res = op(res, Tree[r--]);
            r >>= 1; l >>= 1;
        }
        return res;
    }
 
	void update(int id, T value){
        Tree[sz + id] = value;
        id += sz;
        for(int i = id; i>1; i >>= 1) Tree[i>>1] = op(Tree[i], Tree[i^1]);
    }
 
	SegTree(const vector<T> &V, function<T(T,T)> op_, T neutral_){
        neutral = neutral_;
		sz = V.size();
		Tree = vector<T>(2*sz);
		op = op_;
        for(int i = 0; i<sz; i++) Tree[sz + i] = V[i];
        for(int i = sz-1; i>0; i--) Tree[i] = op(Tree[i<<1], Tree[(i<<1) | 1]);
    }
 
};

template<typename T> //T must be "sum-able -> may have operator+ defined"
class BIT {
	vector<T> B; //EVERYTHING IS ONE-BASED

public:
	void update(int index, T value) {
		while(index < B.size()){
			B[index] += value;
			index += (index & -index);
		}
	}

	T sum(int end) {
		T ret = 0;
		while(end >= 1){
			ret += B[end];
			end -= (end & -end);
		}
		return ret;
	}

	T range_sum(int begin, int end) {
		assert(begin > 0);
		return sum(end) - sum(begin - 1);
	}

	BIT(const vector<T> &base) {
		B = vector<T>(base.size(), 0);
		for(int i = 1; i<base.size(); ++i){
			this->update(i, base[i]);
		}
	}
	
	BIT(int sz){ B = vector<T>(sz, 0); }
};

class PrefixSum {
 
    vector<ll> Pref;
    int sz;
 
public:
    
    ll query(int l, int r) {
        r = min(r, sz - 1);
        if(l <= 0) return Pref[r];
        return Pref[r] - Pref[l - 1];
    }
 
 
    PrefixSum(vector<ll> &v) {
        sz = (int)v.size();
        Pref.resize(sz);
        Pref[0] = v[0];
        for(int i = 1; i<sz; ++i) Pref[i] = Pref[i-1] + v[i];
    }
 
 
};

class Trie{
	vector< vector<int> > T;
	vector<bool> endOfWord;
	int prox = 1;

public:

	Trie(int maxNodes, int alphabetSize){ //maxNodes is the maximum amount of letters allowed
		T = vector< vector<int> >(maxNodes, vector<int>(alphabetSize, 0));
		endOfWord = vector<bool>(maxNodes, false);
	}

	void insert(string s){
		int at = 1;
		for(int i = 0; i<s.length(); ++i){
			int let = s[i] - 'a'; //can change
			if(T[at][let] == 0){
                T[at][let] = ++prox;
			}
			at = T[at][let];
			if(i == s.length() - 1) endOfWord[at] = true;
		}
	}
};

vector<bool> is_composite;

vector<ll> sieve(ll n) {
    vector<ll> primes;
    is_composite = vector<bool>(n + 1, false);

    for(int i = 2; i < n; ++i) {
        if(!is_composite[i]) {
            primes.push_back(i);
            for(int j = 2 * i; j < n; j += i) {
                is_composite[j] = true;
            }
        }
    }
    
    return primes;
}

ll powmod(ll base, ll exp, ll modulus) {
	base %= modulus;
	ll result = 1;
	while (exp > 0) {
		if (exp & 1) result = (result * base) % modulus;
		base = (base * base) % modulus;
		exp >>= 1;
	}
  	return result;
}

// source : https://github.com/kth-competitive-programming/kactl/blob/master/content/data-structures/LineContainer.h
// get MAXIMUM. to get minimum : insert lines with -m and -c, answer will be -min
#pragma once

struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct CHT : multiset<Line, less<> > {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) { x->p = inf; return false; }
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};

vector< vector< ll > > pascal(int n_max, ll modulus){
	vector< vector< ll > > ret = vector< vector< ll > >(0, vector<ll>(0));
	ret[0][0] = 1;
	for(int i = 1; i<=n_max; i++){
		ret[i][0] = 1;
		for(int j = 1; j<=i; j++){
			ret[i][j] = (ret[i-1][j] + ret[i-1][j-1]) % modulus;
		}
	}
	return ret;
}


vector<int> lps;

void buildKMP(string Ptt){
    lps.resize(Ptt.size());
    lps[0] = 0;
    int i = 1, j = 0;
    while(i < Ptt.size()){ //preenche lps[i] (ja tem todos ate i-1 calculados)
        if(Ptt[i] == Ptt[j]){
            i++;
            j++;
            lps[i-1] = j;
        }
        else{
            if(j == 0){
                lps[i] = 0;
                i++;
            }
            else j = lps[j-1];
        }
    }
}

void searchKMP(string Ptt, string Txt){
    int i = 0, j = 0, n = Txt.size(), m = Ptt.size();
    while(i - j <= n - m){
        if(Ptt[j] == Txt[i]){
            i++;
            j++;
            if(j == m){
                cout << "achei: " << i-j << '\n';
                j = lps[j-1];
            }
        }
        else{
            if(j == 0) i++;
            else j = lps[j-1];
        }
    }
}

vector<ll> represent(ll num, ll b) { // representation of num in base b
    vector<ll> ret;
    ll p = b;

    while(num) {
        ll d0 = num % p;
        ll d = d0 / (p / b);
        ret.push_back(d);
        num -= d0;
        p *= b;
    }

    reverse(ret.begin(), ret.end()); // little endian (optional)
    return ret;
}

int LIS(const vector< int > &a) { // Longest non-decreasing: troca lower por upper
    int n = a.size(), lim = 1e8;
    vector<int> d(n+1, lim);
    for (int j = 0; j < n; j++) {
        *lower_bound(d.begin(), d.end(), a[j]) = a[j];
    }
    for(int j = 0; j<=n; j++) {
        if(d[j] == lim) return j;
    }
}

int main(){

	return 0;
}
