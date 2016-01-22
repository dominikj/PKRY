#ifndef OCZEKUJZWYCIEZCY_H
#define OCZEKUJZWYCIEZCY_H

#include <QObject>
#include "utils/tcp.h"
class Sterownik;
/**
 * @brief Klasa sterująca przepływem danych z połączenia tcp w fazie wyboru oferty/oczekiwania na zwycięzcę
 */
class OczekujZwyciezcy : public QObject
{
    Q_OBJECT
public:
    OczekujZwyciezcy(Tcp* tcp, Sterownik& ster): _tcp(tcp), _ster(ster)  {}
    bool blokada = false;
    bool czyFirma = false;
signals:
    void alertZwyciezca(QString zwyciezca);
public slots:
    void czekajZwyciezcy();
 private:
    bool _czyEtap2 = false;
    Tcp* _tcp;
    Sterownik& _ster;
};

#endif // OCZEKUJZWYCIEZCY_H
