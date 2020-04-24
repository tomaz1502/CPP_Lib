#include <bits/stdc++.h>
using namespace std;

template<typename T>
class MergeSortTree{
    int sz;
    vector< vector<T> > Tree;

    vector<T> merge(const vector<T> &A, const vector<T> &B){
        vector<T> ret;
    
        int i, pta = 0, ptb = 0;
        for(i = 0; i<min(A.size(), B.size()); i++){
            if(pta >= A.size()){
                ret.push_back(B[ptb]);
                continue;
            }
            if(ptb >= B.size()){
                ret.push_back(A[pta]);
                continue;
            }
            if(A[pta] < B[ptb]) ret.push_back(A[pta++]);
            else ret.push_back(B[ptb++]);
        }

        while(pta < A.size()) ret.push_back(A[pta++]);
        while(ptb < B.size()) ret.push_back(B[ptb++]);

        return ret;

    }

    void build(int idT, int l, int r, const vector<T> &V){
        if(l >= r){
            Tree[idT] = {V[l]};
            continue;
        }

        int m = (l+r)/2;
        build(2 * idT, l, m, V);
        build(2 * idT + 1, m+1, r, V);

        Tree[idT] = merge(Tree[2 * idT], Tree[2 * idT + 1]]);

    }

    MergeSortTree(const vector<T> &V){
        Tree = vector< vector<T> >(4 * V.size());
        sz = V.size();
        build(1, 0, n-1, V);
    }


};
