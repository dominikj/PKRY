#ifndef BAZA_H
#define BAZA_H
#include <botan/botan.h>
#include <QString>
#include <map>
using namespace Botan;

struct Baza
{
public:
    Baza();
    bool zaladujUzytkownikow(QString);
    QString pobierzHalso(QString);
    QByteArray zaladujKluczUzytkownika(QString);

    QString kluczGAPPrywatny;

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

private:
       std::map<QString,QString> _uzytkownicy;
};

#endif // BAZA_H
