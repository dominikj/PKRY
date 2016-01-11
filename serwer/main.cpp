#include "gui/start.h"
#include "gui/oknoglowne.h"
#include "sterownik/sterownik.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Sterownik sterownik;

    return a.exec();
}
