#include <vector>
#include <iostream>
using namespace std;

template<typename T>
class SegTree { //Array is 0-based, Tree is 1 based
	int size;
	vector<T> Tree, Lazy;

	void build(int idT, int l, int r, const vector<T>& base) {
		if (l == r)
			Tree[idT] = base[l];
		else {
			int m = (l + r) / 2;
			build(idT * 2, l, m, base);
			build(idT * 2 + 1, m + 1, r, base);
			Tree[idT] = Tree[idT * 2] + Tree[idT * 2 + 1];
		}
	}

	void propagate(int idT, int l, int r) { //Lazy só funciona com soma (a principio)
		Tree[idT] += (r - l + 1) * Lazy[idT];
		if (r != l) {
			Lazy[2 * idT] += Lazy[idT];
			Lazy[2 * idT + 1] += Lazy[idT];
		}
		Lazy[idT] = 0;
	}


	T query(int idT, int l, int r, int L, int R) {
		propagate(idT, l, r);

		if (l >= L && r <= R) return Tree[idT];
		if (L > r || R < l || l > r) return 0; //aqui tem que ser o elemento neutro de op

		int mid = (l + r) / 2;
		
		T res_l = query(2 * idT, l, mid , L, R);
		T res_r = query(2 * idT + 1, mid + 1, r, L, R);

		return res_l + res_r;
	}


	T update(int idT, int l, int r, int idL, int idR, T value) {
		propagate(idT, l, r);

		if (idL <= l && r <= idR) {
			Lazy[idT] += value;
			return Tree[idT];
		}

		if (idL > r || idR < l) return Tree[idT];

		int m = (l + r) / 2;

		T res_l = update(2 * idT, l, m, idL, idR, value);
		T res_r = update(2 * idT + 1, m + 1, r, idL, idR, value);

		return Tree[idT] = res_l + res_r;
	}

public:
	SegTree(const vector<T>& base) : size((int) base.size()) {
		Tree = vector<T>(4 * size);
		Lazy = vector<T>(4 * size);
		build(1, 0, size - 1, base);
	}

	T query(int l, int r) {
		return query(1, 0, size - 1, l, r);
	}

	void update(int idL, int idR, T value) {
		update(1, 0, size - 1, idL, idR, value);
	}
};

int main() {
	int n; cin >> n;
	vector<int> a(n);
	for (int& i: a) cin >> i;

	SegTree<int> st(a);
	int q; cin >> q;
	while (q--) {
		int t; cin >> t;
		if (t == 1) {
			int l, r, v; cin >> l >> r >> v;
			st.update(l,r,v);
		}
		else {
			int l, r; cin >> l >> r;
			cout << st.query(l,r) << "\n";
		}
	}

	return 0;
}
