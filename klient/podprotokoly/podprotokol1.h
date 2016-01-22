#ifndef PODPROTOKOL1_H
#define PODPROTOKOL1_H
#include <stdio.h>
#include <iostream>
#include <string>
#include "podprotokol.h"
#define SZYFR_TCP (dynamic_cast<ProxyTcp*>(&_tcp))
/**
 * @brief Klasa podprotokołu 1 po stronie klienta - logowanie użytkownika
 */
class Podprotokol1 : public QObject, public Podprotokol
{
    Q_OBJECT
public:
    Podprotokol1(Szyfrowanie& szyf, Tcp& tcp, Baza& baza);
    virtual bool wykonaj();
    QString oferta;
signals:
    void wyswietlKonsola(QString info);
private:

};

#endif // PODPROTOKOL1_H
