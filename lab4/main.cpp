#include "functions.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_Use96Dpi);

    QApplication a(argc, argv);
    Matrix w;
    w.show();
    return a.exec();
}
