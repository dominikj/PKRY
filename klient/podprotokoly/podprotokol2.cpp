#include "podprotokol2.h"
#include <ctime>
#include <cstdlib>

Podprotokol2::Podprotokol2(Szyfrowanie& szyf, Tcp& tcp, Baza& baza) : Podprotokol(szyf, tcp, baza) {}
/**
  Wykonuje scenariusz podprotokołu 2 po stronie klienta (ogłaszanie aukcji)
 * @brief Podprotokol1::wykonaj
 * @return sukces/porażka operacji
 */
bool Podprotokol2::wykonaj() {
    emit wyswietlKonsola(QString("Dodawanie aukcji"));

    _baza.numerFirmy = QString::number(rand());
    QString tmp = _baza.numerRejestracyjny + SEPARATOR1 + _baza.oferta + SEPARATOR1 + _baza.numerFirmy + SEPARATOR1 +_baza.czasWygenKluczy;

    QByteArray Dc = tmp.toLatin1();

    QByteArray podpis = _szyfrowanie.podpisz(_baza.KluczPrywatny, Dc);
    Dc = scal(Dc,podpis);
   // qDebug() << Dc;
    SZYFR_TCP->wyslijSzyfrowane(_baza.kluczGAP,"PODPROTOKOL2|" +Dc);
    QByteArray dane = SZYFR_TCP->odbierzLinie();
    if(dane != "OK\n") return false;

    dane = SZYFR_TCP->odbierzSzyfrowane(_baza.KluczPrywatny);
    QByteArray daneZwrotneCalosc;
    podziel(dane,daneZwrotneCalosc,podpis);
    _baza.czescKluczaPrzetargu = daneZwrotneCalosc;
    if(_szyfrowanie.sprawdzPodpis(_baza.kluczGAP,podpis,daneZwrotneCalosc)) {
        qDebug() << daneZwrotneCalosc;
        emit wyswietlKonsola(QByteArray("Część klucza aukcji: "));
           emit wyswietlKonsola(QByteArray( daneZwrotneCalosc.mid(0,daneZwrotneCalosc.size()/2)));
        emit wyswietlKonsola(QByteArray(daneZwrotneCalosc.mid(daneZwrotneCalosc.size()/2,-1)));

        return true;
    }
    else return false;
}
Podprotokol2::~Podprotokol2() {

}
