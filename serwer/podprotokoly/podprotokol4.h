#ifndef PODPROTOKOL4_H
#define PODPROTOKOL4_H
#include "podprotokol.h"
#include <QString>
typedef std::deque<Uzytkownik*> UzytkLista;
/**
 * @brief Klasa podprotokołu 4 po stronie serwera - wybór oferty
 */
class Podprotokol4 : public Podprotokol
{
public:
    Podprotokol4(Szyfrowanie& szyf,Baza& baza);
    virtual bool wykonaj();
    virtual bool wykonaj(Uzytkownik*,QByteArray);
    ~Podprotokol4();
    std::vector<QByteArray> fragmentyKlucza;

    UzytkLista* uzytkownicy;
    Aukcja* aukcja;
    bool wykonaj2(Uzytkownik*);
    bool wykonaj3(Uzytkownik* uz,QByteArray dane);
    bool wykonaj4();
    bool wykonaj5(Uzytkownik* uz, QByteArray dane);

private:
        Uzytkownik* _firma;
        std::vector<QByteArray> _fragmentyKluczaOdebrane;
        void zakoncz(QString);
};

#endif // PODPROTOKOL4_H
