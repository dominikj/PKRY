#ifndef STEROWNIK_H
#define STEROWNIK_H
#pragma once
#include "podprotokoly/podprotokol1.h"
#include "podprotokoly/podprotokol2.h"
#include "podprotokoly/podprotokol3.h"
#include "podprotokoly/podprotokol4.h"
#include "utils/baza.h"
#include "utils/szyfrowanie.h"
#include "gui/gui.h"
#include "sterownik/oczekujzwyciezcy.h"
#include "utils/proxytcp.h"
#include <QTime>
class Sterownik : public QObject
{
    Q_OBJECT
public:
    Sterownik();
    void przygotowanie();
    void ustawDaneLogSer(QString login, QString haslo, QString adres, int port = 10099);
    bool dodajAukcje(QString nowaAukcja);
    bool zaloguj();
    std::vector<Aukcja>& pobierzAukcje();
    bool wyslijOferte(QString, QString);
    OczekujZwyciezcy *czekajNaZwyciezce();
    Tcp* _tcp = nullptr;
    QString daneKonsola();
    Podprotokol4* dajPodprot4() { return _podprot4;}
    QString oferty() { return _baza.ofertyDoRozpatrzenia;}
public slots:
    void daneDoKonsoli(QString);
     void czekajZwyciezcy();
     void wyborZwyciezcy(QString);
signals:
    void odpowiedz_serwera(QString odp);

private:
 Podprotokol1* _podprot1 =nullptr;
 Podprotokol2* _podprot2 =nullptr;
 Podprotokol3* _podprot3 =nullptr;
 Podprotokol4* _podprot4 =nullptr;
 GUI _gui;
 Baza _baza;
 Szyfrowanie _szyfr;
    //tu byl Tcp*
 int _port = 10099;
 QString _adres = "127.0.0.1";
 QString _konsola;
 OczekujZwyciezcy* czekZw;
};

#endif // STEROWNIK_H
