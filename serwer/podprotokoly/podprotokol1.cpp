#include "podprotokol1.h"
#include <ctime>
#include <QFile>
#include "utils/uzytkownik.h"
#include "utils/proxytcp.h"
#include <ctime>
#include <cstdlib>
#include <QTime>

#define SZYFR_TCP(UZYT) (dynamic_cast<ProxyTcp*>(UZYT->poloczenie()))


Podprotokol1::Podprotokol1(Szyfrowanie& szyf, Baza& baza) : Podprotokol(szyf, baza) { std::srand(std::time(NULL));}

bool Podprotokol1::wykonaj(Uzytkownik* uz, QByteArray dane) {
    qDebug() << "Logowanie";

    QByteArray daneLogowaniaCalosc, podpis;
    podziel(dane,daneLogowaniaCalosc,podpis);

    QByteArrayList daneLogowaniaLista = daneLogowaniaCalosc.split(SEPARATOR1);

    QString nazwaUzytkownika = daneLogowaniaLista.at(0).split('=').at(1);
    QString haslo = daneLogowaniaLista.at(1).split('=').at(1);
    try {
        if (haslo ==_baza.pobierzHalso(nazwaUzytkownika)) {
            QString klucz = _baza.zaladujKluczUzytkownika(nazwaUzytkownika);
            if(_szyfrowanie.sprawdzPodpis(klucz,podpis,daneLogowaniaCalosc) == true){
                uz->nazwa = nazwaUzytkownika;
                uz->PKc = klucz.toLatin1();
                qDebug() << "Użytkownik: "<<nazwaUzytkownika<< " zalogowany!";
                QByteArray odpowiedz = przygotujOdpowiedz(uz);
                                (uz)->poloczenie()->wyslij("OK\n");
                SZYFR_TCP(uz)->wyslijSzyfrowane(uz->PKc,odpowiedz);
                return true;
            }
        }
        else
            qDebug() << "Użytkownik: "<<nazwaUzytkownika<< " istnieje, ale podał złe hasło";
                 (uz)->poloczenie()->wyslij("OK\n");
                return false;
    }
    catch(std::exception ex) {
        qDebug() << "Użytkownik: "<<nazwaUzytkownika<< " nie istnieje!";
            (uz)->poloczenie()->wyslij("OK\n");
           return false;
    }

}

QByteArray Podprotokol1::przygotujOdpowiedz(Uzytkownik *uz){
    QByteArray odpowiedz;

    uz->numerRejestracyjny = QString::number(rand());
    odpowiedz += uz->numerRejestracyjny;
    odpowiedz += SEPARATOR1;
     uz->czasWygenKluczy = QTime::currentTime().toString();
     odpowiedz += uz->czasWygenKluczy.toLatin1();

    Klucze kl = _szyfrowanie.generujKlucze();
    odpowiedz += SEPARATOR1;
    odpowiedz += kl.prywatny;
    odpowiedz += SEPARATOR1;
    odpowiedz += kl.publiczny;
    QByteArray podpis = _szyfrowanie.podpisz(_baza.kluczGAPPrywatny,odpowiedz);
    odpowiedz = scal(odpowiedz,podpis);
    return odpowiedz;


}

Podprotokol1::~Podprotokol1() {

}
