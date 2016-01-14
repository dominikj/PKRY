#include "sterownik.h"
#include "oczekujzwyciezcy.h"
Sterownik::Sterownik() : _gui(*this)
{
_gui.uruchom();

}

void Sterownik::ustawDaneLogSer(QString login, QString haslo, QString adres, int port){
    _port = port;
    _adres = adres;
    _baza.nazwaUzytkownika = login;
    _baza.haslo = haslo;
    przygotowanie();
}

void Sterownik::przygotowanie(){
    // TODO: zabezpieczyć przed potencjalnym wyciekiem pamięci, przejść np. na wake_ptr
    _tcp = new ProxyTcp(_port, _adres,_szyfr);
    _podprot1 = new Podprotokol1(_szyfr,*_tcp,_baza);
    connect(_podprot1,SIGNAL(wyswietlKonsola(QString)),this,SLOT(daneDoKonsoli(QString)));
}

bool Sterownik::zaloguj(){
   if ((_tcp->polacz()) && ( _podprot1->wykonaj())){
        return true;
   }
   else{
       return false;
}
}

bool Sterownik::wykonajPodProt2(QString _nowaAukcja)
{
    _podprot2 = new Podprotokol2(_szyfr, *_tcp, _baza); //FIXME

    //scal, podpisz, zaszyfruj, wyslij, dostan potwierdzenie i zwroc je
}

QString Sterownik::pobierzAukcje(){
    _tcp->wyslij(QByteArray("GETAUCTIONS"));
    QString dane = _tcp->odbierz();
    return dane;
}

OczekujZwyciezcy* Sterownik::czekajNaZwyciezce(){
    OczekujZwyciezcy* czekZw = new OczekujZwyciezcy(_tcp);

    QObject::connect(_tcp->gniazdo(),SIGNAL(readyRead()),czekZw,SLOT(czekajZwyciezcy()));

 /*   QObject::connect(czekZw,SIGNAL(alertZwyciezca(QString)),_gui._wyborzwyciezcy,SLOT(wyswietl_okno(QString)));
    QObject::connect(_gui._wyborzwyciezcy,SIGNAL(info_dla_sterownika(QString,QString)),this,SLOT(wez_dane_zwyciezcy(QString,QString)));
    QObject::connect(this,SIGNAL(odpowiedz_serwera(QString)),_gui._wyborzwyciezcy,SLOT(odpowiedz_serwera(QString))); */
    return czekZw;
}

/*void Sterownik::wez_dane_zwyciezcy(QString zwyciezca, QString inni)
{
    //TODO: te dane wyzej wysylamy GAPowi
    //CZEKAMY NA ODPOWIEDZ I
    //ODPOWIADAMY OKIENKU
    QString odp = "";
 //   emit odpowiedz_serwera(odp);
}*/
void Sterownik::daneDoKonsoli(QString dane){
    _konsola += "[" + QTime::currentTime().toString() + "] " + dane;
    qDebug() << dane;
}
QString Sterownik::daneKonsola(){
    QString tmp = _konsola;
    _konsola.clear();
    return tmp;
}


