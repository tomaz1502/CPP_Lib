#include <bits/stdc++.h>
using namespace std;

struct segNode {
    int count, answer;

    segNode(int count_, int answer_) : count(count_) , answer(answer_) {}
};


template<typename T>
class SegTree{ //Array is 0-based, Tree is 1 based
	int sz;
	vector<T> Tree, Lazy;
public:

	void build(int idT, int l, int r, vector<T> &V) {
		if(l == r) Tree[idT] = V[l];
		else{
			int m = (l+r)/2;
			build(idT * 2, l, m, V);
			build(idT * 2 + 1, m+1, r, V);
			Tree[idT] = Tree[idT * 2] + Tree[idT * 2 + 1];
		}
	}

	void propagate(int idT, int l, int r) { //Lazy só funciona com soma (a principio)
		Tree[idT] += (r - l + 1) * Lazy[idT];
		
		if(r != l){
			Lazy[2 * idT] += Lazy[idT];
			Lazy[2 * idT + 1] += Lazy[idT];
		}

		Lazy[idT] = 0;
	}

	T query(int l, int r) { return query(1,0,sz-1,l,r); }

	T query(int idT, int l, int r, int ql, int qr) {
		propagate(idT, l, r);

		if(l >= ql and r <= qr) return Tree[idT];
		if(ql > r or qr < l or l > r) return 0; //aqui tem que ser o elemento neutro de op

		int mid = (l + r)/2;
		
		T res_l = query(2*idT    , l , mid , ql, qr);
		T res_r = query(2*idT + 1, mid+1, r, ql, qr);

		return res_l + res_r;
	}

	void update(int idL, int idR, T value) { update(1, 0, sz-1, idL, idR, value); }

	T update(int idT, int l, int r, int idL, int idR, T value) {

		if(idL <= l and r <= idR){
			Lazy[idT] += value;
			propagate(idT, l, r);
			return Tree[idT];
		}

		propagate(idT, l, r);

		if(idL > r or idR < l) return Tree[idT];		

		int m = (l+r)/2;

		T res_l = update(2 * idT, l, m, idL, idR, value);
		T res_r = update(2 * idT + 1, m+1, r, idL, idR, value);

		return Tree[idT] = res_l + res_r;
	}

	SegTree(vector<T> &V){
		sz = V.size();
		Tree = vector<T>(4*sz);
		Lazy = vector<T>(4*sz);
		build(1, 0, sz-1, V);
	}

};


struct Line {
    int x1, y1, x2, y2;
};

struct Event {
    int up, down, x;
    bool fim;

    Event(int up_, int down_, int x_, bool fim_) : up(up_) , down(down_) , x(x_) , fim(fim_) {}
};

bool operator<(const Event &e1, const Event &e2) {
    return e1.x < e2.x;
}

vector< Line > Lines;
int P;
int Rx1, Ry1, Rx2, Ry2;

bool check(int r) {
    
    vector< Event > Evs;
    for(Line L : Lines) {
        int xL = L.x1 - r, xR = L.x2 + r, yL = L.y1 - r, yR = L.y2 + r;
        xL = max(xL, Rx1);
        xR = min(xR, Rx2);
        yL = max(yL, Ry1);
        yR = min(yR, Ry2);

        Event beg(yL, yR, xL, false);
        Event fin(yL, yR, xR, true);
        Evs.push_back(beg); Evs.push_back(fin);
    }

    sort(Evs.begin(), Evs.end());

    int n = (int)Lines.size();
    vector< segNode > base(n, segNode(0,0));
  //  SegTree< segNode > ST(base);

    for(Event ev : Evs) {

    }

}

int bb(int l, int r) {
    if(l >= r) return l;
    int m = (l + r) / 2;
    if(check(m)) return bb(l, m);
    else return bb(m + 1, r);
}

int main() {
    ios::sync_with_stdio(false);

    int n; cin >> n;
    Lines.resize(n);
    for(Line L : Lines) cin >> L.x1 >> L.y1 >> L.x2 >> L.y2;
    cin >> P;
    cin >> Rx1 >> Ry1 >> Rx2 >> Ry2;

    cout << bb(0,1e5) << '\n';

    return 0;
}
