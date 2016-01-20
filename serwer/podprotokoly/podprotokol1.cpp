#include "podprotokol1.h"
#include <ctime>
#include <QFile>
#include "utils/uzytkownik.h"
#include "utils/proxytcp.h"
#include <ctime>
#include <cstdlib>
#include <QTime>


Podprotokol1::Podprotokol1(Szyfrowanie& szyf, Baza& baza) : Podprotokol(szyf, baza) {
    std::srand(std::time(NULL));
}

/**
  Wykonuje scenariusz podprotokołu 1 po stronie serwera (logowanie)
 * @brief Podprotokol1::wykonaj
 * @param uz wskaźnik na obikekt urzytkownika
 * @param dane odebrane dane
 * @return sukces/porażka operacji
 */

bool Podprotokol1::wykonaj(Uzytkownik* uz, QByteArray dane) {
    qDebug() << "Logowanie";

    QByteArray daneLogowaniaCalosc, podpis;
    podziel(dane,daneLogowaniaCalosc,podpis);

    QByteArrayList daneLogowaniaLista = daneLogowaniaCalosc.split(SEPARATOR1);

    QString nazwaUzytkownika = daneLogowaniaLista.at(0).split('=').at(1);
    QString haslo = daneLogowaniaLista.at(1).split('=').at(1);
    qDebug() << "Uzytkownik: " << nazwaUzytkownika;
    qDebug() << "Hasło:" << haslo;
    try {
        if (haslo ==_baza.pobierzHalso(nazwaUzytkownika)) {
            QString klucz = _baza.zaladujKluczUzytkownika(nazwaUzytkownika); //PKcca
            if(_szyfrowanie.sprawdzPodpis(klucz,podpis,daneLogowaniaCalosc) == true) {
                uz->nazwa = nazwaUzytkownika;
                uz->PKc = klucz.toLatin1(); //PKcca
                qDebug() << "Użytkownik zalogowany!";
                QByteArray odpowiedz = przygotujOdpowiedz(uz);
                (uz)->poloczenie()->wyslij("OK\n");
                SZYFR_TCP(uz)->wyslijSzyfrowane(uz->PKc,odpowiedz);
                return true;
            }
            else {
                qDebug() << "Błędy podpis cyfrowy";
                return false;
            }
        }
        else
            qDebug() << "Użytkownik: "<<nazwaUzytkownika<< " istnieje, ale podał złe hasło";
        SZYFR_TCP(uz)->wyslij("ERR\n");
        return false;
    }
    catch(std::exception ex) {
        qDebug() << "Użytkownik: "<<nazwaUzytkownika<< " nie istnieje!";
        SZYFR_TCP(uz)->wyslij("ERR\n");
        return false;
    }

}
/** Przygotowanie odpowiedzi dla użytkownika
 * @brief Podprotokol1::przygotujOdpowiedz
 * @param uz obiekt użytkownika
 * @return odpowiedź
 */
QByteArray Podprotokol1::przygotujOdpowiedz(Uzytkownik *uz) {
    QByteArray odpowiedz;

    uz->numerRejestracyjny = QString::number(rand());
    odpowiedz += uz->numerRejestracyjny;
    odpowiedz += SEPARATOR1;
    QDateTime czas = QDateTime::currentDateTime();
    czas.addSecs(3600*48); //klucze są ważne 48h
    uz->czasWygenKluczy = QString::number(czas.toTime_t());
    odpowiedz += uz->czasWygenKluczy.toLatin1();

    Klucze kl = _szyfrowanie.generujKlucze();
    odpowiedz += SEPARATOR1;
    odpowiedz += kl.prywatny;
    uz->KluczPrywatny= kl.prywatny;
    odpowiedz += SEPARATOR1;
    odpowiedz += kl.publiczny;
    uz->kluczPubliczny = kl.publiczny;
    QByteArray podpis = _szyfrowanie.podpisz(_baza.kluczGAPPrywatny,odpowiedz);
    odpowiedz = scal(odpowiedz,podpis);
    return odpowiedz;


}

Podprotokol1::~Podprotokol1() {

}
