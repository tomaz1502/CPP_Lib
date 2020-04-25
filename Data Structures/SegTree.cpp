#include <vector>
#include <functional>
using namespace std;

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

int main() {

    return 0;
}
