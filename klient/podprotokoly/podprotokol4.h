#ifndef PODPROTOKOL4_H
#define PODPROTOKOL4_H
#include "podprotokol.h"
#include <QString>
#include "utils/proxytcp.h"
#define SZYFR_TCP (dynamic_cast<ProxyTcp*>(&_tcp))
/**
 * @brief Klasa podprotokołu 4 po stronie klienta - wybór oferty
 */
class Podprotokol4 : public QObject, public Podprotokol
{
    Q_OBJECT
public:
    Podprotokol4(Szyfrowanie& szyf, Tcp& tcp, Baza& baza);
    virtual bool wykonaj(){}
    bool wykonajUczestnik();
    bool wykonajFirma();
    bool czekajNaOferty();
    bool odeslijZwyciezce(QString);
    bool odbierzWynik();
    ~Podprotokol4();
signals:
    void wyswietlKonsola(QString info);
};

#endif // PODPROTOKOL4_H
