#ifndef SZYFROWANIE_H
#define SZYFROWANIE_H
#include <QByteArray>
#include <QString>
#include <botan/botan.h>
#include <botan/rsa.h>
#include <botan/look_pk.h>
#include <ida.h>
#include <rng.h>
#include <cryptlib.h>
#include <randpool.h>
#include <files.h>
#include <simple.h>
#include <filters.h>
#define KLUCZ_ROZM 2048
#define MAX_WIAD_ROZM 50
using namespace Botan;
using namespace CryptoPP;
//Podmienić z wersją z serwera
struct Klucze {
    QByteArray publiczny;
    QByteArray prywatny;
};
/**
 * @brief Klasa szyfrująca/deszyfrująca dane i realizująca podział sekretu algorytmem Shamira
 */
class Szyfrowanie
{
public:


    Szyfrowanie();
    Klucze generujKlucze();
    QByteArray szyfruj(QString klucz, QByteArray dane);
    QByteArray deszyfruj(QString klucz, QByteArray dane);
    QByteArray podpisz(QString klucz, QByteArray dane);
    bool sprawdzPodpis(QString klucz,QByteArray podpis, QByteArray dane);
    QByteArray przywrocSekret(int minimalneUczestnictwo, std::vector<QByteArray> dane);
    std::vector<QByteArray> podzielSekret(int minimalneUczestnictwo, int liczbaUdzialow, QByteArray dane);
private:
    LibraryInitializer _init;
    void zapiszDoBufora(QByteArray dane, QString nazwa);
    std::vector<QByteArray> wczytajZBufora(int liczbaFragmentow,std::string prefix);
};

#endif // SZYFROWANIE_H
