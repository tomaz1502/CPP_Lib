// update em range (O (log))
// query em ponto  (O (log))
// cuidado com update de assign -> usar elemento neutro = -1

#include <bits/stdc++.h>
using namespace std;

template<typename T>
class SegTree { //Array is 0-based, Tree is 1 based
	int size;
	vector<T> Lazy;
    function<T(T,T)> operation;
    T neutral;

    void push_down(int node) {
        if (Lazy[node] != neutral) {
            Lazy[2 * node] = operation(Lazy[node], Lazy[2 * node]);
            Lazy[2 * node + 1] = operation(Lazy[node], Lazy[2 * node + 1]);
            Lazy[node] = neutral;
        }
    }

	void update(int node, int l, int r, int idL, int idR, T value) {
        if (l != r)
            push_down(node);

		if (idL <= l && r <= idR) {
			Lazy[node] = operation(value, Lazy[node]);
			return;
		}

		if (idL > r || idR < l) return;

		int m = (l + r) / 2;

        update(2 * node, l, m, idL, idR, value);
		update(2 * node + 1, m + 1, r, idL, idR, value);
	}

    T get(int id, int node, int L, int R) {
        if (L == R)
            return Lazy[node];

        push_down(node);

        int M = (L + R) / 2;
        if (id <= M)
            return get(id, 2 * node, L, M);
        else
            return get(id, 2 * node + 1, M + 1, R);
    }

public:
    SegTree(int len, function<T(T,T)> _operation, T _neutral) : size(len), operation(_operation), neutral(_neutral) {
        Lazy = vector<T>(4 * size, neutral);
    }

	void update(int idL, int idR, T value) {
		update(1, 0, size - 1, idL, idR, value);
	}

    T get(int id) {
        return get(id, 1, 0, size - 1);
    }
};

int main() {

    return 0;
}
