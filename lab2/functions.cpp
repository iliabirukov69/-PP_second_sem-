#include "functions.h"
#include <stdexcept>
#include <string>

namespace mt {

void Matrix::clear() {
    if (M_ != nullptr){
        for (int i = 0; i < rows_; i++) {
            delete[] M_[i];
        }
        delete[] M_;
        M_ = nullptr;
    }
    rows_ = 0;
    cols_ = 0;
}

void Matrix::copyFrom(const Matrix& other){
    rows_ = other.rows_;
    cols_ = other.cols_;

    if (rows_ > 0 && cols_ > 0){
        M_ = new int*[rows_];
        for (int i = 0; i < rows_; i++) {
            M_[i] = new int[cols_];
            for(int j = 0; j < cols_; j++){
                M_[i][j] = other.M_[i][j];
            }
        }
    }
    else {
        M_ = nullptr;
    }
}

Matrix::Matrix() : rows_(0), cols_(0), M_(nullptr) {}

Matrix::Matrix(int rows, int cols, int value) : rows_(rows), cols_(cols) {
    if (rows < 0 || cols < 0) {
        throw std::invalid_argument("Размеры матрицы не могут быть отрицательными");
    }

    if (rows == 0 || cols == 0) {
        M_ = nullptr;
    }
    else {
        M_ = new int*[rows_];
        for (int i = 0; i < rows_; i++) {
            M_[i] = new int[cols_];
            for (int j = 0; j < cols_; j++) {
                M_[i][j] = value;
            }
        }
    }
}

Matrix::Matrix(const Matrix& other) {
    copyFrom(other);
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        clear();
        copyFrom(other);
    }
    return *this;
}

Matrix::~Matrix() {
    clear();
}

int& Matrix::at(int i, int j) {
    if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
        throw std::out_of_range("Индекс выходит за границы матрицы");
    }
    return M_[i][j];
}

int Matrix::getRows() const { return rows_; }
int Matrix::getCols() const { return cols_; }
bool Matrix::isEmpty() const { return rows_ == 0 || cols_ == 0; }

void Matrix::fill(int value) {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            M_[i][j] = value;
        }
    }
}

// Перевод матрицы в стандартную строку для последующего вывода в GUI
std::string Matrix::toString() const {
    if (isEmpty()) {
        return "Матрица пуста\n";
    }

    std::string result = "";
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            result += std::to_string(M_[i][j]) + " ";
        }
        result += "\n";
    }
    return result;
}
}
