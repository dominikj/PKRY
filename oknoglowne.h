#ifndef OKNOGLOWNE_H
#define OKNOGLOWNE_H

#include <QMainWindow>
#include <QList>
#include <QString>
#include <QListWidgetItem>
#include "nowaaukcja.h"

namespace Ui {
class OknoGlowne;
}

class OknoGlowne : public QMainWindow
{
    Q_OBJECT

public:
    struct polaAukcji{
        QString nazwa_aukcji;
        QString opis_aukcji;
        QDateTime data_rozpoczecia;
        QDateTime data_zakonczenia;
        QList<QString> lista_kryteriow;
    };
    explicit OknoGlowne(QWidget *parent = 0);
    NowaAukcja *nowa;
    static QString ZMIENNA_ODSWIEZ;  //można ustawić coś innego jako nazwę pola na liście, na którym dwuklik skutkuje odświeżeniem listy
    void zapelnij_liste_aukcji();   //tutaj dostanie listę aukcji z GAPa
    void odswiez_liste_aukcji();    //jakby coś miało się zmienić i trzeba było pobrać nową listę z GAPa
    ~OknoGlowne();

private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_pushButton_2_clicked();

private:
    Ui::OknoGlowne *ui;
    QList<QString> listaAukcji;
    void pierwsze_miejsce_na_liscie_odswieza_liste_aukcji(); //zamiast przycisku, dwuklik na pierwszy element
};

#endif // OKNOGLOWNE_H
