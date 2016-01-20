#include "podprotokol1.h"
#include <ctime>
#include "utils/proxytcp.h"
#include "QDateTime"

Podprotokol1::Podprotokol1(Szyfrowanie& szyf, Tcp& tcp, Baza& baza) : Podprotokol(szyf, tcp, baza) {}
/**
  Wykonuje scenariusz podprotokołu 1 po stronie klienta (logowanie)
 * @brief Podprotokol1::wykonaj
 * @return sukces/porażka operacji
 */
bool Podprotokol1::wykonaj() {
    emit wyswietlKonsola(QString("Logowanie"));

    QString tmp = "USER=" + _baza.nazwaUzytkownika + SEPARATOR1 + "PASSWD=" + _baza.haslo;

    QByteArray Dc = tmp.toLatin1();
    QByteArray podpis = _szyfrowanie.podpisz(_baza.SKcca, Dc);
    Dc = scal(Dc,podpis);
    SZYFR_TCP->wyslijSzyfrowane(_baza.kluczGAP,"PODPROTOKOL1|" +Dc);
     qDebug() << "info";
    QByteArray dane = SZYFR_TCP->odbierzLinie();
     qDebug() << "info";
    if(dane != "OK\n") return false;

    dane = SZYFR_TCP->odbierzSzyfrowane(_baza.SKcca);
    qDebug() << "info";
    QByteArray daneZwrotneCalosc;
    podziel(dane,daneZwrotneCalosc,podpis);
    QByteArrayList daneZwrotneLista = daneZwrotneCalosc.split(SEPARATOR1);
    if(_szyfrowanie.sprawdzPodpis(_baza.kluczGAP,podpis,daneZwrotneCalosc)) {
        emit wyswietlKonsola  ("Numer rejestracyjny: " + (_baza.numerRejestracyjny = daneZwrotneLista.at(0)));
        emit wyswietlKonsola ("Czas ważności kluczy: " + (_baza.czasWygenKluczy = daneZwrotneLista.at(1)));
        emit wyswietlKonsola  ("Indywidualny klucz prywatny: " + ( _baza.KluczPrywatny = daneZwrotneLista.at(2)));
        emit wyswietlKonsola("Indywidualny klucz publiczny: "+ (_baza.kluczPubliczny = daneZwrotneLista.at(3)));
        return true;
    }
    return false; //TODO: Poprawić jeden if w serwerze

}

