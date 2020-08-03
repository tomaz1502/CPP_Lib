#include <iostream>
#include <cstddef>
#include <vector>
#include <cassert>
#include <ostream>
#include <algorithm>

template<typename T>
class Matrix {
    T** data;
    size_t rows, cols;
    T neutral;

public:
    Matrix();
    Matrix(const Matrix<T>&);
    Matrix(size_t, size_t, T = 0);
    Matrix(std::initializer_list<std::vector<T>>, T = 0);
    
    ~Matrix();

    void allocate();

    Matrix<T>& operator=(const Matrix<T>& rhs) {
        if (rows == 0 && cols == 0) {
            rows = rhs.rows;
            cols = rhs.cols;
            neutral = rhs.neutral;
            allocate();
        }
        assert(this->rows == rhs.rows);
        assert(this->cols == rhs.cols);

        for (size_t i = 0; i < rows; ++i)
            std::copy(rhs.data[i], rhs.data[i] + cols, data[i]);

        return *this;
    }

    T* operator[](size_t i) {
        return data[i];
    }

    Matrix<T> operator+(Matrix<T>& rhs) const {
        Matrix<T> result(rows, cols, neutral);
        assert(rows == rhs.rows);
        assert(cols == rhs.cols);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++)
                result[i][j] = data[i][j] + rhs[i][j];
        }
        return result;
    }

    Matrix<T> operator*(Matrix<T>& rhs) const {
        Matrix<T> result(rows, cols, neutral);
        assert(rows == rhs.cols);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                T val = neutral;
                for (size_t k = 0; k < cols; k++)
                    val += data[i][k] * rhs[k][j];
                result[i][j] = val;
            }
        }
        return result;
    }

    Matrix<T> operator-(const Matrix<T>& rhs) {
        Matrix<int> tmp = -rhs;
        return (*this) + tmp;
    }

    Matrix<T> operator-() const {
        Matrix<T> result(rows, cols, neutral);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++)
                result[i][j] = -data[i][j];
        }
        return result;
    }

    void operator+=(Matrix<T>& rhs) {
        *this = (*this) + rhs;
    }

    void operator*=(Matrix<T>& rhs) {
        *this = (*this) * rhs;
    }

    void operator-=(Matrix<T>& rhs) {
        *this = (*this) - rhs;
    }

    friend std::ostream& operator<<(std::ostream& out, Matrix<T>& M) {
        for (size_t i = 0; i < M.rows; i++) {
            for (size_t j = 0; j < M.cols; j++) {
                if (j > 0) out << " ";
                out << M[i][j];
            }
            if (i < M.rows - 1) out << "\n";
        }
        return out;
    }

    T operator()(size_t i, size_t j) {
        return data[i][j];
    }
};

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& rhs) {
    rows = rhs.rows;
    cols = rhs.cols;
    neutral = rhs.neutral;
    allocate();
    *this = rhs;
}


template <typename T>
Matrix<T>::Matrix(): rows(0), cols(0) { }

template <typename T>
Matrix<T>::Matrix(size_t _rows, size_t _cols, T _neutral) :
       rows(_rows), cols(_cols), neutral(_neutral) {
    this->allocate();     
}

template <typename T>
Matrix<T>::Matrix(std::initializer_list<std::vector<T>> IL, T _neutral) {
    neutral = _neutral;
    rows = IL.size();
    cols = IL.begin()->size();
    this->allocate();
    size_t row = 0;
    for (const std::vector<T>& vec: IL) {
        assert(vec.size() == cols);
        std::copy(vec.begin(), vec.end(), data[row]);
        row++;
    }
}

template <typename T>
Matrix<T>::~Matrix() {
    if (rows > 0 && cols > 0) {
        for (size_t i = 0; i < rows; i++)
            delete[] data[i];
        delete[] data;
    }
}

template <typename T>
void Matrix<T>::allocate() {
    data = new T*[rows];
    for (size_t i = 0; i < rows; i++) {
        data[i] = new T[cols];
        std::fill_n(data[i], cols, neutral);
    }
}


int main() {
    Matrix<int> M = {{1, 2}, {3, 4}};
    Matrix<int> N = {{5, 6}, {7, 8}};
    Matrix<int> O = M + N;

    Matrix<int> P = O;
    P += O;

    Matrix<int> Q = P - M;
    Matrix<int> R = Q * O;
    Matrix<int> S = R;
    S *= M;
    Matrix<int> T = -S;

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