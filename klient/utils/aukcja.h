#ifndef AUKCJA_H
#define AUKCJA_H
#include <QString>

class Aukcja
{
public:
    Aukcja();
    QByteArray numer;
    QByteArray dataZakonczenia;
    QByteArray parametry;
    QByteArray kluczPublicznyAucji;

};

#endif // AUKCJA_H
