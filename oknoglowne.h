#ifndef OKNOGLOWNE_H
#define OKNOGLOWNE_H

#include <QMainWindow>
#include <QList>
#include <QHash>
#include <QString>
#include <QListWidgetItem>
#include "nowaaukcja.h"
#include "zlozoferte.h"
class Sterownik;
class zlozOferte;
namespace Ui {
class OknoGlowne;
}

class OknoGlowne : public QMainWindow
{
    Q_OBJECT

public:
    struct polaAukcji{
        QString numer_aukcji;
        QString nazwa_aukcji;
        QString opis_aukcji;
        QDateTime data_rozpoczecia;
        QDateTime data_zakonczenia;
        QList<QString> lista_kryteriow;
    };
    explicit OknoGlowne(QWidget *parent, Sterownik& ster);
    NowaAukcja *nowa;
    zlozOferte *oknooferty;
    static QString ZMIENNA_ODSWIEZ;  //można ustawić coś innego jako nazwę pola na liście, na którym dwuklik skutkuje odświeżeniem listy
    static QString nr_aktywnej_aukcji; //ostatni dwuklik na danej aukcji
    void zapelnij_liste_aukcji();   //tutaj dostanie listę aukcji z GAPa
    void odswiez_liste_aukcji();    //jakby coś miało się zmienić i trzeba było pobrać nową listę z GAPa
    ~OknoGlowne();

public slots:
    void zlap_nowa_aukcje(polaAukcji pA);

private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::OknoGlowne *ui;
    QList<QString> listaAukcji;
    QHash<QString, polaAukcji> bazaAktywnychAukcji;
    QList<polaAukcji> listaAktywnychAukcji; //pierwsze - nr aukcji, drugie - warunki aukcji
    polaAukcji konwertuj_do_struktury(QString wpis);
    Sterownik& _sterownik;
    void pierwsze_miejsce_na_liscie_odswieza_liste_aukcji(); //zamiast przycisku, dwuklik na pierwszy element
};

#endif // OKNOGLOWNE_H
