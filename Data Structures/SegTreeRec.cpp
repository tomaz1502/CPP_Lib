#include <cassert>
#include <vector>
#include <functional>
using namespace std;

template<typename T>
class SegTree { //Tudo 0-based

public :
 
    void build(size_t node, size_t L, size_t R, const vector<T>& V) {
        if (L == R) Tree[node] = V[L];
        else {
            size_t M = (L + R) / 2;
            build(2 * node, L, M, V);
            build(2 * node + 1, M + 1, R, V);
            Tree[node] = op(Tree[2 * node], Tree[2 * node + 1]);
        }
    }

    T query(size_t l, size_t r, size_t node, size_t L, size_t R) {
        if (l > R or r < L)
            return neutral;
        if (l <= L and R <= r)
            return Tree[node];
        
        size_t M = (L + R) / 2;
        return op(query(l, r, 2 * node, L, M), query(l, r, 2 * node + 1, M + 1, R));
    }

    T query(size_t l, size_t r) { return query(l, r, 1, 0, sz - 1); }

    void update(size_t id, T val, size_t node, size_t L, size_t R) {
        if (L == R) Tree[node] = op(Tree[node], val);
        else {
            size_t M = (L + R) / 2;
            
            if (id <= M)
                update(id, val, 2 * node, L, M);
            else
                update(id, val, 2 * node + 1, M + 1, R);
            
            Tree[node] = op(Tree[2 * node], Tree[2 * node + 1]);
        }
    }

    void update(size_t id, T val) { update(id, val, 1, 0, sz - 1); }

	SegTree(const vector<T>& V, function<T(T,T)> op_, T neutral_) : neutral(neutral_) , op(op_) {
		sz = V.size();
		Tree = vector<T>(4 * sz);
    
        build(1, 0, sz - 1, V);
    }

    SegTree(size_t sz_, function<T(T, T)> op_, T neutral_) : sz(sz_) , neutral(neutral_) , op(op_) {
        Tree = vector<T>(4 * sz, neutral);
    }
 
private :

    size_t sz;
    vector<T> Tree;
    const T neutral;
    function<T(T, T)> op;

};

int main() {

    SegTree<int> ST(10, [&] (int a, int b) { return a + b; }, 0);
    ST.update(2, 3);
    ST.update(3, 4);
    ST.update(4, 5);
    assert(ST.query(0, 9) == 12);
    assert(ST.query(0, 2) == 3);
    assert(ST.query(3, 4) == 9);

    return 0;
}
