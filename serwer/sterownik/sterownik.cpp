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

void Sterownik::przyszlyDane(Uzytkownik *uz) {

    qDebug() << "Odebrano dane od użytkownika:" << uz->numerWew;
   // SZYFR_TCP(uz)->wyslijSzyfrowane(_baza.kluczGAPPrywatny);
    QByteArray rozkaz,tmp, dane = SZYFR_TCP(uz)->odbierzSzyfrowane(_baza.kluczGAPPrywatny);
    int i;
    for( i =0; dane[i] != SEPARATOR3; ++i){
    rozkaz += dane[i];
    }
    qDebug() << dane;
    if( rozkaz == "PODPROTOKOL1")
        _podprot1->wykonaj(uz,dane.mid(++i,-1));


}
