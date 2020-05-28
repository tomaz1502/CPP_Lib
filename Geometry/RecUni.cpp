#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 3e5 + 10;

struct segNode {
    ll tag, answer, sum;
    segNode(ll tag_, ll answer_, ll sum_) : tag(tag_) , answer(answer_), sum(sum_) {}
};


struct SegTree{ //Array is 0-based, Tree is 1 based
	ll sz;
	vector< segNode > Tree;

    void build(ll idT, ll l, ll r) {
        if(l == r) Tree[idT].sum = 1;
        else {
            ll mid = (l + r) / 2;
            build(2 * idT, l, mid);
            build(2 * idT + 1, mid + 1, r);
            Tree[idT].sum = Tree[2 * idT].sum + Tree[2 * idT + 1].sum;
        }
    }

    ll ask(ll node) {
        if(Tree[node].tag) return Tree[node].sum;
        return Tree[node].answer;
    }

	void update(ll idL, ll idR, ll value) { update(1, 0, sz-1, idL, idR, value); }
	void update(ll idT, ll l, ll r, ll idL, ll idR, ll value) {
		if(idL <= l and r <= idR) {
            Tree[idT].tag += value;
            return;
		}

	 if(idL > r or idR < l) return;

		ll m = (l + r) / 2;

	    update(2 * idT, l, m, idL, idR, value);
		update(2 * idT + 1, m+1, r, idL, idR, value);

        Tree[idT].answer = ask(2 * idT) + ask(2 * idT + 1);
    }

    SegTree(ll sz_) {
        sz = sz_;
        Tree.assign(4 * N, segNode(0,0,0));
        build(1, 0, sz - 1);
    }

};

struct Rec {
    int x1, y1, x2, y2;
};

struct Event {
    int up, down, x;
    int type;

    Event(int down_, int up_, int x_, int type_) : up(up_) , down(down_) , x(x_) , type(type_) {}
};

bool operator<(const Event &e1, const Event &e2) {
    return e1.x < e2.x;
}

ll RecUnion(const vector< Rec > &Recs) {

    vector< Event > Evs;
    for(Rec R : Recs) {
        int yL = R.y1, yR = R.y2;
        int xL = R.x1, xR = R.x2;

        Evs.emplace_back(yL, yR, xL, 1);
        Evs.emplace_back(yL, yR, xR, -1);
    }

    sort(Evs.begin(), Evs.end());
    SegTree ST(N);

    int last = 0;
    ll ans = 0;
    for(Event ev : Evs) {
        ans += 1LL * ST.ask(1) * (ev.x - last);
        last = ev.x;

        ST.update(ev.down + 1, ev.up, ev.type);
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    int n; cin >> n;
    vector< Rec > Recs(n);
    for(Rec &R : Recs) cin >> R.x1 >> R.y1 >> R.x2 >> R.y2; // bottom left and up right corners

    cout << RecUnion(Recs) << '\n';

    return 0;
}
