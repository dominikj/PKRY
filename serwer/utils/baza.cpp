#include "baza.h"
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QByteArray>
#include <exception>
Baza::Baza()
{
 QFile gap("gapPriv");
    if (gap.open(QIODevice::ReadOnly)) {
           QDataStream wejscie(&gap);
           QByteArray klucz;

           while (!gap.atEnd()) {
               wejscie >> klucz;
           }
         kluczGAPPrywatny = QByteArray::fromBase64(klucz);
          }
          else throw std::exception();

   gap.close();
}

bool Baza::zaladujUzytkownikow(QString nazwa){
    QFile plik(nazwa);
    if(!plik.open(QIODevice::ReadOnly)) {
       return false;
    }

    QTextStream wej(&plik);

    while(!wej.atEnd()) {
        QString linia = wej.readLine();
        QStringList pola = linia.split("=");
        _uzytkownicy[pola.at(0)] = pola.at(1);
    }

    plik.close();
    return true;
}

QString Baza::pobierzHalso(QString uzytkownik ){
    auto znajdz = _uzytkownicy.find(uzytkownik);
        if(znajdz != _uzytkownicy.end()) {
            return znajdz->second;
        }
        else {
            throw std::exception();
        }
}

QByteArray Baza::zaladujKluczUzytkownika(QString nazwa){
     QFile pkcca(nazwa +"_PKcca");
      QByteArray tmp;
     QByteArray klucz;
    if (pkcca.open(QIODevice::ReadOnly)) {
           QDataStream wejscie(&pkcca);
           while (!pkcca.atEnd()) {
               wejscie >> klucz;
           }
         tmp = QByteArray::fromBase64(klucz);
          }
    else throw std::exception();
    pkcca.close();
    return tmp;
}
