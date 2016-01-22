#ifndef BAZA_H
#define BAZA_H
#include <botan/botan.h>
#include <QString>
#include <map>
#include "utils/aukcja.h"
#include <deque>
using namespace Botan;
/**
 * @brief Klasa z danymi, które są wykorzystywane w wielu miejscach w programie
 */
struct Baza
{
public:
    Baza();
    bool zaladujUzytkownikow(QString);
    QString pobierzHalso(QString);
    QByteArray zaladujKluczUzytkownika(QString);

    QByteArray kluczGAPPrywatny;

    std::deque<Aukcja*> aukcje;

private:
       std::map<QString,QString> _uzytkownicy;
};

#endif // BAZA_H
