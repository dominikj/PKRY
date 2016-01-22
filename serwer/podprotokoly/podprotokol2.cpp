#include "podprotokol2.h"
#include "utils/uzytkownik.h"
#include "utils/aukcja.h"
#include "utils/proxytcp.h"
#include <QObject>
Podprotokol2::Podprotokol2(Szyfrowanie& szyf, Baza& baza) : Podprotokol(szyf, baza)
{

}
/** Wykonuje scenariusz podprotokołu 2 po stronie serwera (założenie przetargu)
 * @brief Podprotokol2::wykonaj
 * @param uz obiekt użytkownika
 * @param dane odebrane dane
 * @return sukces/porażka operacji
 */

bool Podprotokol2::wykonaj(Uzytkownik* uz ,QByteArray dane) {
    qDebug() << czas()<<"Użytkownik ogłasza nową ofertę";

    QByteArray daneAukcjaCalosc, podpis;
    podziel(dane,daneAukcjaCalosc,podpis);
    if(_szyfrowanie.sprawdzPodpis(uz->kluczPubliczny,podpis,daneAukcjaCalosc)) {
        QByteArrayList daneLista = daneAukcjaCalosc.split(SEPARATOR1);
        if(uz->numerRejestracyjny == daneLista.at(0) && QDateTime::currentDateTime().toTime_t() > daneLista.at(3).toInt()) {
            qDebug() <<czas() << "Numer rejestracyjny:" <<daneLista.at(0);
            qDebug() << czas()<<"Czas wygaśnięcia kluczy:" << daneLista.at(3);
            qDebug() << czas()<<"Pozytywnie uwierzytelniono firmę";
            (uz)->poloczenie()->wyslij("OK\n");
            Aukcja* aukcja = new Aukcja();
            qDebug() << czas() <<"Numer firmy: " << daneLista.at(2);
            qDebug() << czas() <<"Warunki aukcji:" << daneLista.at(1);
            QByteArrayList lista = daneLista.at(1).split(';');
            QByteArray zakonczenie =  lista.at(2);

            QDateTime dtZakonczenie;

            QByteArrayList dataCzas = zakonczenie.split(' ');
            QByteArrayList tmp = dataCzas.at(0).split('=');
            dtZakonczenie.setDate( QDate::fromString(tmp.at(1),QString("dd:MM:yyyy")));
            dtZakonczenie.setTime(QTime::fromString(dataCzas.at(1),QString("HH:mm:ss")));

            aukcja->numerFirmy = daneLista.at(2).toInt();
            aukcja->zakonczenie = dtZakonczenie;
            aukcja->numerAukcji = std::rand();
            aukcja->firmaNazwa = uz->nazwa;
            Klucze kl = _szyfrowanie.generujKlucze();
            aukcja->kluczPublicznyAukcji = kl.publiczny;
            auto czesciKlucza = _szyfrowanie.podzielSekret(3,3,kl.prywatny);
            aukcja->kluczPrywatnyAukcjiCzescFirma = czesciKlucza[0];
            aukcja->kluczPrywatnyAukcjiCzescGAP = czesciKlucza[1];
            aukcja->kluczPrywatnyAukcjiCzescUczestnicy = czesciKlucza[2];
            aukcja->parametry = daneLista.at(1);

            aukcja->timer.setSingleShot(true);
            try {
                aukcja->timer.start(QDateTime::currentDateTime().msecsTo(aukcja->zakonczenie));
            }
            catch(...) {
                return false;
            }

            QByteArray odpowiedz;
            qDebug() << aukcja->kluczPrywatnyAukcjiCzescFirma;
            QByteArray podpis = _szyfrowanie.podpisz(_baza.kluczGAPPrywatny,aukcja->kluczPrywatnyAukcjiCzescFirma);
            odpowiedz = scal(aukcja->kluczPrywatnyAukcjiCzescFirma,podpis);
            try{
            SZYFR_TCP(uz)->wyslijSzyfrowane(uz->kluczPubliczny,odpowiedz);
            }
            catch(...){
                qDebug() << czas() << "Błąd transmisji";
                return false;
            }
             QObject::connect(aukcja,SIGNAL(zakonczonaAukcja(Aukcja*)),ster,SLOT(koniecAukcji(Aukcja*)));
              _baza.aukcje.push_back(aukcja);
            qDebug() <<czas()<<"Dodano aukcję";
            return true;
        }
        else
            (uz)->poloczenie()->wyslij("ERR\n");
    }
    else
        (uz)->poloczenie()->wyslij("ERR\n");
    return false;
}


Podprotokol2::~Podprotokol2() {

}
