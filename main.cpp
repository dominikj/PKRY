#include "start.h"
#include "oknoglowne.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Start w;
    OknoGlowne o;
    w.show();
    o.show();


    return a.exec();
}
