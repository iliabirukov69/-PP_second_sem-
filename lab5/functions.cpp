#include "functions.h"
#include "./ui_mainwindow.h"
#include <QString>
#include <algorithm>

void BigInt::trim() {
    while (digits.size() > 1 && digits.back() == 0) {
        digits.pop_back();
    }
}

BigInt::BigInt() {
    digits.push_back(0);
}

BigInt::BigInt(std::string str) {
    if (str.empty()) {
        digits.push_back(0);
        return;
    }
    if (!std::all_of(str.begin(), str.end(), ::isdigit)) {
        throw std::invalid_argument("Invalid BigInt format");
    }
    for (int i = str.length() - 1; i >= 0; --i) {
        digits.push_back(str[i] - '0');
    }
    trim();
}

BigInt::BigInt(long long num) {
    if (num <= 0) {
        digits.push_back(0);
    } else {
        while (num > 0) {
            digits.push_back(num % 10);
            num /= 10;
        }
    }
}

std::string BigInt::toString() const {
    std::string str = "";
    for (int i = digits.size() - 1; i >= 0; --i) {
        str += std::to_string(digits[i]);
    }
    return str;
}

bool BigInt::operator==(const BigInt& other) const {
    return digits == other.digits;
}

bool BigInt::operator<(const BigInt& other) const {
    if (digits.size() != other.digits.size()) {
        return digits.size() < other.digits.size();
    }
    for (int i = digits.size() - 1; i >= 0; --i) {
        if (digits[i] != other.digits[i]) {
            return digits[i] < other.digits[i];
        }
    }
    return false;
}

bool BigInt::operator>(const BigInt& other) const {
    return other < *this;
}

BigInt BigInt::operator+(const BigInt& other) const {
    BigInt result;
    result.digits.clear();
    int carry = 0;
    size_t n = std::max(digits.size(), other.digits.size());
    for (size_t i = 0; i < n || carry; ++i) {
        int sum = carry;
        if (i < digits.size()) sum += digits[i];
        if (i < other.digits.size()) sum += other.digits[i];
        result.digits.push_back(sum % 10);
        carry = sum / 10;
    }
    result.trim();
    return result;
}

BigInt BigInt::operator*(const BigInt& other) const {
    BigInt result;
    result.digits.assign(digits.size() + other.digits.size(), 0);
    for (size_t i = 0; i < digits.size(); ++i) {
        int carry = 0;
        for (size_t j = 0; j < other.digits.size() || carry; ++j) {
            long long cur = result.digits[i + j] + 1LL * digits[i] * (j < other.digits.size() ? other.digits[j] : 0) + carry;
            result.digits[i + j] = cur % 10;
            carry = cur / 10;
        }
    }
    result.trim();
    return result;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_number_A_textChanged(const QString &arg1) {
    strA = arg1.toStdString();
}

void MainWindow::on_number_B_textChanged(const QString &arg1) {
    strB = arg1.toStdString();
}

void MainWindow::on_input_clicked() {
    try {
        a = BigInt(strA);
        b = BigInt(strB);
        a_valid = true;
        b_valid = true;
        ui->inf->addItem("Числа загружены: " + QString::fromStdString(strA) + " и " + QString::fromStdString(strB));
    } catch (const std::exception& e) {
        ui->inf->addItem("Ошибка: введите корректные числа");
        a_valid = false;
        b_valid = false;
    }
}

void MainWindow::on_plus_clicked() {
    if (!a_valid || !b_valid) {
        ui->inf->addItem("Сначала нажмите input");
        return;
    }
    try {
        BigInt result = a + b;
        QString res = QString::fromStdString(result.toString());
        ui->inf->addItem(res);
    } catch (const std::exception& e) {
        ui->inf->addItem("Ошибка при сложении");
    }
}

void MainWindow::on_mult_clicked() {
    if (!a_valid || !b_valid) {
        ui->inf->addItem("Сначала нажмите input");
        return;
    }
    try {
        BigInt result = a * b;
        QString res = QString::fromStdString(result.toString());
        ui->inf->addItem(res);
    } catch (const std::exception& e) {
        ui->inf->addItem("Ошибка при умножении");
    }
}

void MainWindow::on_pushButton_2_clicked() {
    ui->inf->clear();
}

void MainWindow::on_pushButton_3_clicked() {
    if (!a_valid || !b_valid) {
        ui->inf->addItem("Сначала нажмите input");
        return;
    }
    try {
        if (a > b) {
            ui->inf->addItem("A больше B");
        } else if (a < b) {
            ui->inf->addItem("A меньше B");
        } else {
            ui->inf->addItem("A равно B");
        }
    } catch (const std::exception& e) {
        ui->inf->addItem("Ошибка при сравнении");
    }
}

void MainWindow::on_pushButton_4_clicked() {
    ui->inf->clear();
    ui->number_A->clear();
    ui->number_B->clear();
    a_valid = false;
    b_valid = false;
}
