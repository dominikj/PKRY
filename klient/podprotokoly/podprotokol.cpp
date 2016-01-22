#include "podprotokol.h"
/**
 * @brief oddziela dane od ich podpisu
 * @param dane
 * @param czesc1
 * @param czesc2
 */
void Podprotokol::podziel(QByteArray &dane, QByteArray &czesc1, QByteArray &czesc2){
    QByteArray rozm;
    for(int i =0; dane[i] != SEPARATOR2; ++i){
    rozm += dane[i];
    }

    czesc1 = dane.mid(rozm.size()+1,rozm.toInt());
    czesc2 = dane.mid(rozm.toInt()+rozm.size()+1,-1);
}
/**
 * @brief skleja dane z podpisem
 * @param czesc1
 * @param czesc2
 * @return
 */
QByteArray Podprotokol::scal(QByteArray czesc1, QByteArray czesc2){
 QByteArray rozm = QByteArray::number(czesc1.size()) + SEPARATOR2;
 return rozm + czesc1 + czesc2;
}

