#include <bits/stdc++.h>
using namespace std;


template <typename T>
struct Matrix {
    vector< vector<T> > M;

    Matrix(int rows, int columns, bool identity = false) {
        M = vector< vector<T> >(rows, vector<T>(columns, 0));
        assert(rows == columns or identity == false);

        if(identity) for(int i = 0; i<rows; ++i) this->update(i,i,1);
    }

    Matrix(const vector< vector<T> > &V) { M = V; }

    int size() const { return this->M.size(); }

    vector<T>& operator[](int i){ return M[i]; }

    Matrix<T> invert() {


    }

    Matrix<T> operator+(const Matrix<T> &M_) const {
        Matrix<T> ret = Matrix(M.size(), M[0].size());
        assert(M.size() == M_.size());

        for(int i = 0; i<M.size(); ++i) {
            assert(M[i].size() == M_.get(i).size());

            for(int j = 0; j<M[i].size(); ++j){
                ret.update(i,j, M[i][j] + M_.get(i,j));
            }
        }

        return ret;
    }

    Matrix<T> operator*(const Matrix<T> &M_) const {
        assert(M[0].size() == M_.size());
        Matrix<T> ret = Matrix(M.size(), M_.get(0).size());

        for(int i = 0; i<M.size(); ++i) {
            for(int j = 0; j<M_.get(0).size(); ++j){
                int c = 0;
                for(int k = 0; k<M_.size(); ++k) c = (c + M[i][k] * M_.get(k,j));
                ret.update(i,j,c);
            }
        }

        return ret;
    }

    Matrix<T> operator^(int exp) const {
        assert(M.size() == M[0].size()); //M is a square matrix
        Matrix<T> ret = Matrix<T>(M.size(), M[0].size(), true);
        Matrix<T> temp = Matrix<T>(M);

        while(exp) {
            if(exp & 1) ret = ret * temp;
            temp = temp * temp;
            exp >>= 1;
        }

        return ret;
    }

    Matrix<T> neg() {
        Matrix<T> ret(*this);
        for(int i = 0; i < this->size(); i++) for(int j = 0; j < M[i].size(); j++) ret[i][j] *= -1;
        return ret;
    }

    void operator+=(Matrix<T> M_) { *this = *this + M_; }
    void operator-=(Matrix<T> M_) { *this = *this + M_.neg(); }
    void operator*=(Matrix<T> M_) { *this = *this * M_; }
};

template<typename T>
ostream& operator<<(ostream &out, Matrix<T> &M) {
    for(int i = 0; i<M.size(); ++i, out << '\n') {
        for(int j = 0; j<M[i].size(); ++j) out << M[i][j] << ' ';
    }
    return out;
}
