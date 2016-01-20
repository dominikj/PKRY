#include "baza.h"
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QByteArray>
Baza::Baza()
{




    //qDebug() << SKcca;
    qDebug() << kluczGAPPrywatny;
   gap.close();
    skcca.close();
}
