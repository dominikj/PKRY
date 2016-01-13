#ifndef PODPROTOKOL1_H
#define PODPROTOKOL1_H
#include <stdio.h>
#include <iostream>
#include <string>
#include "podprotokol.h"
class Podprotokol1 : public Podprotokol
{
public:
    Podprotokol1(Szyfrowanie& szyf, Baza& baza);
    virtual bool wykonaj(Uzytkownik*,QByteArray);
    ~Podprotokol1();

private:
    QByteArray przygotujOdpowiedz(Uzytkownik*);

};

#endif // PODPROTOKOL1_H
