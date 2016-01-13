#ifndef PODPROTOKOL4_H
#define PODPROTOKOL4_H
#include "podprotokol.h"
#include <QString>

class Podprotokol4 : public Podprotokol
{
public:
    Podprotokol4(Szyfrowanie& szyf,Baza& baza);
    virtual bool wykonaj();
    ~Podprotokol4();

private:
    void podpisywanie_dokumentu();
    void kodowanie_asymetryczne();
    void odkodowanie_asymetryczne();
    void weryfikacja_podpisu();
    void generacja_PKG();
    void generacja_stempla_czasowego();

    QString SK_po; //czesc sekretu dla oferenta
    QString oferty; //oferty dla firmy dla rozstrzygniecia aukcji
    QString nr_aukcji; //znowu, jeśli nie zachowamy tego wczesniej
    QString nr_zwyciezcy; //numer zwyciezcy aukcji
    QString lista_ofert; //lista wszystkich ofert wzietych pod uwage
    //takze swoj numer rejestracyjny i numer jako firmy tworzącej aukcje z podprot1 i 2



};

#endif // PODPROTOKOL4_H
