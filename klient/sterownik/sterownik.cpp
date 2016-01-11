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
}

bool Sterownik::zaloguj(){
   //FIXME: if (_tcp->polacz()){
        _podprot1->wykonaj();
    //    return true;
   // }
 //   else return false;


}

bool Sterownik::wykonajPodProt2(QString _nowaAukcja)
{
    _podprot2 = new Podprotokol2(_szyfr, *_tcp, _baza);

    //scal, podpisz, zaszyfruj, wyslij, dostan potwierdzenie i zwroc je
}

QString Sterownik::pobierzAukcje(){
    _tcp->wyslij(QByteArray("GETAUCTIONS"));
    QString dane = _tcp->odbierz();
    return dane;
}

OczekujZwyciezcy* Sterownik::czekajNaZwyciezce(){
    OczekujZwyciezcy* czekZw = new OczekujZwyciezcy(_tcp);
    QObject::connect(_tcp,SIGNAL(readyRead()),czekZw,SLOT(czekajZwyciezcy()));
    return czekZw;
}

Sterownik::~Sterownik(){
    if (_podprot1 != nullptr)
        delete _podprot1;
}
