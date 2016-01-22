#include "podprotokol4.h"
#include "utils/uzytkownik.h"
#include "utils/proxytcp.h"
#include <unistd.h>
Podprotokol4::Podprotokol4(Szyfrowanie& szyf,Baza& baza) : Podprotokol(szyf, baza)
{

}
bool Podprotokol4::wykonaj(Uzytkownik* uz,QByteArray dane) { }
/**
 * @brief Realizacja podprotokołu 4 (rozstrzygnięcie przetargu) - część żądająca  do uczestników ich części klucza
 * @return sukces/porażka operacji
 */
bool Podprotokol4::wykonaj() {

    for(int i = 0; i < aukcja->oferty.size(); ++i) {
        if(aukcja->oferty[i].uzyte == false) {
            aukcja->oferty[i].uzyte = true;
            for(Uzytkownik* uz : *uzytkownicy) {
                if(uz->nazwa == aukcja->oferty[i].nazwaUczestnika) {
                    SZYFR_TCP(uz)->wyslij("test\n");
                    qDebug() << czas()<<"Proszę o klucz:" << uz->nazwa;
                    return true;
                }
            }
        }
    }
    if (!aukcja->czyFirmaOdpytana) {
        for(Uzytkownik* uz : *uzytkownicy) {
            if(aukcja->firmaNazwa == uz->nazwa) {
                SZYFR_TCP(uz)->wyslij("test\n");
                qDebug() <<czas()<< "Proszę o klucz:" << uz->nazwa;
                aukcja->czyFirmaOdpytana = true;
                _firma = uz;
                return true;
            }
        }
    }

    wykonaj4();
koniec:
    return true;
}
/**
 * @brief Realizacja podprotokołu 4 (rozstrzygnięcie przetargu) - część wysyłająca fragmenty klucza do użytkowników
 * @param uz wskaźnik na użytkownika
 * @return sukces/porażka operacji
 */
bool Podprotokol4::wykonaj2(Uzytkownik* uz) {
    qDebug() << czas() <<"Wysłano fragment klucza do: " << uz->nazwa;
    QByteArray Dc = fragmentyKlucza[fragmentyKlucza.size()-1];
    fragmentyKlucza.pop_back();
    QByteArray podpis = _szyfrowanie.podpisz(_baza.kluczGAPPrywatny,Dc);
    Dc = scal(Dc,podpis);
    try{
    SZYFR_TCP(uz)->wyslijSzyfrowane(uz->kluczPubliczny,Dc);
    }
    catch(...){
        qDebug() << czas() << "Błąd transmisji";
        wykonaj();
        return false;
    }
    return true;
}
/**
 * @brief Realizacja podprotokołu 4 (rozstrzygnięcie przetargu) - część odbierająca fragmenty klucza do użytkowników
 * @param uz użytkownik
 * @param dane odebrane dane
 * @return sukces/porażka operacji
 */
bool Podprotokol4::wykonaj3(Uzytkownik* uz,QByteArray dane) {
    qDebug() << czas() <<"Odebrano fragment klucza";
    QByteArray odp, podpis;
    podziel(dane,odp,podpis);
    if(_szyfrowanie.sprawdzPodpis(uz->kluczPubliczny,podpis,odp)) {
        qDebug() << aukcja->firmaNazwa;
        if(aukcja->firmaNazwa != uz->nazwa)
            _fragmentyKluczaOdebrane.push_back(odp);
        else
            aukcja->kluczPrywatnyAukcjiCzescFirma = odp;
    }
    wykonaj();
    return true;
}
/**
 * @brief Realizacja podprotokołu 4 (rozstrzygnięcie przetargu) - część odszyfrowująca oferty i przesyłająca je do firmy
 * @return sukces/porażka operacji
 */
