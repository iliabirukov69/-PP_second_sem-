#include <QApplication>
#include <QMessageBox>
#include <QInputDialog>
#include <QString>
#include "functions.h"

using namespace mt;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    bool okRows, okCols;

    
    int rows = QInputDialog::getInt(
        nullptr,
        "Ввод данных",
        "Введите количество строк матрицы:",
        3, 1, 100, 1, &okRows
        );

    if (!okRows) return 0;

    
    int cols = QInputDialog::getInt(
        nullptr,
        "Ввод данных",
        "Введите количество столбцов матрицы:",
        3, 1, 100, 1, &okCols
        );

    if (!okCols) return 0;

    try {
        
        Matrix m1(rows, cols, 0);
        m1.fill(3);

        Matrix m2(rows, cols, 6);
        m2.at(0, 0) = 5;

        m1 = m1;

        Matrix m3 = m2; 

        
        QString output = "";

        output += "Матрица m1 (заполнена 3):\n" + QString::fromStdString(m1.toString()) + "\n";
        output += "Матрица m2 (заполнена 6, элемент [0][0]=5):\n" + QString::fromStdString(m2.toString()) + "\n";
        output += "Матрица m3 (копия m2):\n" + QString::fromStdString(m3.toString()) + "\n";

        m3 = m1;
        output += "Матрица m3 (после m3 = m1):\n" + QString::fromStdString(m3.toString()) + "\n";

        Matrix m4(5, 6, 7);
        m2 = m1 = m4;

        output += "--- Результаты каскадного присваивания (m2 = m1 = m4) ---\n";
        output += "Матрица m4 (размер 5х6, заполнена 7):\n" + QString::fromStdString(m4.toString()) + "\n";
        output += "Матрица m1 (стала как m4):\n" + QString::fromStdString(m1.toString()) + "\n";
        output += "Матрица m2 (стала как m4):\n" + QString::fromStdString(m2.toString()) + "\n";

        
        QMessageBox::information(nullptr, "Лабораторная работа — Матрицы", output);

    } catch(const std::invalid_argument& ex) {
        QMessageBox::critical(nullptr, "Ошибка данных", QString("Ошибка: %1").arg(ex.what()));
    } catch(const std::out_of_range& ex) {
        QMessageBox::critical(nullptr, "Ошибка индекса", QString("Ошибка: %1").arg(ex.what()));
    }

    return 0;
}


