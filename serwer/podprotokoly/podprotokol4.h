#ifndef PODPROTOKOL4_H
#define PODPROTOKOL4_H
#include "podprotokol.h"
#include <QString>
typedef std::deque<Uzytkownik*> UzytkLista;
class Podprotokol4 : public Podprotokol
{
public:
    Podprotokol4(Szyfrowanie& szyf,Baza& baza);
    virtual bool wykonaj();
    virtual bool wykonaj(Uzytkownik*,QByteArray);
    ~Podprotokol4();
 std::vector<QString> oferty;
 std::vector<QByteArray> fragmentyKlucza;
 std::vector<QByteArray> fragmentyKluczaOdebrane;
 UzytkLista* uzytkownicy;
 Aukcja* aukcja;
 Uzytkownik* firma;
 bool wykonaj2(Uzytkownik*);
 bool wykonaj3(Uzytkownik* uz,QByteArray dane);
 bool wykonaj4();
 bool wykonaj5(Uzytkownik* uz, QByteArray dane);

private:
};

#endif // PODPROTOKOL4_H
