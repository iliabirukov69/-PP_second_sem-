#include <QApplication>
#include <QMessageBox>
#include <QInputDialog>
#include <QString>
#include "functions.h" // Убрали строчку #include <QTextCodec>

int main(int argc, char *argv[]) {
    // В Qt 6 здесь больше ничего настраивать не нужно,
    // так как UTF-8 включен по умолчанию для всех строк!

    QApplication a(argc, argv);

    // Этот цикл позволит вводить числа сколько угодно раз
    while (true) {
        bool ok;

        // Красивое окно для ввода числа с клавиатуры
        double userSide = QInputDialog::getDouble(
            nullptr,
            "Лабораторная 1 - Ввод",
            "Введите длину стороны квадрата\n(или нажмите Cancel для выхода):",
            5.0,     // Значение по умолчанию в поле ввода
            0.001,   // Минимально возможная сторона
            100000.0,// Максимально возможная сторона
            3,       // Количество знаков после запятой
            &ok
            );

        // Если нажата кнопка "Cancel" или крестик — программа аккуратно закроется
        if (!ok) {
            break;
        }

        try {
            // Передаем число в класс Square для расчетов
            Square mySquare(userSide);

            // Собираем текст результатов
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

            // Показываем окно с результатами и кнопками "Да"/"Нет"
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(nullptr, "Лабораторная 1 - Успех", resultText,
                                          QMessageBox::Yes | QMessageBox::No);

            // Если нажал "No", то выходим из программы
            if (reply == QMessageBox::No) {
                break;
            }

        } catch (const std::exception& e) {
            // Если введено некорректное число, покажется ошибка
            QMessageBox::critical(nullptr, "Ошибка", e.what());
        }
    }

    return 0;
}
