#ifndef PODPROTOKOL1_H
#define PODPROTOKOL1_H
#include <stdio.h>
#include <iostream>
#include <string>
#include "podprotokol.h"

/*!
 * Klasa odpowiedzialna za podprotokół nr 1 - identyfikacja i autoryzacja użytkownika w GAPie.
 */
class Podprotokol1 : public QObject, public Podprotokol
{
        Q_OBJECT
public:
    /*!
     * Konstruktor klasy Podprotokol.
     */
    Podprotokol1(Szyfrowanie& szyf, Tcp& tcp, Baza& baza);
    /*!
     * Implementacja funkcji odpowiedzialnej za wykonanie podprotokołu.
     * \return - zwraca true w przypadku pomyślnego wykonania podprotokołu. W przeciwnym wypadku false.
     */
    virtual bool wykonaj();
signals:
    /*!
     * Wyświetla w konsoli informacje o wymienianych z GAPem serwerem.
     * \param info - informacje o wykonywanych krokach.
     */
    void wyswietlKonsola(QString info);
private:

};

#endif // PODPROTOKOL1_H
