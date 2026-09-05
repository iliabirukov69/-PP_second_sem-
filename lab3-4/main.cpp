#include "functions.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Cub w;
    w.show();
    return a.exec();
}
