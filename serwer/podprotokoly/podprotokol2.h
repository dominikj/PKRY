#ifndef PODPROTOKOL2_H
#define PODPROTOKOL2_H
#include "podprotokol.h"
#include <QString>

class Podprotokol2 : public Podprotokol
{
public:
    Podprotokol2(Szyfrowanie& szyf, Baza& baza);
    virtual bool wykonaj();
    ~Podprotokol2();

private:
    void podpisywanie_dokumentu();
    void kodowanie_asymetryczne();
    void odkodowanie_asymetryczne();
    void weryfikacja_podpisu();
    void generacja_PKG();
    void generacja_stempla_czasowego();

    QString N_f; //numer "zezwolenia" na utworzenie aukcji
    QString WP_f; //warunki przetargu
    QString SK_f; //klucz prywatny firmy !!!CZY TO NIE JEST TO SAMO CO SK_c w podprotokol1???
    QString NR_f; //numer rejestracyjny uzytkownika (znowu dubel z podprot1)
    QString T_nrf; //stempel czasowy numeru rejestracyjnego (znowu dubel z podprot1)
    QString klucz_publiczny_przetargu_F; //czesc klucza dla firmy

};

#endif // PODPROTOKOL2_H
