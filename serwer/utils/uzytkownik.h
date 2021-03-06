#ifndef UZYTKOWNIK_H
#define UZYTKOWNIK_H

#include <QObject>
#include "utils/tcp.h"
/**
 * @brief Klasa pojedynczego użytkownika
 */
class Uzytkownik : public QObject
{
    Q_OBJECT
public:
    explicit Uzytkownik(QObject *parent = 0, Tcp* soc = 0): _soc(soc) {
        connect(_soc->gniazdo(),SIGNAL(disconnected()),this,SLOT(koniecPoloczenia()));
        connect(_soc->gniazdo(),SIGNAL(readyRead()),this,SLOT(daneWBuforze()));
    }
    bool operator==(Uzytkownik& uz) const {
        if(numerWew == uz.numerWew) return true;
        else return false;
    }
    Tcp* const poloczenie() {
        return _soc;
    }

signals:
    void poloczenieZamkniete(Uzytkownik* uz);
    void przyszyDane(Uzytkownik* uz);
private slots:
    void koniecPoloczenia();
    void daneWBuforze();
private:
    Tcp* _soc;
public:
    unsigned int numerWew; // Nie zmieniać!

    QByteArray PKc;
    QString nazwa = "";

    QString numerRejestracyjny; // NRc
    QByteArray kluczPubliczny; //PKc
    QByteArray KluczPrywatny; //SKc
    QString czasWygenKluczy; //TNRc

};

#endif // UZYTKOWNIK_H
