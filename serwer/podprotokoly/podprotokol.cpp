#include "podprotokol.h"
/**
 * @brief oddziela właściwe dane od podpisu
 * @param dane
 * @param czesc1
 * @param czesc2
 */
void Podprotokol::podziel(QByteArray &dane, QByteArray &czesc1, QByteArray &czesc2) {
    QByteArray rozm;
    for(int i =0; dane[i] != SEPARATOR2; ++i) {
        rozm += dane[i];
    }

    czesc1 = dane.mid(rozm.size()+1,rozm.toInt());
    czesc2 = dane.mid(rozm.toInt()+rozm.size()+1,-1);
}
/**
 * @brief scala dane z ich podpisem
 * @param czesc1
 * @param czesc2
 * @return dane scalone
 */
QByteArray Podprotokol::scal(QByteArray czesc1, QByteArray czesc2) {
    QByteArray rozm = QByteArray::number(czesc1.size()) + SEPARATOR2;
    return rozm + czesc1 + czesc2;
}

QString Podprotokol::czas() {
    return QString("[" + QTime::currentTime().toString() + "] ");
}

