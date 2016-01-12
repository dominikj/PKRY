#include "podprotokol1.h"
#include <ctime>
#include <QFile>

Podprotokol1::Podprotokol1(Szyfrowanie& szyf, Tcp& tcp, Baza& baza) : Podprotokol(szyf, tcp, baza){}

bool Podprotokol1::wykonaj(){
   /* {
    QString strToSave(_szyfrowanie.generujKlucze().publiczny);
    QFile output("gap");
    if (output.open(QIODevice::Append)) {
        QDataStream out(&output);
        out << strToSave.toUtf8().toBase64();
        output.close();
    }
    }
    {
    QString strToSave(_szyfrowanie.generujKlucze().prywatny);
    QFile output("skcca");
    if (output.open(QIODevice::Append)) {
        QDataStream out(&output);
        out << strToSave.toUtf8().toBase64();
        output.close();
    }
    }*/

    QString Dc = "USER=" + _baza.nazwaUzytkownika + " PASSWD=" + _baza.haslo + " ";
   QString podpis = _szyfrowanie.podpisz(_baza.SKcca, Dc.toLatin1());
    Dc += podpis;
    QString daneDoWyslania = _szyfrowanie.szyfruj(_baza.kluczGAPPrywatny,Dc.toLatin1());
    qDebug() << daneDoWyslania;
   // _tcp.wyslij(daneDoWyslania.toLatin1());

   QString daneZaszyfrowane = _tcp.odbierz();
   QString dane = _szyfrowanie.deszyfruj(_baza.SKcca, daneZaszyfrowane.toLatin1());
   QStringList pola = dane.split("|||");
   QStringList tmp =pola.at(1).split("=");
   if(tmp.at(0) == "SKGAP")
       podpis = tmp.at(1);
    if (_szyfrowanie.sprawdzPodpis(_baza.kluczGAPPrywatny,podpis.toLatin1(),pola.at(0).toLatin1())){
        // zapis pól
    }


    return true;
}
Podprotokol1::~Podprotokol1(){

}
