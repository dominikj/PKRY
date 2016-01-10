#ifndef PODPROTOKOL_H
#define PODPROTOKOL_H
#include "szyfrowanie.h"
#include "tcp.h"
#include "baza.h"
#include <QString>
#include <QByteArray>
#include <QDebug>
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

};

#endif // PODPROTOKOL_H
