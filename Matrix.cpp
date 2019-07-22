#include <bits/stdc++.h>
using namespace std;

const long long mod = 1e9 + 7;

template <typename T>
class Matrix{
	vector< vector<T> > M;

public:
	Matrix(long long rows, long long columns, bool identity = false){
		M = vector< vector<T> >(rows, vector<T>(columns, 0));
		assert(rows == columns or identity == false);
		if(identity) for(long long i = 0; i<rows; ++i) this->update(i,i,1);

	}

	Matrix(vector< vector<T> > V){
		M = V;
	}

	long long size() const{
		return this->M.size();
	}

	T get(long long i, long long j) const{
		return M[i][j];
	}

	vector<T> get(long long i) const{
		return M[i];
	}

	vector<T>& operator[](long long i){
		return M[i];
	}

	void update(long long i, long long j, T value){
		M[i][j] = value;
	}

	Matrix<T> operator+(const Matrix<T> &M_) const{
		Matrix<T> ret = Matrix(M.size(), M[0].size());
		assert(M.size() == M_.size());

		for(long long i = 0; i<M.size(); ++i){
			assert(M[i].size() == M_.get(i).size());

			for(long long j = 0; j<M[i].size(); ++j){
				ret.update(i,j, M[i][j] + M_.get(i,j));
			}
		}

		return ret;
	}

	Matrix<T> operator*(const Matrix<T> &M_) const{
		assert(M[0].size() == M_.size());
		Matrix<T> ret = Matrix(M.size(), M_.get(0).size());

		for(long long i = 0; i<M.size(); ++i){
			for(long long j = 0; j<M_.get(0).size(); ++j){
				long long c = 0;
				for(long long k = 0; k<M_.size(); ++k) c = (c + M[i][k] * M_.get(k,j))%mod;
				ret.update(i,j,c);
			}
		}

		return ret;
	}

	Matrix<T> operator^(long long exp) const{
		assert(M.size() == M[0].size()); //M is a square matrix
		Matrix<T> ret = Matrix<T>(M.size(), M[0].size(), true);
		Matrix<T> aux = Matrix<T>(M);

		while(exp){
			if(exp & 1) ret = ret * aux;
			aux = aux*aux;
			exp >>= 1;
		}

		return ret;
	}

};

template<typename T>
ostream& operator<<(ostream &out, Matrix<T> &M){
	for(long long i = 0; i<M.size(); ++i, out << '\n'){
		for(long long j = 0; j<M[i].size(); ++j) out << M[i][j] << ' ';
	}
	return out;
}
