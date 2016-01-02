#ifndef BAZA_H
#define BAZA_H
#include <botan/botan.h>
#include <QString>
using namespace Botan;

class Baza
{
public:
    Baza();
    //1
    QString SKcca;
    QString kluczGAP; //PKgap
    QString nazwaUzytkownika;
    SecureVector<byte> haslo;
    QString numerRejestracyjny; // NRc
    QString kluczPubliczny; //PKc
    QString KluczPrywatny; //SKc
    QString czasWygenKluczy; //TNRc

    //2
    //TODO: dodać pola przechowujace warunki naszego przetargu WPf
    QString czescKluczaPrzetargu; //SKp(f) lub SKp(o)
    QString numerFirmy; //Nf
    QString numerAukcji; //Np
    QString kluczPublicznyPrzetargu; //PKp

    //3
    QString czasWygenOferty; //To
    QString numerOferenta; //No
     //TODO: dodać pola przechowujace ofertę oferenta



};

#endif // BAZA_H
