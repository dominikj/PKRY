#ifndef OCZEKUJZWYCIEZCY_H
#define OCZEKUJZWYCIEZCY_H

#include <QObject>
#include "utils/tcp.h"

class OczekujZwyciezcy : public QObject
{
    Q_OBJECT
public:
    OczekujZwyciezcy(Tcp* tcp): _tcp(tcp) {}
signals:
    void alertZwyciezca(QString zwyciezca);
public slots:
    void czekajZwyciezcy();
 private:
    Tcp* _tcp;
};

#endif // OCZEKUJZWYCIEZCY_H
