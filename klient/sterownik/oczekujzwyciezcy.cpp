#include "oczekujzwyciezcy.h"
#include "sterownik.h"
#include <unistd.h>
void OczekujZwyciezcy::czekajZwyciezcy(){
    if(!blokada){

        qDebug() << "WYKONUJE";
        sleep(2);
       if(!czyFirma){
           if(!czyEtap2){
               qDebug() << "TUTAAAJ";
           _ster.dajPodprot4()->wykonajUczestnik();
           czyEtap2 = true;
            }
           else{
                qDebug() << "TUTeeeJ";
               _ster.dajPodprot4()->odbierzWynik();
               blokada = false;
               disconnect(_tcp,0,0,0);
               emit alertZwyciezca(QString(""));
           }
       }
       else {
            qDebug() << "TUToeeJ";
           _ster.dajPodprot4()->wykonajFirma();
           blokada = true;
                emit alertZwyciezca(QString(""));
       }

    }
}
