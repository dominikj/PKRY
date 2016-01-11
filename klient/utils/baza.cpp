#include "baza.h"
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QByteArray>
Baza::Baza()
{
 QFile skcca("skcca");
 QFile gap("gap");
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
         kluczGAP = QByteArray::fromBase64(klucz);
          }



    //qDebug() << SKcca;
   // qDebug() << kluczGAP;
   gap.close();
    skcca.close();
}
