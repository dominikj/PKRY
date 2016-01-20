#include "proxytcp.h"
#include <QTimer>
#define TIMEOUT 2000
void ProxyTcp::wyslijSzyfrowane(QString klucz, QByteArray dane) {

    qDebug() << "tutaj";
    QTimer* t = new QTimer(0);
    wyslij("START");
    t->setSingleShot(true);
    t->start(TIMEOUT);
    while(odbierz() != "OK") {
        if(!t->remainingTime())
            throw std::exception();
    }
    t->stop();
    int i = 0, j = 0;
    QByteArray daneZaszyfrowane;
    while( i*MAX_WIAD_ROZM < dane.size()) {
        j = (((i*MAX_WIAD_ROZM)+MAX_WIAD_ROZM-1) < (dane.size()-1)) ? MAX_WIAD_ROZM : -1;
        QByteArray porcja= dane.mid(i*MAX_WIAD_ROZM, j);
        daneZaszyfrowane = _szyfr.szyfruj(klucz,porcja);
        wyslij(daneZaszyfrowane);
        t->start(TIMEOUT);
        while(odbierz() != "OK") {
            if(!t->remainingTime())
                throw std::exception();
        }
        t->stop();
        ++i;

    }
    wyslij("END");
}

QByteArray ProxyTcp::odbierzSzyfrowane(QString klucz) {
    QTimer* t = new QTimer();
    t->setSingleShot(true);
    t->start(TIMEOUT);
    while(odbierz() != "START") {
        if(!t->remainingTime())
            throw std::exception();
    }
    t->stop();
    wyslij("OK");
    QByteArray dane;
    QByteArray wiadomosc;
    while((dane = odbierz()) != "END") {
        if(dane == "") throw std::exception();
        wiadomosc += _szyfr.deszyfruj(klucz, dane);
        _gniazdo->write("OK");
    }
    return wiadomosc;
}
