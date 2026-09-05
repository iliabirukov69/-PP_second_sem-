#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QMainWindow>
#include <string>
#include <vector>

class BigInt {
private:
    std::vector<int> digits;

    void trim();

public:
    BigInt();
    BigInt(std::string str);
    BigInt(long long num);

    std::string toString() const;

    bool operator==(const BigInt& other) const;
    bool operator<(const BigInt& other) const;
    bool operator>(const BigInt& other) const;

    BigInt operator+(const BigInt& other) const;
    BigInt operator*(const BigInt& other) const;
};

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_number_A_textChanged(const QString &arg1);
    void on_number_B_textChanged(const QString &arg1);
    void on_input_clicked();
    void on_plus_clicked();
    void on_minus_clicked() {}
    void on_mult_clicked();
    void on_div_clicked() {}
    void on_pushButton_clicked() {}
    void on_pushButton_2_clicked();
    void on_pow_clicked() {}
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    std::string strA;
    std::string strB;
    BigInt a;
    BigInt b;
    bool a_valid = false;
    bool b_valid = false;
};

#endif // FUNCTIONS_H
