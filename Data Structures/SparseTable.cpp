#include <bits/stdc++.h>
using namespace std;


template< typename T >
class SparseTable {
    
    vector< vector< T > > SpT;
    function<T(T,T)> F;
    vector< int > logr;
    int sz, lg;

public:

    SparseTable(vector< T > &V, function<T(T,T)> F_) {
        F = F_;
        sz = V.size();
        lg = (int)log2(sz) + 1;
        SpT = vector< vector< T > >(sz, vector< T >(lg));

        for(int i = 0; i<sz; i++) {
            SpT[i][0] = V[i];
        }

        for(int j = 1; j<lg; j++) {
            for(int i = 0; i + 1 << (j - 1) < sz; ++i) {
                SpT[i][j] = F(SpT[i][j-1], SpT[i + 1 << (j - 1)][j-1]);
            }
        }
        
        logr = vector<int>(lg + 1);
        logr[1] = 0;
        for(int i = 2; i<lg; i++) logr[i] = logr[i/2] + 1;

    }

    T querry(int L, int R) {
        T ret = 0; // neutral element of F
        for(int j = lg-1; j>=0; j--) {
            if(1 << j <= R - L + 1) {
                ret = F(ret, SpT[L][j]);
                L += 1 << j;
            }
        }
        return ret;
    }

    T fastQuerry(int L, int R) { // O(1) (only for idempotent functions)
        int j = logr[R - L + 1];
        return F(SpT[L][j], SpT[R - (1 << j) + 1][j]);
    }


};

int f(int a, int b) { return min(a,b); }


int main() {

    vector<int> V = {1,4,1,2,3,10,6,3};

    SparseTable<int> S(V,f);
    cout << S.fastQuerry(3,5) << '\n';

    return 0;
}
