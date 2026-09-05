#include "functions.h"
#include "./ui_matrix.h"
#include <QTableWidgetItem>
#include <QString>
#include <cmath>
#include <stdexcept>

namespace mt {

void Matrix_t::clear() {
    if (M_ != nullptr) {
        for (int i = 0; i < rows_; i++) {
            delete[] M_[i];
        }
        delete[] M_;
        M_ = nullptr;
    }
    rows_ = 0;
    cols_ = 0;
}

void Matrix_t::copyFrom(const Matrix_t& other) {
    rows_ = other.rows_;
    cols_ = other.cols_;
    if (rows_ > 0 && cols_ > 0) {
        M_ = new int*[rows_];
        for (int i = 0; i < rows_; i++) {
            M_[i] = new int[cols_];
            for (int j = 0; j < cols_; j++) {
                M_[i][j] = other.M_[i][j];
            }
        }
    } else {
        M_ = nullptr;
    }
}

Matrix_t::Matrix_t() : rows_(0), cols_(0), M_(nullptr) {}

Matrix_t::Matrix_t(int rows, int cols, int value) : rows_(rows), cols_(cols) {
    if (rows < 0 || cols < 0) {
        throw std::invalid_argument("Размеры матрицы не могут быть отрицательными");
    }
    if (rows == 0 || cols == 0) {
        M_ = nullptr;
    } else {
        M_ = new int*[rows_];
        for (int i = 0; i < rows_; i++) {
            M_[i] = new int[cols_];
            for (int j = 0; j < cols_; j++) {
                M_[i][j] = value;
            }
        }
    }
}

Matrix_t::Matrix_t(const Matrix_t& other) {
    copyFrom(other);
}

Matrix_t& Matrix_t::operator=(const Matrix_t& other) {
    if (this != &other) {
        clear();
        copyFrom(other);
    }
    return *this;
}

Matrix_t::~Matrix_t() {
    clear();
}

int& Matrix_t::at(int i, int j) {
    if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
        throw std::out_of_range("Индекс выходит за границы матрицы");
    }
    return M_[i][j];
}

int Matrix_t::getRows() const { return rows_; }
int Matrix_t::getCols() const { return cols_; }
bool Matrix_t::isEmpty() const { return rows_ == 0 || cols_ == 0; }

void Matrix_t::fill(int value) {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            M_[i][j] = value;
        }
    }
}

Matrix_t Matrix_t::operator+(const Matrix_t& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Размеры матриц должны совпадать для сложения");
    }
    Matrix_t result(rows_, cols_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            result.M_[i][j] = this->M_[i][j] + other.M_[i][j];
        }
    }
    return result;
}

Matrix_t Matrix_t::operator*(int scalar) const {
    Matrix_t result(rows_, cols_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            result.M_[i][j] = this->M_[i][j] * scalar;
        }
    }
    return result;
}

Matrix_t& Matrix_t::operator++() {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            M_[i][j] += 1;
        }
    }
    return *this;
}

Matrix_t Matrix_t::operator++(int) {
    Matrix_t temp(*this);
    ++(*this);
    return temp;
}
}

Matrix::Matrix(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Matrix)
    , rows_M(3)
    , cols_M(3)
    , ch_M(1)
    , n(0)
    , flag(1)
    , A(rows_M, cols_M, 0)
    , B(rows_M, cols_M, 0)
{
    ui->setupUi(this);
    initializeTables();
}

Matrix::~Matrix()
{
    delete ui;
}

void Matrix::initializeTables() {
    ui->Matrix_A->setRowCount(rows_M);
    ui->Matrix_A->setColumnCount(cols_M);
    ui->Matrix_B->setRowCount(rows_M);
    ui->Matrix_B->setColumnCount(cols_M);
    ui->out_M->setRowCount(rows_M);
    ui->out_M->setColumnCount(cols_M);
    for (int i = 0; i < rows_M; i++) {
        for (int j = 0; j < cols_M; j++) {
            ui->Matrix_A->setItem(i, j, new QTableWidgetItem("0"));
            ui->Matrix_B->setItem(i, j, new QTableWidgetItem("0"));
            ui->out_M->setItem(i, j, new QTableWidgetItem(""));
        }
    }
    ui->inf->addItem("Программа запущена. Выбрана матрица A");
}

void Matrix::on_Matrix_A_cellChanged(int row, int column)
{
    bool ok;
    QTableWidgetItem* item = ui->Matrix_A->item(row, column);
    if (item) {
        A.at(row, column) = item->text().toInt(&ok);
        if (!ok){
            ui->inf->addItem("Ошибка: введите число");
        }
    }
}

void Matrix::on_Matrix_B_cellChanged(int row, int column)
{
    bool ok;
    QTableWidgetItem* item = ui->Matrix_B->item(row, column);
    if (item) {
        B.at(row, column) = item->text().toInt(&ok);
        if (!ok){
            ui->inf->addItem("Ошибка: введите число");
        }
    }
}

