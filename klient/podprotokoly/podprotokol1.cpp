#include "podprotokol1.h"
#include <ctime>
#include <QFile>
#include "utils/proxytcp.h"
#define SZYFR_TCP (dynamic_cast<ProxyTcp*>(&_tcp))

Podprotokol1::Podprotokol1(Szyfrowanie& szyf, Tcp& tcp, Baza& baza) : Podprotokol(szyf, tcp, baza) {}

bool Podprotokol1::wykonaj() {
    emit wyswietlKonsola(QString("Wykonuje podprot1"));

    QString tmp = "USER=" + _baza.nazwaUzytkownika + SEPARATOR1 + "PASSWD=" + _baza.haslo;

    QByteArray Dc = tmp.toLatin1();
    QByteArray podpis = _szyfrowanie.podpisz(_baza.SKcca, Dc);
    Dc = scal(Dc,podpis);
    SZYFR_TCP->wyslijSzyfrowane(_baza.kluczGAP,"PODPROTOKOL1|" +Dc);
    QByteArray dane = SZYFR_TCP->odbierzLinie();
    qDebug() << dane;
    if(dane != "OK\n") return false;

      dane = SZYFR_TCP->odbierzSzyfrowane(_baza.SKcca);
     QByteArray daneZwrotneCalosc;
     podziel(dane,daneZwrotneCalosc,podpis);
         qDebug() << dane;
      QByteArrayList daneZwrotneLista = daneZwrotneCalosc.split(SEPARATOR1);
    if(_szyfrowanie.sprawdzPodpis(_baza.kluczGAP,podpis,daneZwrotneCalosc)){
  qDebug() <<  ( _baza.numerRejestracyjny = daneZwrotneLista.at(0));
  qDebug() <<  (_baza.czasWygenKluczy = daneZwrotneLista.at(1));
  qDebug() <<  (_baza.KluczPrywatny = daneZwrotneLista.at(2));
  qDebug() <<  (_baza.kluczPubliczny = daneZwrotneLista.at(3));
    return true;
    }

    return true;
}

