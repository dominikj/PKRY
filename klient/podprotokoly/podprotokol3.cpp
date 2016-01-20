#include "podprotokol3.h"
#include <QDateTime>
#include "utils/aukcja.h"
Podprotokol3::Podprotokol3(Szyfrowanie& szyf, Tcp& tcp, Baza& baza) : Podprotokol(szyf, tcp, baza)
{

}
/**
  Wykonuje scenariusz podprotokołu 3 po stronie klienta (złożenie oferty)
 * @brief Podprotokol1::wykonaj
 * @return sukces/porażka operacji
 */
bool Podprotokol3::wykonaj() {
    emit wyswietlKonsola(QString("Składanie oferty"));

    _baza.numerOferenta = QString::number(rand());
    _baza.czasWygenOferty = QString::number(QDateTime::currentDateTime().toTime_t() + 3600*48);
    QString tmp = _baza.ofertaNumerAukcji + SEPARATOR1 + _baza.numerOferenta + SEPARATOR1 + _baza.numerRejestracyjny + SEPARATOR1 + _baza.czasWygenKluczy;
    QByteArray Dc = tmp.toLatin1();
    QByteArray podpis = _szyfrowanie.podpisz(_baza.KluczPrywatny, Dc);
    Dc = scal(Dc,podpis);
    SZYFR_TCP->wyslijSzyfrowane(_baza.kluczGAP,"PODPROTOKOL31|" +Dc);
    QByteArray dane = SZYFR_TCP->odbierzLinie();
    if(dane != "OK\n") return false;
    tmp = _baza.oferta;
    Dc = tmp.toLatin1();
    for (Aukcja a : _baza.DostepneAukcje) {
        if(a.numer == _baza.ofertaNumerAukcji) {
            Dc = _szyfrowanie.szyfruj(a.kluczPublicznyAucji, Dc);
            SZYFR_TCP->wyslijSzyfrowane(_baza.kluczGAP,"PODPROTOKOL32|"+ Dc);
            QByteArray dane = SZYFR_TCP->odbierzLinie();
            if(dane != "OK\n") return false;
            dane = SZYFR_TCP->odbierzSzyfrowane(_baza.KluczPrywatny);
            QByteArray dane1;
            podziel(dane,dane1,podpis);
            if(_szyfrowanie.sprawdzPodpis(_baza.kluczGAP,podpis,dane1) && dane1 == "OK")
                emit wyswietlKonsola(QString("Odpowiedź serwera: ") + dane1);
            return true;
        }
    }
    return false;

}
Podprotokol3::~Podprotokol3() {

}
