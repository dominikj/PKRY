#ifndef PODPROTOKOL_H
#define PODPROTOKOL_H
#include "utils/szyfrowanie.h"
#include "utils/tcp.h"
#include "utils/baza.h"
#include <QString>
#include <QByteArray>
#include <QDebug>
#define SEPARATOR1 '\t'
#define SEPARATOR2 '\r'
#define SEPARATOR3 '|'
/*!
 * Podprotkół - klasa abstrakcyjna, narzuca pewne stałe elementy niezbędne do zaimplementowania w podprotokołach.
 */
class Podprotokol //klasa abstrakcyjna
{
public:
    /*!
     * Konstruktor pobiera referencje na obiekty klas Szyfrowanie, Tcp oraz Baza.
     */
    Podprotokol(Szyfrowanie& szyf, Tcp& tcp, Baza& baza): _szyfrowanie(szyf), _tcp(tcp), _baza(baza){}
    /*!
     * Desktruktor wirtualny klasy Podprotokol.
     */
    virtual ~Podprotokol(){}

    /*!
     * Wykonuje zadany podprotokół.
     * \return - zwraca true jeśli wykonano pomyślnie; w przeciwnym wypadku false.
     */
    virtual bool wykonaj() = 0;  // W tym operacje podprotokołu
protected:
    /*!
     * Referencja na obiekt klasy Szyfrowanie.
     */
    Szyfrowanie& _szyfrowanie;
    /*!
     * Referencja na obiekt klasy Tcp.
     */
    Tcp& _tcp;
    /*!
     * Referencja na obiekt klasy Baza.
     */
    Baza& _baza;

    void podziel(QByteArray& dane, QByteArray& czesc1, QByteArray& czesc2);
    QByteArray scal(QByteArray czesc1, QByteArray czesc2);
};

#endif // PODPROTOKOL_H
