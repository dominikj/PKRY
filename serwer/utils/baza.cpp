#include "baza.h"
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QByteArray>
Baza::Baza()
{
 QFile skcca("skcca");
 QFile gap("gapPriv");
    if (skcca.open(QIODevice::ReadOnly)) {
           QDataStream wejscie(&skcca);
           QByteArray klucz;

           while (!skcca.atEnd()) {
               wejscie >> klucz;
           }
         SKcca = QByteArray::fromBase64(klucz);
          }
    if (gap.open(QIODevice::ReadOnly)) {
           QDataStream wejscie(&gap);
           QByteArray klucz;

           while (!gap.atEnd()) {
               wejscie >> klucz;
           }
         kluczGAPPrywatny = QByteArray::fromBase64(klucz);
          }



    //qDebug() << SKcca;
    qDebug() << kluczGAPPrywatny;
   gap.close();
    skcca.close();
}
