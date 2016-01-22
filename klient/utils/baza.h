#ifndef BAZA_H
#define BAZA_H
#include <QString>
#include"utils/aukcja.h"

/**
 * @brief Klasa bazy danych potrzebnych do komunikacji
 */

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
    QByteArray czescKluczaPrzetargu; //SKp(f) lub SKp(o)
    QString numerFirmy; //Nf

    std::vector<Aukcja> DostepneAukcje;

    //3
    QString czasWygenOferty; //To
    QString numerOferenta; //No
    QString oferta;
    QString ofertaNumerAukcji;
     //TODO: dodać pola przechowujace ofertę oferenta

    //4
    QString ofertyDoRozpatrzenia;
};

#endif // BAZA_H
