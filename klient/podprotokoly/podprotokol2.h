#ifndef PODPROTOKOL2_H
#define PODPROTOKOL2_H
#include "podprotokol.h"
#include <QString>
#include "utils/proxytcp.h"
#define SZYFR_TCP (dynamic_cast<ProxyTcp*>(&_tcp))
/**
 * @brief Klasa podprotokołu 2 po stronie klienta - ogłaszanie nowej aukcji
 */
class Podprotokol2 : public QObject, public Podprotokol
{
    Q_OBJECT
public:
    Podprotokol2(Szyfrowanie& szyf, Tcp& tcp, Baza& baza);
    virtual bool wykonaj();
    ~Podprotokol2();

signals:
    void wyswietlKonsola(QString info);

};

#endif // PODPROTOKOL2_H
