#ifndef STEROWNIK_H
#define STEROWNIK_H
#include "podprotokoly/podprotokol1.h"
#include "podprotokoly/podprotokol2.h"
#include "podprotokoly/podprotokol3.h"
#include "podprotokoly/podprotokol4.h"
#include "utils/baza.h"
#include "utils/szyfrowanie.h"
#include "utils/tcp.h"
#include "gui/gui.h"
#include "sterownik/oczekujzwyciezcy.h"
class Sterownik
{
public:
    Sterownik();
    ~Sterownik();
    void przygotowanie();
    void ustawDaneLogSer(QString login, QString haslo, QString adres, int port = 10099);
    bool wykonajPodProt2(QString _nowaAukcja);
    bool zaloguj();
    QString pobierzAukcje();
    OczekujZwyciezcy *czekajNaZwyciezce();
private:
 Podprotokol1* _podprot1 =nullptr;
 Podprotokol2* _podprot2 =nullptr;
 Podprotokol3* _podprot3 =nullptr;
 Podprotokol4* _podprot4 =nullptr;
 GUI _gui;
 Baza _baza;
 Szyfrowanie _szyfr;
 Tcp* _tcp = nullptr;
 int _port = 10099;
 QString _adres = "127.0.0.1";
};

#endif // STEROWNIK_H
