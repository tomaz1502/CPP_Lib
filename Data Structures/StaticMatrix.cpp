#include <iostream>
#include <cstddef>
#include <vector>
#include <cassert>
#include <ostream>
#include <algorithm>

template<size_t n_rows, size_t n_cols, typename T>
class Matrix {
    T data[n_rows][n_cols];
    T neutral;
public:
    Matrix(T _neutral = 0) : neutral(_neutral) {}
    Matrix(std::initializer_list<std::vector<T>> IL, T _neutral = 0) : neutral(_neutral) {
        size_t row = 0;
        for (const std::vector<T>& vec: IL) {
            std::copy(vec.begin(), vec.end(), data[row]);
            row++;
        }
    }

    T* operator[](size_t i) {
        return data[i];
    }

    Matrix<n_rows, n_cols, T> operator+(Matrix<n_rows, n_cols, T>& rhs) const {
        Matrix<n_rows, n_cols, T> result(neutral);
        for (size_t i = 0; i < n_rows; i++) {
            for (size_t j = 0; j < n_cols; j++)
                result[i][j] = data[i][j] + rhs[i][j];
        }
        return result;
    }

    template<size_t rhs_cols>
    Matrix<n_rows, rhs_cols, T> operator*(Matrix<n_cols, rhs_cols, T>& rhs) const {
        Matrix<n_rows, rhs_cols, T> result(neutral);
        for (size_t i = 0; i < n_rows; i++) {
            for (size_t j = 0; j < n_cols; j++) {
                T val = neutral;
                for (size_t k = 0; k < n_cols; k++)
                    val += data[i][k] * rhs[k][j];
                result[i][j] = val;
            }
        }
        return result;
    }

    Matrix<n_rows, n_cols, T> operator-(const Matrix<n_rows, n_cols, T>& rhs) {
        Matrix<n_rows, n_cols, T> tmp = -rhs;
        return (*this) + tmp;
    }

    Matrix<n_rows, n_cols, T> operator-() const {
        Matrix<n_rows, n_cols, T> result(neutral);
        for (size_t i = 0; i < n_rows; i++) {
            for (size_t j = 0; j < n_cols; j++)
                result[i][j] = -data[i][j];
        }
        return result;
    }

    void operator+=(Matrix<n_rows, n_cols, T>& rhs) {
        *this = (*this) + rhs;
    }

    template <size_t rhs_cols>
    void operator*=(Matrix<n_cols, rhs_cols, T>& rhs) {
        *this = (*this) * rhs;
    }

    void operator-=(Matrix<n_rows, n_cols, T>& rhs) {
        *this = (*this) - rhs;
    }

    friend std::ostream& operator<<(std::ostream& out, Matrix<n_rows, n_cols, T>& M) {
        for (size_t i = 0; i < n_rows; i++) {
            for (size_t j = 0; j < n_cols; j++) {
                if (j > 0) out << " ";
                out << M[i][j];
            }
            if (i < n_rows - 1) out << "\n";
        }
        return out;
    }

    T operator()(size_t i, size_t j) {
        return data[i][j];
    }

    Matrix<n_cols, n_rows, T> transpose() {
        Matrix<n_cols, n_rows, T> result(neutral);
        for (size_t i = 0; i < n_cols; i++) {
            for (size_t j = 0; j < n_rows; j++)
                result[i][j] = data[j][i];
        }
        return result;
    }
};

int main() {
    Matrix<2, 2 ,int> M = {{1, 2}, {3, 4}};
    Matrix<2, 2, int> N = {{5, 6}, {7, 8}};
    Matrix<2, 2, int> O = M + N;

    Matrix<2, 2, int> P = O;
    P += O;

    Matrix<2, 2, int> Q = P - M;
    Matrix<2, 2, int> R = Q * O;
    Matrix<2, 2, int> S = R;
    S *= M;
    Matrix<2, 2, int> T = -S;

    std::cout << "M\n" << M << "\n";
    std::cout << "N\n" << N << "\n";
    std::cout << "O\n" << O << "\n";
    std::cout << "P\n" << P << "\n";
    std::cout << "Q\n" << Q << "\n";
    std::cout << "R\n" << R << "\n";
    std::cout << "S\n" << S << "\n";
    std::cout << "T\n" << T << "\n";
    return 0;
}
