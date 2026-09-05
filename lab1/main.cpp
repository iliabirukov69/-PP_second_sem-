#include <QApplication>
#include <QMessageBox>
#include <QInputDialog>
#include <QString>
#include "functions.h"

int main(int argc, char *argv[]) {
    

    QApplication a(argc, argv);

    
    while (true) {
        bool ok;

       
        double userSide = QInputDialog::getDouble(
            nullptr,
            "Лабораторная 1 - Ввод",
            "Введите длину стороны квадрата\n(или нажмите Cancel для выхода):",
            5.0,     
            0.001,
            100000.0,
            3,       
            &ok
            );

        
        if (!ok) {
            break;
        }

        try {
           
            Square mySquare(userSide);

            
            QString resultText = QString(
                                     "--- Результаты вычислений ---\n\n"
                                     "Сторона:       %1\n"
                                     "Площадь:       %2\n"
                                     "Периметр:      %3\n"
                                     "Диагональ:     %4\n\n"
                                     "Хотите рассчитать другой квадрат?"
                                     )
                                     .arg(mySquare.getSide())
                                     .arg(mySquare.calculateArea())
                                     .arg(mySquare.calculatePerimeter())
                                     .arg(mySquare.calculateDiagonal());

            
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(nullptr, "Лабораторная 1 - Успех", resultText,
                                          QMessageBox::Yes | QMessageBox::No);

            
            if (reply == QMessageBox::No) {
                break;
            }

        } catch (const std::exception& e) {
            
            QMessageBox::critical(nullptr, "Ошибка", e.what());
        }
    }

    return 0;
}