void Matrix::on_r_c_input_button_clicked()
{
    int rows = ui->rows_input->text().toInt();
    int cols = ui->cols_input->text().toInt();

    if (rows <= 0 || cols <= 0) {
        ui->inf->addItem("Ошибка: размерности должны быть положительными");
        return;
    }
    mt::Matrix_t C1(rows, cols, 0);
    mt::Matrix_t C2(rows, cols, 0);
    int min_r = std::min(rows, rows_M);
    int min_c = std::min(cols, cols_M);
    for (int i = 0; i < min_r; i++) {
        for (int j = 0; j < min_c; j++) {
            C1.at(i, j) = A.at(i, j);
            C2.at(i, j) = B.at(i, j);
        }
    }
    A = C1;
    B = C2;

    rows_M = rows;
    cols_M = cols;

    ui->Matrix_A->setRowCount(rows);
    ui->Matrix_A->setColumnCount(cols);
    ui->Matrix_B->setRowCount(rows);
    ui->Matrix_B->setColumnCount(cols);
    ui->out_M->setRowCount(rows);
    ui->out_M->setColumnCount(cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!ui->Matrix_A->item(i, j)) {
                ui->Matrix_A->setItem(i, j, new QTableWidgetItem("0"));
            }
            if (!ui->Matrix_B->item(i, j)) {
                ui->Matrix_B->setItem(i, j, new QTableWidgetItem("0"));
            }
            if (!ui->out_M->item(i, j)) {
                ui->out_M->setItem(i, j, new QTableWidgetItem(""));
            }
        }
    }
}

void Matrix::print_M(mt::Matrix_t& M){
    if (&M == &A){
        for (int i = 0; i < rows_M; i++) {
            for (int j = 0; j < cols_M; j++) {
                ui->Matrix_A->item(i, j)->setText(QString::number(M.at(i, j)));
            }
        }
    }
    else{
        for (int i = 0; i < rows_M; i++) {
            for (int j = 0; j < cols_M; j++) {
                ui->Matrix_B->item(i, j)->setText(QString::number(M.at(i, j)));
            }
        }
    }
}

void Matrix::on_choice_A_clicked()
{
    ch_M = 1;
    ui->inf->addItem("Выбрана матрица А");
}

void Matrix::on_choice_B_clicked()
{
    ch_M = 0;
    ui->inf->addItem("Выбрана матрица В");
}

void Matrix::on_operator_ink_1_clicked()
{
    if(ch_M){
        A++;
        print_M(A);
    }
    else{
        B++;
        print_M(B);
    }
}

void Matrix::on_operator_ink_2_clicked()
{
    if(ch_M){
        ++A;
        print_M(A);
    }
    else{
        ++B;
        print_M(B);
    }
}

void Matrix::on_number_to_mult_textChanged(const QString &arg1)
{
    n = ui->number_to_mult->text().toInt(&flag);
}

void Matrix::on_mult_n_M_clicked()
{
    if (flag) {
        if(ch_M){
            mt::Matrix_t C = A*n;
            for (int i = 0; i < rows_M; i++) {
                for (int j = 0; j < cols_M; j++) {
                    ui->Matrix_A->item(i, j)->setText(QString::number(C.at(i, j)));
                }
            }
        }
        else{
            mt::Matrix_t C = B*n;
            for (int i = 0; i < rows_M; i++) {
                for (int j = 0; j < cols_M; j++) {
                    ui->Matrix_B->item(i, j)->setText(QString::number(C.at(i, j)));
                }
            }
        }
    }
    else{
        ui->inf->addItem("Ошибка: введите число");
    }
}

void Matrix::on_add_M_clicked(){
    try {
        mt::Matrix_t C = A+B;
        for (int i = 0; i < rows_M; i++) {
            for (int j = 0; j < cols_M; j++) {
                ui->out_M->item(i, j)->setText(QString::number(C.at(i, j)));
            }
        }
    } catch(const std::exception& e) {
        ui->inf->addItem(e.what());
    }
}

void Matrix::on_clear_out_clicked(){
    ui->inf->clear();
    for (int i = 0; i < rows_M; i++) {
        for (int j = 0; j < cols_M; j++) {
            if(ui->out_M->item(i, j)) ui->out_M->item(i, j)->setText("");
        }
    }
}

void Matrix::on_clear_all_clicked(){
    ui->inf->clear();
    for (int i = 0; i < rows_M; i++) {
        for (int j = 0; j < cols_M; j++) {
            if(ui->out_M->item(i, j)) ui->out_M->item(i, j)->setText("");
            if(ui->Matrix_A->item(i, j)) ui->Matrix_A->item(i, j)->setText("0");
            if(ui->Matrix_B->item(i, j)) ui->Matrix_B->setItem(i, j, new QTableWidgetItem("0"));
            A.at(i, j) = 0;
            B.at(i, j) = 0;
        }
    }
    ui->number_to_mult->clear();
    ui->rows_input->clear();
    ui->cols_input->clear();
}
