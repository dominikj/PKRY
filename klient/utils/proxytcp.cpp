#include "proxytcp.h"

void ProxyTcp::wyslijSzyfrowane(QString klucz, QByteArray dane){
    qDebug() <<"----------";
    wyslij("START");
    while(odbierz() != "OK");
    int i = 0, j = 0;
    QByteArray daneZaszyfrowane;
    while( i*MAX_WIAD_ROZM < dane.size()){
          j = (((i*MAX_WIAD_ROZM)+MAX_WIAD_ROZM-1) < (dane.size()-1)) ? MAX_WIAD_ROZM : -1;
         QByteArray porcja= dane.mid(i*MAX_WIAD_ROZM, j);
         daneZaszyfrowane = _szyfr.szyfruj(klucz,porcja);
         wyslij(daneZaszyfrowane);
        while(odbierz() != "OK"); //FIXME do poprawienia, niebezpieczeństwo zawieszenia aplikacji
         ++i;

    }
    wyslij("END");
}

QString ProxyTcp::odbierzSzyfrowane(QString klucz){
    while(odbierz() != "START");
    wyslij("OK");
    QByteArray dane;
    QString wiadomosc;
    while((dane = odbierz()) != "END"){
        //wiadomosc += _szyfr.deszyfruj(klucz, dane);
        wiadomosc += dane;
        qDebug() << dane;
        _gniazdo->write("OK");
    }
    return wiadomosc;
}
