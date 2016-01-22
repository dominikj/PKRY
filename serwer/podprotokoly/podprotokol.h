#ifndef PODPROTOKOL_H
#define PODPROTOKOL_H
#include "utils/szyfrowanie.h"
#include "utils/tcp.h"
#include "utils/baza.h"
#include <QString>
#include <QByteArray>
#include <QDebug>
class Uzytkownik;
#define SEPARATOR1 '\t'
#define SEPARATOR2 '\r'
#define SEPARATOR3 '|'
#define SZYFR_TCP(UZYT) (dynamic_cast<ProxyTcp*>(UZYT->poloczenie()))
/**
 * @brief Klasa abstrakcyjna podprotokołów
 */
class Podprotokol //klasa abstrakcyjna
{
public:
    Podprotokol(Szyfrowanie& szyf, Baza& baza): _szyfrowanie(szyf), _baza(baza){}
    virtual ~Podprotokol(){}

    virtual bool wykonaj(Uzytkownik*, QByteArray dane) = 0;  // W tym operacje podprotokołu
protected:
    Szyfrowanie& _szyfrowanie;
    Baza& _baza;
    void podziel(QByteArray& dane, QByteArray& czesc1, QByteArray& czesc2);
    QByteArray scal(QByteArray czesc1, QByteArray czesc2);
    QString czas();
};

#endif // PODPROTOKOL_H
