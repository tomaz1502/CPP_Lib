#include <vector>
#include <iostream>
#include <cassert>
#include <iomanip>

template<typename T>
struct Matrix : std::vector<std::vector<T>> {
    T neutral;
    int rows;
    int cols;

    Matrix() { }
    Matrix(std::initializer_list<std::vector<T>> IL) : std::vector<std::vector<T>>(IL) { SetDims(); }
    Matrix(std::vector<std::vector<T>>&& v) : std::vector<std::vector<T>>(v) { SetDims(); }
    Matrix(int _rows, int _cols, T _neutral = 0) : std::vector<std::vector<T>>(_rows, std::vector<T>(_cols, _neutral)) { SetDims(_neutral); }

    void SetDims(T _neutral = 0) {
        rows = this->size();
        cols = (*this)[0].size();
        neutral  = _neutral;
    }

    Matrix<T> operator+(const Matrix<T> &M) const {
        Matrix<T> ret = Matrix(rows, cols);
        assert(rows == M.rows && cols == M.cols);

        for (int i = 0; i < rows; ++i) {
            for(int j = 0; j < cols; ++j){
                ret[i][j] = (*this)[i][j] + M[i][j];
            }
        }

        return ret;
    }

    Matrix<T> operator*(const Matrix<T> &M) const {
        assert(cols == M.rows);
        Matrix<T> ret = Matrix(rows, M.cols);

        for (int i = 0; i < M.rows; ++i) {
            for (int j = 0; j < M.cols; ++j) {
                T c = neutral;
                for (int k = 0; k < M.rows; ++k) c = (c + (*this)[i][k] * M[k][j]);
                ret[i][j] = c;
            }
        }

        return ret;
    }

    Matrix<T> neg() {
        Matrix<T> ret(*this);

        for (int i = 0; i < this->size(); i++) {
            for (int j = 0; j < (*this)[i].size(); j++) ret[i][j] *= -1;
        }

        return ret;
    }

    void operator+=(Matrix<T> M) { *this = *this + M; }
    void operator-=(Matrix<T> M) { *this = *this + M.neg(); }
    void operator*=(Matrix<T> M) { *this = *this * M; }
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& M) {
    for (int i = 0; i < M.rows; i++) {
        for (int j = 0; j < M.cols; j++) out << M[i][j] << " ";
        out << "\n";
    }
    return out;
}

template<typename T>
struct SquareMatrix: Matrix<T> {
    SquareMatrix(int len) : Matrix<T>(len, len) {}
    SquareMatrix(std::initializer_list<std::vector<T>> il) : Matrix<T>(il) {
        assert(this->rows == this->cols);
    }

    SquareMatrix<T> Identity(int len) {
        SquareMatrix Id(len);
        for (int i = 0; i < len; i++) Id[i][i] = 1;
        return Id;
    }

    SquareMatrix<T> operator^(int exp) {
        Matrix<T> ret = Identity(this->rows);
        Matrix<T> temp = SquareMatrix<T>(*this);

        while (exp) {
            if (exp & 1) ret = ret * temp;
            temp = temp * temp;
            exp >>= 1;
        }

        return static_cast<SquareMatrix&>(ret);
    }

    void operator^=(int exp) { *this = (*this) ^ exp; }
};

// example usage
// from: https://codeforces.com/gym/102644/problem/A
int main() {
    std::ios::sync_with_stdio(false);
    std::cout << std::fixed << std::setprecision(9);

    int n;
    double p;
    std::cin >> n >> p;
    n++;

    Matrix<double> B = {{1.0},
                        {0.0},
                        {1.0},
                        {0.0}};
    SquareMatrix<double> Rec = {{1.0 - p, p, 0.0, 0.0},
                                {p, 1.0 - p, 0.0, 0.0},
                                {0.0, 0.0, 1.0 - p, p},
                                {0.0, 0.0, p, 1.0 - p}};

    Rec ^= (n - 1);
    // std::cout << Rec.size() << " x " << Rec[0].size() << "\n";
    // std::cout << B.size() << " x " << B[0].size() << "\n";
    Matrix<double> answer = Rec * B;

    std::cout << answer[0][0] << "\n";
    return 0;
}
