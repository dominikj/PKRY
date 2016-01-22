#include "oczekujzwyciezcy.h"
#include "sterownik.h"
#include <unistd.h>
/**
 * Steruje procesem oczekiwania na rozstrzygnięcie aukcji
 */
void OczekujZwyciezcy::czekajZwyciezcy() {
    if(!blokada) {
        sleep(2);
        if(!czyFirma) {
            if(!_czyEtap2) {
               if(! _ster.dajPodprot4()->wykonajUczestnik()){
                   blokada = true;
                  // disconnect(_tcp,0,0,0);
                   emit alertZwyciezca(QString(""));
               }
               else
                _czyEtap2 = true;
            }
            else {
                _ster.dajPodprot4()->odbierzWynik();
                blokada = true;
                _czyEtap2 = false;
               // disconnect(_tcp,0,0,0);
                emit alertZwyciezca(QString(""));
            }
        }
        else {
           if( _ster.dajPodprot4()->wykonajFirma()){
            blokada = true;
          //  disconnect(_tcp,0,0,0);
            emit alertZwyciezca(QString(""));
           }
           else{
               blokada = true;
          //     disconnect(_tcp,0,0,0);
                emit alertZwyciezca(QString("ERR"));
           }
        }

    }
}
