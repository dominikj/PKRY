#include "sterownik.h"
#define SZYFR_TCP(UZYT) (dynamic_cast<ProxyTcp*>(UZYT->poloczenie()))

void Sterownik::koniecPoloczenia(Uzytkownik* uz) {
    auto i = listaUzytkownikow.begin();

    for(; i < listaUzytkownikow.end(); ++i) {
        if(**i == *uz)
            listaUzytkownikow.erase(i);
    }
    qDebug() << "Użytkownik: " << ((uz->nazwa != "") ? uz->nazwa : QString::number(uz->numerWew)) << " rozłączył się";
}
/**
 * @brief decyduje, co zrobić z przychodzącymi danymi
 * @param uz użytkownik, który przysłał dane
 */
void Sterownik::przyszlyDane(Uzytkownik *uz) {
    QByteArray rozkaz,tmp, dane ;
    try{
     dane = SZYFR_TCP(uz)->odbierzSzyfrowane(_baza.kluczGAPPrywatny);
    }
catch(...){
    qDebug() << "Błąd transmisji";
}
    int i;
    for( i =0; dane[i] != SEPARATOR3; ++i) {
        rozkaz += dane[i];
    }
    if( rozkaz == "PODPROTOKOL1")
        _podprot1->wykonaj(uz,dane.mid(++i,-1));
    else if( rozkaz == "PODPROTOKOL2")
        _podprot2->wykonaj(uz,dane.mid(++i,-1));
    else if( rozkaz == "GETAUCTIONS")
        wyslijAukcje(uz);
    else if( rozkaz == "PODPROTOKOL31")
        _podprot3->wykonaj(uz,dane.mid(++i,-1));
    else if( rozkaz == "PODPROTOKOL32")
        _podprot3->wykonaj2(uz,dane.mid(++i,-1));
    else if( rozkaz == "PODPROTOKOL41")
        _podprot4->wykonaj3(uz,dane.mid(++i,-1));
    else if( rozkaz == "PODPROTOKOL40")
        _podprot4->wykonaj2(uz);
    else if( rozkaz == "PODPROTOKOL42")
        _podprot4->wykonaj5(uz,dane.mid(++i,-1));
}
/**
 * @brief Wysyła listę dostępnych aukcji do klienta
 * @param uzuz użytkownik, który tego zażądał
 */
void Sterownik::wyslijAukcje(Uzytkownik* uz) {
    QByteArray aukcja;
    for(Aukcja* a : _baza.aukcje) {
        aukcja += QByteArray::number(a->numerAukcji) +  SEPARATOR1 + a->zakonczenie.toString() + SEPARATOR1 + a->parametry + SEPARATOR1 + a->kluczPublicznyAukcji + SEPARATOR2; //Pamiętać że ostatni znak to separator!
    }
    uz->poloczenie()->wyslij(aukcja);

}
/**
 * @brief Wykonuje się, gdy, nastąpi timeout timera aukcji
 * @param au aukcja
 */
void Sterownik::koniecAukcji(Aukcja* au) {
    qDebug() << "KONIEC AUKCJI NR: "<< au->numerAukcji;
    _podprot4->aukcja = au;
    _podprot4->uzytkownicy = &listaUzytkownikow;
    _podprot4->fragmentyKlucza = _szyfr.podzielSekret(2,au->oferty.size(),au->kluczPrywatnyAukcjiCzescUczestnicy);
    _podprot4->wykonaj();
}

