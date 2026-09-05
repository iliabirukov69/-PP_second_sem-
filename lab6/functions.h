#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QMainWindow>
#include "shape.h"
#include <vector>
#include <QString>

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
    void on_choice_figure_textActivated(const QString &arg1);
    void on_par_1_textChanged(const QString &arg1);
    void on_par_2_textChanged(const QString &arg1);
    void on_par_3_textChanged(const QString &arg1);
    void on_num_textChanged(const QString &arg1);
    void on_input_clicked();
    void on_clear_clicked();
    void on_inf_clicked();
    void on_back_clicked();
    void on_sort_area_clicked();
    void on_sort_perimeter_clicked();

private:
    void error();
    bool error_par(QString s);
    bool error_triangle();

    Ui::MainWindow *ui;
    std::vector<Shape*> shapes;
    int shape_bool = 0;
    bool er = 0;
};

#endif // FUNCTIONS_H
