#ifndef PODPROTOKOL3_H
#define PODPROTOKOL3_H
#include "podprotokol.h"
#include <QString>

class Podprotokol3 : public Podprotokol
{
public:
    Podprotokol3(Szyfrowanie& szyf, Tcp& tcp, Baza& baza);
    virtual bool wykonaj();
    ~Podprotokol3();

private:
    void podpisywanie_dokumentu();
    void kodowanie_asymetryczne();
    void odkodowanie_asymetryczne();
    void weryfikacja_podpisu();
    void generacja_PKG();
    void generacja_stempla_czasowego();
    //NR_o1 = NR_c
    //SK_i1 = SK_c
    QString OF_o; //oferta danego uzytkownika
    QString N_o; //nowy numer uzytkownika dla danej aukcji
    QString T_o; //stempel czasowy oferty
    QString W_o; //potwierdzenie oferty
};

#endif // PODPROTOKOL3_H
