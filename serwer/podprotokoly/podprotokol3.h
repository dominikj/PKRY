#ifndef PODPROTOKOL3_H
#define PODPROTOKOL3_H
#include "podprotokol.h"
#include <QString>
/**
 * @brief Klasa podprotokołu 3 po stronie serwera - dodawanie nowej oferty
 */
class Podprotokol3 : public Podprotokol
{
public:
    Podprotokol3(Szyfrowanie& szyf, Baza& baza);
    virtual bool wykonaj(Uzytkownik*,QByteArray);
     virtual bool wykonaj2(Uzytkownik*,QByteArray);
    ~Podprotokol3();

private:
    Aukcja * _aukcja;
    QString _numerUczestnika;

};

#endif // PODPROTOKOL3_H
