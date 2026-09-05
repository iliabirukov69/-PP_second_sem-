#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <stdexcept>

namespace mt {
class Matrix_t {
public:
    Matrix_t();
    Matrix_t(int rows, int cols, int value = 0);
    Matrix_t(const Matrix_t& other);
    Matrix_t& operator=(const Matrix_t& other);
    ~Matrix_t();

    int& at(int i, int j);
    int getRows() const;
    int getCols() const;
    bool isEmpty() const;
    void fill(int value);

    Matrix_t operator+(const Matrix_t& other) const;
    Matrix_t operator*(int scalar) const;
    Matrix_t& operator++();
    Matrix_t operator++(int);

private:
    void clear();
    void copyFrom(const Matrix_t& other);

private:
    int rows_;
    int cols_;
    int** M_;
};
}

QT_BEGIN_NAMESPACE
namespace Ui {
class Matrix;
}
QT_END_NAMESPACE

class Matrix : public QMainWindow
{
    Q_OBJECT

public:
    Matrix(QWidget *parent = nullptr);
    ~Matrix();

    void print_M(mt::Matrix_t& M);

private slots:
    void on_Matrix_A_cellChanged(int row, int column);
    void on_Matrix_B_cellChanged(int row, int column);
    void on_r_c_input_button_clicked();
    void on_rows_input_textChanged(const QString &arg1) {}
    void on_cols_input_textChanged(const QString &arg1) {}
    void on_choice_A_clicked();
    void on_choice_B_clicked();
    void on_operator_ink_1_clicked();
    void on_operator_ink_2_clicked();
    void on_number_to_mult_textChanged(const QString &arg1);
    void on_mult_n_M_clicked();
    void on_add_M_clicked();
    void on_clear_out_clicked();
    void on_clear_all_clicked();

private:
    void initializeTables();

    Ui::Matrix *ui;
    int rows_M;
    int cols_M;
    int n;
    bool flag;
    bool ch_M;
    mt::Matrix_t A;
    mt::Matrix_t B;
};

#endif
