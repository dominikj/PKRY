#include "proxytcp.h"

void ProxyTcp::wyslijSzyfrowane(QString klucz, QByteArray dane) {
   // qDebug() << dane;
    wyslij("START");
    while(odbierz() != "OK");
    int i = 0, j = 0;
    QByteArray daneZaszyfrowane;
    while( i*MAX_WIAD_ROZM < dane.size()) {
        j = (((i*MAX_WIAD_ROZM)+MAX_WIAD_ROZM-1) < (dane.size()-1)) ? MAX_WIAD_ROZM : -1;
        QByteArray porcja= dane.mid(i*MAX_WIAD_ROZM, j);
        daneZaszyfrowane = _szyfr.szyfruj(klucz,porcja);
        wyslij(daneZaszyfrowane);
        while(odbierz() != "OK"); //FIXME do poprawienia, niebezpieczeństwo zawieszenia aplikacji
        ++i;

    }
    wyslij("END");
}

QByteArray ProxyTcp::odbierzSzyfrowane(QString klucz) {
    if(debug)
    qDebug() <<odbierz();
    while(odbierz() != "START");
    wyslij("OK");
    QByteArray dane;
    QByteArray wiadomosc;
    while((dane = odbierz()) != "END") {
        qDebug() << dane;
        if(!debug)
        wiadomosc += _szyfr.deszyfruj(klucz, dane);
        _gniazdo->write("OK");
    }
    return wiadomosc;
}
