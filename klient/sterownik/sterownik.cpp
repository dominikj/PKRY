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
/**
 * @brief Przygotowuje aplikację do pracy
 */
void Sterownik::przygotowanie() {
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
        _czekZw = new OczekujZwyciezcy(_tcp,*this);
        _czekZw->blokada = true;

    }
}
/**
 * @brief logowanie użytkownika
 * @return
 */
bool Sterownik::zaloguj() {
    if ((_tcp->polacz()) && ( _podprot1->wykonaj())) {
             QObject::connect(_tcp->gniazdo(),SIGNAL(readyRead()),_czekZw,SLOT(czekajZwyciezcy()));
        return true;
    }
    else {
        return false;
    }
}
/**
 * @brief czeka na zwycięzcę
 * @return
 */
OczekujZwyciezcy* Sterownik::czekajNaZwyciezce() {
    _tcp->gniazdo()->readAll();
    _czekZw->blokada = false;
    return _czekZw;
}
/**
 * @brief przygotowuje informacje do wyświetlenia w konsoli
 * @param dane
 */
void Sterownik::daneDoKonsoli(QString dane) {
    _konsola += "[" + QTime::currentTime().toString() + "] " + dane +"\n";
    qDebug() << dane;
}
QString Sterownik::daneKonsola() {
    QString tmp = _konsola;
    _konsola.clear();
    return tmp;
}
/**
 * @brief wykonuje przesłanie nowej aukcji
 * @param nowaAukcja ogłaszany przetarg
 * @return sukces/porażka
 */
bool Sterownik::dodajAukcje(QString nowaAukcja) {
    _baza.oferta = nowaAukcja;
    return  _podprot2->wykonaj();
}
/**
 * @brief pobiera aukcje z serwera
 * @return aukcje
 */
std::vector<Aukcja>& Sterownik::pobierzAukcjeZSerwera() {
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
/**
 * @brief Pobiera aukcje z lokalnej bazy
 * @return aukcje
 */
std::vector<Aukcja>& Sterownik::pobierzAukcje() {
    return _baza.DostepneAukcje;
}/**
 * @brief wysyła ofertę do gapa
 * @param oferta
 * @param nr aukcji
 * @return sukces/porażka
 */
bool Sterownik::wyslijOferte(QString oferta, QString nrAukcji) {
    _baza.oferta = oferta;
    _baza.ofertaNumerAukcji = nrAukcji;
    return _podprot3->wykonaj();
}
/**
 * @brief odsyła zwycięzcę do gapa
 * @param zwycięzca
 */
void Sterownik::wyborZwyciezcy(QString odpowiedz) {
    _czekZw->blokada = true;
    _podprot4->odeslijZwyciezce(odpowiedz);
}

