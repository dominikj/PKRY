#ifndef PODPROTOKOL_H
#define PODPROTOKOL_H
#include "utils/szyfrowanie.h"
#include "utils/tcp.h"
#include "utils/baza.h"
#include <QString>
#include <QByteArray>
#include <QDebug>
#define SEPARATOR1 '\t'
#define SEPARATOR2 '\r'
#define SEPARATOR3 '|'
class Podprotokol //klasa abstrakcyjna
{
public:
    Podprotokol(Szyfrowanie& szyf, Tcp& tcp, Baza& baza): _szyfrowanie(szyf), _tcp(tcp), _baza(baza){}
    virtual ~Podprotokol(){}

    virtual bool wykonaj() = 0;  // W tym operacje podprotokołu
protected:
    Szyfrowanie& _szyfrowanie;
    Tcp& _tcp;
    Baza& _baza;

    void podziel(QByteArray& dane, QByteArray& czesc1, QByteArray& czesc2);
    QByteArray scal(QByteArray czesc1, QByteArray czesc2);
};

#endif // PODPROTOKOL_H
