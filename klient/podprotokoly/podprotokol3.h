#ifndef PODPROTOKOL3_H
#define PODPROTOKOL3_H
#include "podprotokol.h"
#include <QString>
#include "utils/proxytcp.h"
#define SZYFR_TCP (dynamic_cast<ProxyTcp*>(&_tcp))

class Podprotokol3 : public QObject, public Podprotokol
{
    Q_OBJECT
public:
    Podprotokol3(Szyfrowanie& szyf, Tcp& tcp, Baza& baza);
    virtual bool wykonaj();
    ~Podprotokol3();
signals:
    void wyswietlKonsola(QString info);
private:
};

#endif // PODPROTOKOL3_H
