#include <functional> // function
#include <iostream> // output on main
#include <vector>
#include <ostream>

template<int n_rows, int n_cols, typename T>
class Matrix {
public:
    std::function<T(int, int)> get;
    T neutral;

    Matrix(T _neutral = 0) : neutral(_neutral) { }

    Matrix(std::function<T(int, int)> _get, T _neutral = 0) :
      get(_get), neutral(_neutral) { }

    Matrix<n_rows, n_cols, T> transpose() {
        auto get_flipped = [&] (int i, int j) { return this->get(j, i); };
        return Matrix(get_flipped, this->neutral);
    }

    void set_get(std::function<T(int,int)> _get) {
        get = _get;
    }

    friend std::ostream& operator<<(std::ostream& out, Matrix<n_rows, n_cols, T>& M) {
        for (int i = 0; i < n_rows; i++) {
            for (int j = 0; j < n_cols; j++) {
                if (j > 0) out << " ";
                out << M.get(i, j);
            }
            if (i < n_rows - 1) out << "\n";
        }
        return out;
    }
};

template<int n_rows, int n_cols, typename T>
class ExplicitMatrix : public Matrix<n_rows, n_cols, T> {
    T data[n_rows][n_cols];
public:

    std::function<T(int,int)> default_get = [&] (int i, int j) { return data[i][j]; };

    ExplicitMatrix(T _neutral = 0) :
      Matrix<n_rows, n_cols, T>([&](int i, int j) { return data[i][j]; }, _neutral) {
        std::fill(*data, *data + n_rows * n_cols, _neutral);
        this->set_get(default_get);
    }

    ExplicitMatrix(std::initializer_list<std::vector<T>> IL, T _neutral = 0) :
      Matrix<n_rows, n_cols, T>(_neutral) {
        int row = 0;
        for (const std::vector<T>& vec: IL) {
            std::copy(vec.begin(), vec.end(), data[row]);
            row++;
        }
        this->set_get(default_get);
    }

    ExplicitMatrix operator=(ExplicitMatrix<n_rows, n_cols, T> rhs) {
        for (int i = 0; i < n_rows; i++)
            for (int j = 0; j < n_cols; j++)
                data[i][j] = rhs.get(i, j);
        
        this->set_get(default_get);
        this->neutral = rhs.neutral;
        return *this;
    }

    ExplicitMatrix(ExplicitMatrix<n_rows, n_cols, T>& rhs) : Matrix<n_rows, n_cols, T>(rhs.neutral) {
        for (int i = 0; i < n_rows; i++)
            for (int j = 0; j < n_cols; j++)
                data[i][j] = rhs.get(i, j);
        this->set_get(default_get);
    }

    ExplicitMatrix(ExplicitMatrix<n_rows, n_cols, T>&& rhs) {
        for (int i = 0; i < n_rows; i++)
            for (int j = 0; j < n_cols; j++)
                data[i][j] = rhs.get(i, j);
        this->set_get(default_get);
    }

    T* operator[](int i) {
        return data[i];
    }

    T& operator()(int i, int j) {
        return data[i][j];
    }

    void set(int i, int j, const T& val) {
        data[i][j] = val;
    }

    ExplicitMatrix<n_rows, n_cols, T> operator+(Matrix<n_rows, n_cols, T>& rhs) {
        ExplicitMatrix<n_rows, n_cols, T> result(this->neutral);
        for (int i = 0; i < n_rows; i++) {
            for (int j = 0; j < n_cols; j++) {
                T val = this->get(i, j) + rhs.get(i, j);
                result.set(i, j, val);
            }
        }
        return result;
    }

    template<int rhs_cols>
    ExplicitMatrix<n_rows, rhs_cols, T> operator*(Matrix<n_cols, rhs_cols, T>& rhs) {
        ExplicitMatrix<n_rows, rhs_cols, T> result(this->neutral);
        for (int i = 0; i < n_rows; i++) {
            for (int j = 0; j < rhs_cols; j++) {
                T val = this->neutral;
                for (int k = 0; k < n_cols; k++)
                    val += this->get(i, k) * rhs.get(k, j);
                result.set(i,j,val);
            }
        }
        return result;
    }

    Matrix<n_rows, n_cols, T> operator-(const Matrix<n_rows, n_cols, T>& rhs) {
        Matrix<n_rows, n_cols, T> tmp = -rhs;
        return (*this) + tmp;
    }

    ExplicitMatrix<n_rows, n_cols, T> operator-() {
        ExplicitMatrix<n_rows, n_cols, T> result(this->neutral);
        for (int i = 0; i < n_rows; i++) {
            for (int j = 0; j < n_cols; j++)
                result.set(i, j, -this->get(i, j));
        }
        return result;
    }

    void operator+=(Matrix<n_rows, n_cols, T>& rhs) {
        *this = (*this) + rhs;
    }

    template <int rhs_cols>
    void operator*=(Matrix<n_cols, rhs_cols, T>& rhs) {
        *this = (*this) * rhs;
    }

    void operator-=(Matrix<n_rows, n_cols, T>& rhs) {
        *this = (*this) - rhs;
    }
};

template<int len, typename T>
class SquareMatrix: public ExplicitMatrix<len, len, T> {
public:
    SquareMatrix(T _neutral = 0) :
      ExplicitMatrix<len, len, T>(_neutral) {}

    SquareMatrix(std::initializer_list<std::vector<T>> IL, T _neutral = 0) :
      ExplicitMatrix<len, len, T>(IL, _neutral) { }

    SquareMatrix<len, T> operator^(int64_t exp) {
        if (exp == 0) {
            SquareMatrix<len, T> answer(this->neutral);
            for (int i = 0; i < len; ++i)
                answer.set(i, i, 1);
            return answer;
        }

        auto mid_result = (*this) ^ (exp / 2);
        auto result = mid_result * mid_result;
        if (exp % 2 == 1)
            result *= (*this);
        return static_cast<SquareMatrix&>(result);
    }

    void operator^=(int64_t exp) {
        *this = (*this) ^ exp;
    }
};

int main() {

    ExplicitMatrix<2,2,int> M = {{1,2},
                                 {3,4}};

    auto N = Matrix<2,2,int>([&](int i, int j) { return i == j; });
    std::cout << N << "\n";
 
    auto P = M * N;
    std::cout << P << "\n";

    SquareMatrix<2,int> SM = {{1,2},
                              {3,4}};

    SM = SM ^ 1;

    std::cout << SM << "\n";

    Matrix<2,2,int> IT = N.transpose();
    std::cout << IT << "\n";

    return 0;
}
