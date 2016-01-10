#ifndef BAZA_H
#define BAZA_H
#include <botan/botan.h>
#include <QString>
using namespace Botan;

struct Baza
{
public:
    Baza();
    //1
    QString SKcca;
    QString kluczGAP; //PKgap
    QString nazwaUzytkownika;
    QString haslo;
    QString numerRejestracyjny; // NRc
    QString kluczPubliczny; //PKc
    QString KluczPrywatny; //SKc
    QString czasWygenKluczy; //TNRc

    //2
    //TODO: dodać pola przechowujace warunki naszego przetargu WPf
    QString warunkiPrzetargu;
    QString czescKluczaPrzetargu; //SKp(f) lub SKp(o)
    QString numerFirmy; //Nf
    QString numerAukcji; //Np
    QString kluczPublicznyPrzetargu; //PKp <- ten tylko dla składającej ofertę

    //3
    QString czasWygenOferty; //To
    QString numerOferenta; //No
    QString oferta;
     //TODO: dodać pola przechowujace ofertę oferenta

    //4
    QString czescKluczaPrzetarguOferenta;
    QString ofertyDoRozpatrzenia;
    QString numerAukcjiRozpatrywanej;
    QString numerZwyciezcyAukcji;
    QString listaOfertRozpatrywanych;
};

#endif // BAZA_H
