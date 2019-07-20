#include <bits/stdc++.h>
using namespace std;

const long long mod = 1e9 + 7;

long long powmod(long long base, long long exp) {
	base %= mod;
	long long result = 1;
	while (exp > 0) {
		if (exp & 1) result = (result * base) % mod;
		base = (base * base) % mod;
		exp >>= 1;
	}
  	return result;
}

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

long long main(){

	vector< vector<long long> > I1 = {{0,1,0}, {0,0,1},{1,0,0}}, I2 = {{0,1,0}, {0,0,1}, {0,1,0}};
	vector< vector<long long> > I3 = {{0,1,0}, {0,0,1}, {0,0,1}}, B1 = {{1},{0},{0}}, B2 = {{0},{1},{0}}, B3 = {{0},{0},{1}};

	Matrix<long long> I1_(I1), I2_(I2), I3_(I3), B1_(B1), B2_(B2), B3_(B3);

	long long n, f1, f2, f3, c; cin >> n >> f1 >> f2 >> f3 >> c;

	I1 = I1^n; I2 = I2^n; I3 = I3^n;
	Matrix<long long> F1 = I1 * B1, F2 = I2 * B2, F3 = I3 * B3;
	long long expf1 = F1[2][0], expf2 = F2[2][0], expf3 = F3[2][0];
	long long r1 = binpow(f1, expf1), r2 = binpow(f2, expf2), r3 = binpow(f3, expf3);
	long long r = (((r1 * r2) % mod) * r3) % mod;


	vector< vector<long long> > Xc_ = {{1,0,0,0,0}, {1,1,0,0,0}, {0,0,0,1,0}, {0,0,0,0,1}, {1,1,1,1,1}};
	vector< vector<long long> > C_ = {{2},{0},{0},{0},{0}};

	Matrix<long long> Xc(Xc_), C(C_)

	Xc = Xc ^ (n - 3);
	C = C * Xc;


	long long expc = C[4][0];
	long long ec = binpow(c, expc);
	r = (r * ec) % mod;
	cout << r << '\n';
	return 0;
}