bool Podprotokol4::wykonaj4() {
    QByteArray kompletnyKluczUczestnicy, kompletnyKlucz;
    std::vector<QByteArray> fragmenty;
    if(!aukcja->czyFirmaOdpytana){
         qDebug() << czas() <<"Firma rozłączyła się";
         zakoncz("NIEWAZNY\n");
         return false;
    }
    fragmenty.push_back(aukcja->kluczPrywatnyAukcjiCzescFirma);
    fragmenty.push_back(aukcja->kluczPrywatnyAukcjiCzescGAP);
  //  fragmenty.push_back(aukcja->kluczPrywatnyAukcjiCzescUczestnicy); // dla debugu
    if(_fragmentyKluczaOdebrane.size() >= 2) {
        kompletnyKluczUczestnicy = _szyfrowanie.przywrocSekret(2,_fragmentyKluczaOdebrane);
        fragmenty.push_back(kompletnyKluczUczestnicy);
    }
    else {
        qDebug() << czas() <<"Przetarg nieważny. Mniej niż 2 uczestników";
         SZYFR_TCP(_firma)->wyslij("NIEWAZNY\n");
         zakoncz("AUKCJA NIEWAZNA");
         return false;
    }
    kompletnyKlucz = _szyfrowanie.przywrocSekret(3,fragmenty);
    QString tmp, tmp1;
    QByteArray Dc;
    tmp1 = "nr_aukc="+QByteArray::number(aukcja->numerAukcji);
    for(Oferta of : aukcja->oferty) {
        int i = 0;
        for(; i < uzytkownicy->size(); ++i)
            if((*uzytkownicy)[i]->nazwa == of.nazwaUczestnika)
                break;

        tmp = "nr_uczes=" +of.numerUczestnika + ";nrc="+ (*uzytkownicy)[i]->numerRejestracyjny;
        (tmp  +=";"+ _szyfrowanie.deszyfruj(kompletnyKlucz,of.oferta));
        qDebug() << czas() <<"Odszyfrowuję ofertę: " << tmp;
        tmp1 += "::" + tmp;
    }
    Dc = tmp1.toLatin1();
    SZYFR_TCP(_firma)->wyslij("WAZNY\n");
    QByteArray podpis = _szyfrowanie.podpisz(_baza.kluczGAPPrywatny, Dc);
    Dc = scal(Dc,podpis);
    try{
    SZYFR_TCP(_firma)->wyslijSzyfrowane(_firma->kluczPubliczny,Dc);
    }
    catch(...){
        qDebug() << czas() << "Błąd transmisji";
        zakoncz("AUKCJA NIEWAZNA");
        return false;
    }

    qDebug() <<czas() << "Oferty przesłano";
    return true;
}
/**
 * @brief Realizacja podprotokołu 4 (rozstrzygnięcie przetargu) - część odbierająca zwycięzcę od firmy i przygotowująca ogłoszenie dla pozostałych uczestników
 * @param uz użytkownik
 * @param dane odebrane dane
 * @return sukces/porażka operacji
 */
bool Podprotokol4::wykonaj5(Uzytkownik* uz, QByteArray dane) {
    QByteArray daneBezpodpisu, podpis, ogloszenie;
    podziel(dane,daneBezpodpisu,podpis);
    if(_szyfrowanie.sprawdzPodpis(uz->kluczPubliczny,podpis,daneBezpodpisu)) {
        qDebug() << czas()<< "Odebrano zwyciezcę";
        QByteArrayList tmp = daneBezpodpisu.split(';');
        qDebug() << tmp;
        QByteArrayList tmp1 = tmp.at(1).split(SEPARATOR1);
        QString zwyciezcaImie, zwyciezcaNumer;
        for(Uzytkownik* u : *uzytkownicy) {
            if(u->numerRejestracyjny.toLatin1() == tmp1.at(0)) {
                zwyciezcaImie = u->nazwa;
                break;
            }
        }
        for(Oferta of : aukcja->oferty) {
            if(of.nazwaUczestnika == zwyciezcaImie) {
                zwyciezcaNumer = of.numerUczestnika;
                break;
            }
        }
        QByteArray tmp2 =tmp.at(0);
        tmp2 = tmp2.replace('\t', ' ');
          ogloszenie = zwyciezcaImie.toLatin1() + " numer: " + zwyciezcaNumer.toLatin1() + " numery pozostałych uczestników: " + tmp2 +"\n";
          zakoncz(ogloszenie);
    }
    else{
        //błąd
    }
}
/**
 * @brief Realizacja podprotokołu 4 (rozstrzygnięcie przetargu) - część wysyłająca ogłoszenie o zwycięzcy do wszystkich oferentów i kasująca aukcję z systemu
 * @param ogloszenie komunikat wysyłany do oferentów
 */
void Podprotokol4::zakoncz(QString ogloszenie){
    for(Uzytkownik* u : *uzytkownicy) {
        for(Oferta of : aukcja->oferty) {
            if(u->nazwa == of.nazwaUczestnika) {
                qDebug() << czas() <<"Wysyłam ogłoszenie do:" << u->nazwa;

                SZYFR_TCP(u)->wyslij(ogloszenie.toLatin1());
            }
        }
    }

    for (auto it = _baza.aukcje.begin(); it < _baza.aukcje.end(); ++it) {
        if(aukcja->numerAukcji == (*it)->numerAukcji)
            _baza.aukcje.erase(it);
    }
    fragmentyKlucza.clear();
    _fragmentyKluczaOdebrane.clear();
    _firma = nullptr;
    aukcja=nullptr;

    qDebug() << "KONIEC";
}

Podprotokol4::~Podprotokol4() {

}
