#ifndef SZYFROWANIE_H
#define SZYFROWANIE_H
#include <QByteArray>
#include <QString>
#include <botan/botan.h>
#include <botan/rsa.h>
#include <botan/look_pk.h>
#define KLUCZ_ROZM 2048
#define MAX_WIAD_ROZM 240
using namespace Botan;

struct Klucze{
    QString publiczny;
    QString prywatny;
};

class Szyfrowanie
{
public:

    Szyfrowanie();
    Klucze generujKlucze();
    QByteArray szyfruj(QString klucz, QString dane);
    QByteArray deszyfruj(QString klucz, QByteArray dane);
    QByteArray podpisz(QString klucz, QByteArray dane);
    bool sprawdzPodpis(QString klucz,QByteArray podpis, QByteArray dane);
private:
      LibraryInitializer _init;
};

#endif // SZYFROWANIE_H
