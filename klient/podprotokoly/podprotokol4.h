#ifndef PODPROTOKOL4_H
#define PODPROTOKOL4_H
#include "podprotokol.h"
#include <QString>
#include "utils/proxytcp.h"
#define SZYFR_TCP (dynamic_cast<ProxyTcp*>(&_tcp))

class Podprotokol4 : public QObject, public Podprotokol
{
    Q_OBJECT
public:
    Podprotokol4(Szyfrowanie& szyf, Tcp& tcp, Baza& baza);
    virtual bool wykonaj();
    bool wykonajUczestnik();
    bool wykonajFirma();
    bool czekajNaOferty();
    bool odeslijZwyciezce(QString);
    bool odbierzWynik();
    ~Podprotokol4();

private:
};

#endif // PODPROTOKOL4_H
