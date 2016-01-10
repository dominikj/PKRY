#include "sterownik.h"

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
    _tcp = new Tcp(_port, _adres);
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

Sterownik::~Sterownik(){
    if (_podprot1 != nullptr)
        delete _podprot1;
}
