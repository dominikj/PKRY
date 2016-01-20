#ifndef OCZEKUJZWYCIEZCY_H
#define OCZEKUJZWYCIEZCY_H

#include <QObject>
#include "utils/tcp.h"
class Sterownik;
class OczekujZwyciezcy : public QObject
{
    Q_OBJECT
public:
    OczekujZwyciezcy(Tcp* tcp, Sterownik& ster): _tcp(tcp), _ster(ster)  {}
    bool blokada = false;
    bool czyFirma = false;
    bool czyEtap2 = false;
signals:
    void alertZwyciezca(QString zwyciezca);
public slots:
    void czekajZwyciezcy();
 private:
    Tcp* _tcp;
    Sterownik& _ster;
};

#endif // OCZEKUJZWYCIEZCY_H
