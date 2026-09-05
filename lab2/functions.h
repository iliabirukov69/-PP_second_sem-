#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdexcept>

namespace mt {
class Matrix {
public:
    Matrix();
    Matrix(int rows, int cols, int value = 0);
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);
    ~Matrix();

    int& at(int i, int j);

    int getRows() const;
    int getCols() const;
    bool isEmpty() const;

    void fill(int value);

    
    std::string toString() const;

private:
    void clear();
    void copyFrom(const Matrix& other);

private:
    int rows_;
    int cols_;
    int** M_;
};
}

#endif // FUNCTIONS_H
