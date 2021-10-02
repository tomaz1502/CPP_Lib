#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <vector>

template <size_t n_rows, size_t n_cols, typename T> class Matrix {
protected:
  T data[n_rows][n_cols];
  T neutral;

public:
  Matrix(T _neutral = 0) : neutral(_neutral) {
    std::fill(*data, *data + n_rows * n_cols, neutral);
  }

  Matrix(std::initializer_list<std::vector<T>> IL, T _neutral = 0) {
    *this = Matrix(std::vector<std::vector<T>>(IL), _neutral);
  }

  Matrix(std::vector<std::vector<T>> V, T _neutral = 0)
      : neutral(_neutral) {
    size_t row = 0;
    assert(V.size() == n_rows);
    for (const std::vector<T> &vec : V) {
      assert(vec.size() == n_rows);
      std::copy(vec.begin(), vec.end(), data[row]);
      row++;
    }
  }

  T *operator[](size_t i) { return data[i]; }

  Matrix<n_rows, n_cols, T> operator+(Matrix<n_rows, n_cols, T> &rhs) const {
    Matrix<n_rows, n_cols, T> result(neutral);
    for (size_t i = 0; i < n_rows; i++) {
      for (size_t j = 0; j < n_cols; j++)
        result[i][j] = data[i][j] + rhs[i][j];
    }
    return result;
  }

  template <size_t rhs_cols>
  Matrix<n_rows, rhs_cols, T>
  operator*(Matrix<n_cols, rhs_cols, T> &rhs) const {
    Matrix<n_rows, rhs_cols, T> result(neutral);
    for (size_t i = 0; i < n_rows; i++) {
      for (size_t j = 0; j < rhs_cols; j++) {
        T val = neutral;
        for (size_t k = 0; k < n_cols; k++)
          val += data[i][k] * rhs[k][j];
        result[i][j] = val;
      }
    }
    return result;
  }

  Matrix<n_rows, n_cols, T> operator-(const Matrix<n_rows, n_cols, T> &rhs) {
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

  void operator+=(Matrix<n_rows, n_cols, T> &rhs) { *this = (*this) + rhs; }

  template <size_t rhs_cols> void operator*=(Matrix<n_cols, rhs_cols, T> &rhs) {
    *this = (*this) * rhs;
  }

  void operator-=(Matrix<n_rows, n_cols, T> &rhs) { *this = (*this) - rhs; }

  friend std::ostream &operator<<(std::ostream &out,
                                  Matrix<n_rows, n_cols, T> &M) {
    for (size_t i = 0; i < n_rows; i++) {
      for (size_t j = 0; j < n_cols; j++) {
        if (j > 0)
          out << " ";
        out << M[i][j];
      }
      if (i < n_rows - 1)
        out << "\n";
    }
    return out;
  }

  T operator()(size_t i, size_t j) { return data[i][j]; }

  Matrix<n_cols, n_rows, T> transpose() {
    Matrix<n_cols, n_rows, T> result(neutral);
    for (size_t i = 0; i < n_cols; i++) {
      for (size_t j = 0; j < n_rows; j++)
        result[i][j] = data[j][i];
    }
    return result;
  }
};

template <size_t len, typename T>
struct SquareMatrix : public Matrix<len, len, T> {

  SquareMatrix(T _neutral = 0) : Matrix<len, len, T>(_neutral) {}
  SquareMatrix(std::initializer_list<std::vector<T>> IL, T _neutral = 0)
      : Matrix<len, len, T>(IL, _neutral) {}

  static SquareMatrix<len, T> Identity(T neutral) {
    SquareMatrix Id(neutral);
    for (size_t i = 0; i < len; i++)
      Id[i][i] = 1;
    return Id;
  }

  SquareMatrix<len, T> operator^(int64_t exp) {
    Matrix<len, len, T> result = Identity(this->neutral);
    Matrix<len, len, T> tmp = *this;

    while (exp > 0) {
      if (exp & 1)
        result = result * tmp;
      tmp *= tmp;
      exp >>= 1;
    }

    return static_cast<SquareMatrix &>(result);
  }

  void operator^=(int64_t exp) { *this = (*this) ^ exp; }
};

int main() {

  SquareMatrix<2, int> M = {{1, 2}, {3, 4}};
  M = M ^ 3;
  std::cout << M << "\n";

  return 0;
}
