
#include "sterownik/sterownik.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Sterownik sterownik;

    return a.exec();
}
