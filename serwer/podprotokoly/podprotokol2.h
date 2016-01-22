#ifndef PODPROTOKOL2_H
#define PODPROTOKOL2_H
#include "podprotokol.h"
#include <QString>
class Sterownik;
/**
 * @brief Klasa podprotokołu 2 po stronie serwera - ogłaszanie nowej aukcji
 */
class Podprotokol2 : public Podprotokol
{
public:
    Podprotokol2(Szyfrowanie& szyf, Baza& baza);
    virtual bool wykonaj(Uzytkownik*,QByteArray);
    ~Podprotokol2();
        QObject* ster;
private:


};

#endif // PODPROTOKOL2_H
