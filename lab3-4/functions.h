#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Cub;
}
QT_END_NAMESPACE

class Cub : public QMainWindow
{
    Q_OBJECT

public:
    Cub(QWidget *parent = nullptr, float side_cub = 1);
    ~Cub();

private slots:
    void on_Edit_side_cub_textChanged(const QString &arg1);
    void on_input_side_clicked();
    void on_Area_calculate_clicked();
    void on_Volume_calculate_clicked();
    void on_diag_calculate_clicked();

private:
    bool is_side_cub_valid_(float side_cub);
    void calculate_S_cub();
    void calculate_V_cub();
    void calculate_diag_cub();
    void Clear();

private:
    Ui::Cub *ui;
    float side_cub_ = 0.0f;
    float S_cub_ = 0.0f;
    float V_cub_ = 0.0f;
    float diag_cub_ = 0.0f;
    QString q_side = "";
    QString q_Area = "";
    QString q_Volume = "";
    QString q_diag = "";
};
#endif // FUNCTIONS_H
