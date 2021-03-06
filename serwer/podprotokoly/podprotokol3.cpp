#include "podprotokol3.h"
#include "utils/uzytkownik.h"
#include "utils/proxytcp.h"
#include <thread>         // std::this_thread::sleep_for
#include <chrono>
Podprotokol3::Podprotokol3(Szyfrowanie& szyf, Baza& baza) : Podprotokol(szyf, baza)
{

}

/**
 * @brief Wykonuje scenariusz podprotokołu 3 po stronie serwera (złożenie oferty) - przesłanie Np, No, NRo, To
 * @param uz obiekt użytkownika
 * @param dane odebrane dane
 * @return sukces/porażka operacji
 */
bool Podprotokol3::wykonaj(Uzytkownik* uz,QByteArray dane) {
    qDebug() << czas()<<"Użytkownik ogłasza nową ofertę";

    QByteArray daneAukcjaCalosc, podpis;
    podziel(dane,daneAukcjaCalosc,podpis);
    if(_szyfrowanie.sprawdzPodpis(uz->kluczPubliczny,podpis,daneAukcjaCalosc)) {
        QByteArrayList daneLista = daneAukcjaCalosc.split(SEPARATOR1);
        qDebug() << czas()<<"Numer aukcji: " <<daneLista.at(0);
        qDebug() << czas()<<"Numer rejestracyjny: " << daneLista.at(2);
        qDebug() << czas()<<"Timestamp oferty: " << daneLista.at(3);
        qDebug() << czas()<<"Numer uczestnika: " << daneLista.at(1);
        _numerUczestnika = daneLista.at(1);
        int numerAukcji = 0;
        for(Aukcja* au : _baza.aukcje) {
            if(QByteArray::number(au->numerAukcji) == daneLista.at(0)) {
                numerAukcji = au->numerAukcji;
                _aukcja = au;
            }
        }
        if (numerAukcji != 0) {
            if(uz->numerRejestracyjny == daneLista.at(2)) {
                qDebug() <<czas()<< "Pozytywnie uwierzytelniono uczestnika";
                (uz)->poloczenie()->wyslij("OK\n");

            }
            else
                (uz)->poloczenie()->wyslij("ERR\n");
        }
        else
            (uz)->poloczenie()->wyslij("ERR\n");
    }
    else
        (uz)->poloczenie()->wyslij("ERR\n");
    return true;
}

/** Wykonuje scenariusz podprotokołu 3 po stronie serwera (złożenie oferty) - przesłanie oferty
 * @brief Podprotokol3::wykonaj
 * @param uz obiekt użytkownika
 * @param dane odebrane dane
 * @return sukces/porażka operacji
 */
bool Podprotokol3::wykonaj2(Uzytkownik *uz , QByteArray dane) {
    Oferta of;
    of.nazwaUczestnika =uz->nazwa;
    of.oferta = dane;
    of.numerUczestnika = _numerUczestnika;
    (uz)->poloczenie()->wyslij("OK\n");
    QByteArray odpowiedz;
    odpowiedz = "OK";
    QByteArray podpis = _szyfrowanie.podpisz(_baza.kluczGAPPrywatny, odpowiedz);
    odpowiedz = scal(odpowiedz,podpis);
    try{
    SZYFR_TCP(uz)->wyslijSzyfrowane(uz->kluczPubliczny,odpowiedz);
    }
    catch(...){
        qDebug() << czas() << "Błąd transmisji";
        return false;
    }
    qDebug() <<czas()<< "Dodano ofertę";
    _aukcja->oferty.push_back(of);

    return true;
}

Podprotokol3::~Podprotokol3() {

}
