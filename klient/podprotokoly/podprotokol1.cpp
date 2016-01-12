#include "podprotokol1.h"
#include <ctime>
#include <QFile>
#include "utils/proxytcp.h"
Podprotokol1::Podprotokol1(Szyfrowanie& szyf, Tcp& tcp, Baza& baza) : Podprotokol(szyf, tcp, baza){}

bool Podprotokol1::wykonaj(){
   // QByteArray dane = "PODPROTOKOL1\n";
//    _tcp.wyslij(dane);
//    _tcp.odbierz();
    /*{
        Klucze k = _szyfrowanie.generujKlucze();
    QString strToSave = k.publiczny;
    QFile output("gap");
    if (output.open(QIODevice::Append)) {
        QDataStream out(&output);
        out << strToSave.toUtf8().toBase64();
        output.close();
    }
    strToSave = k.prywatny;
    QFile output1("gapPriv");
    if (output1.open(QIODevice::Append)) {
        QDataStream out(&output1);
        out << strToSave.toUtf8().toBase64();
        output.close();
    }
    }*/

   /* QString strToSave(_szyfrowanie.generujKlucze().prywatny);
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
    qDebug() << Dc;
    (dynamic_cast<ProxyTcp*>(&_tcp))->wyslijSzyfrowane(_baza.kluczGAP,Dc.toLatin1());


/*   QString daneZaszyfrowane = _tcp.odbierz();
   QString dane = _szyfrowanie.deszyfruj(_baza.SKcca, daneZaszyfrowane.toLatin1());
   QStringList pola = dane.split("|||");
   QStringList tmp =pola.at(1).split("=");
   if(tmp.at(0) == "SKGAP")
       podpis = tmp.at(1);
    if (_szyfrowanie.sprawdzPodpis(_baza.kluczGAP,podpis.toLatin1(),pola.at(0).toLatin1())){
        // zapis pól
    }
*/


    return true;
}
Podprotokol1::~Podprotokol1(){

}
