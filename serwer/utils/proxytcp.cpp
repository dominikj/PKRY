#include "proxytcp.h"
#include <math.h>

void ProxyTcp::wyslijSzyfrowane(QString klucz, QString dane){
    int i = 0, j = 0;
    QString daneZaszyfrowane;
    while( i*MAX_WIAD_ROZM < dane.size()){
          j = (((i*MAX_WIAD_ROZM)+MAX_WIAD_ROZM-1) < (dane.size()-1)) ? ((i*MAX_WIAD_ROZM)+MAX_WIAD_ROZM-1) : (dane.size()-1);
         QString porcja= dane.mid(i*MAX_WIAD_ROZM, j);
         daneZaszyfrowane = _szyfr.szyfruj(klucz,porcja.toLatin1());
         wyslij(daneZaszyfrowane.toLatin1());
         odbierz();
         ++i;

    }
}

QString ProxyTcp::odbierzSzyfrowane(QString klucz){
    QString dane, wiadomosc;
    while(dane != "END"){
        dane = odbierz();
        wiadomosc += _szyfr.deszyfruj(klucz, dane.toLatin1());
    }
    return wiadomosc;
}
