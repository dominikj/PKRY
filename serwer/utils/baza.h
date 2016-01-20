#ifndef BAZA_H
#define BAZA_H
#include <botan/botan.h>
#include <QString>
#include <map>
#include "utils/aukcja.h"
using namespace Botan;

struct Baza
{
public:
    Baza();
    bool zaladujUzytkownikow(QString);
    QString pobierzHalso(QString);
    QByteArray zaladujKluczUzytkownika(QString);

    QByteArray kluczGAPPrywatny;

    std::vector<Aukcja*> aukcje;

private:
       std::map<QString,QString> _uzytkownicy;
};

#endif // BAZA_H
