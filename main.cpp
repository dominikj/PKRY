#include "start.h"
#include "oknoglowne.h"
#include "sterownik.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Sterownik sterownik;
    Start *w = new Start(0,sterownik);
    OknoGlowne o;
    w->show();
    //w.show();
    o.show();


    return a.exec();
}
