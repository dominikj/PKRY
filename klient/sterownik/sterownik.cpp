#include "sterownik.h"
#include "oczekujzwyciezcy.h"
Sterownik::Sterownik() : _gui(*this)
{
    _gui.uruchom();

}

void Sterownik::ustawDaneLogSer(QString login, QString haslo, QString adres, int port) {
    _port = port;
    _adres = adres;
    _baza.nazwaUzytkownika = login;
    _baza.haslo = haslo;
    przygotowanie();
}

void Sterownik::przygotowanie() {
    // TODO: zabezpieczyć przed potencjalnym wyciekiem pamięci, przejść np. na wake_ptr
    if(_tcp == nullptr) {
        _tcp = new ProxyTcp(_port, _adres,_szyfr);
        _podprot1 = new Podprotokol1(_szyfr,*_tcp,_baza);
        _podprot2 = new Podprotokol2(_szyfr,*_tcp,_baza);
        _podprot3 = new Podprotokol3(_szyfr,*_tcp,_baza);
        _podprot4 = new Podprotokol4(_szyfr,*_tcp,_baza);
        connect(_podprot1,SIGNAL(wyswietlKonsola(QString)),this,SLOT(daneDoKonsoli(QString)));
        connect(_podprot2,SIGNAL(wyswietlKonsola(QString)),this,SLOT(daneDoKonsoli(QString)));
        connect(_podprot3,SIGNAL(wyswietlKonsola(QString)),this,SLOT(daneDoKonsoli(QString)));
        connect(_podprot4,SIGNAL(wyswietlKonsola(QString)),this,SLOT(daneDoKonsoli(QString)));

        czekZw = new OczekujZwyciezcy(_tcp,*this);
    }
}

bool Sterownik::zaloguj() {
    if ((_tcp->polacz()) && ( _podprot1->wykonaj())) {
        return true;
    }
    else {
        return false;
    }
}

OczekujZwyciezcy* Sterownik::czekajNaZwyciezce() {
    _tcp->gniazdo()->readAll();
    QObject::connect(_tcp->gniazdo(),SIGNAL(readyRead()),czekZw,SLOT(czekajZwyciezcy()));
    return czekZw;
}

void Sterownik::daneDoKonsoli(QString dane) {
    _konsola += "[" + QTime::currentTime().toString() + "] " + dane +"\n";
    qDebug() << dane;
}
QString Sterownik::daneKonsola() {
    QString tmp = _konsola;
    _konsola.clear();
    return tmp;
}

bool Sterownik::dodajAukcje(QString nowaAukcja) {
    _baza.oferta = nowaAukcja;
    return  _podprot2->wykonaj();
}

std::vector<Aukcja>& Sterownik::pobierzAukcje() {
    (dynamic_cast<ProxyTcp*>(_tcp))->wyslijSzyfrowane(_baza.kluczGAP,"GETAUCTIONS|");
    QByteArray aukcje = _tcp->odbierz();
    _baza.DostepneAukcje.clear();
    if(aukcje == "") throw std::exception();
    aukcje = aukcje.mid(0,aukcje.size()-2); // wyciecie ostatniego separatora
    QByteArrayList aukcjeLista = aukcje.split(SEPARATOR2);
    for(QByteArray auk : aukcjeLista) {
        Aukcja obAuk;
        QByteArrayList aukPola = auk.split(SEPARATOR1);
        obAuk.numer = aukPola.at(0);
        obAuk.dataZakonczenia = aukPola.at(1);
        obAuk.parametry = aukPola.at(2);
        obAuk.kluczPublicznyAucji = aukPola.at(3);
        _baza.DostepneAukcje.push_back(obAuk);
        qDebug() <<  obAuk.numer << obAuk.parametry;
    }
    return _baza.DostepneAukcje;
}

bool Sterownik::wyslijOferte(QString oferta, QString nrAukcji) {
    _baza.oferta = oferta;
    _baza.ofertaNumerAukcji = nrAukcji;
    return _podprot3->wykonaj();
}

void Sterownik::czekajZwyciezcy(){
    qDebug() << "TUTAJ";
}
void Sterownik::wyborZwyciezcy(QString odpowiedz){
 _podprot4->odeslijZwyciezce(odpowiedz);
}

