#ifndef OKNOGLOWNE_H
#define OKNOGLOWNE_H

#include <QMainWindow>
#include <QList>
#include <QHash>
#include <QString>
#include <QListWidgetItem>
#include "zlozoferte.h"
#include "wybierzzwyciezce.h"
#include "gui/start.h"
#include "gui/nowaaukcja.h"

class Sterownik;
namespace Ui {
class OknoGlowne;
}
/**
 * @brief Klasa okna głównego aukcji
 */
class OknoGlowne : public QMainWindow
{
    Q_OBJECT

public:
    explicit OknoGlowne(QWidget *parent, Sterownik& ster, Start& st);

    ~OknoGlowne();

signals:
    void odpowiedz_serwera(QString odp, bool powodzenie);

private:
    struct polaAukcji{
        QString numer_aukcji;
        QString nazwa_aukcji;
        QString opis_aukcji;
        QString data_zakonczenia;
        QByteArrayList lista_kryteriow;
    };

private slots:
    void zlap_nowa_aukcje(polaAukcji pA);
    void zlap_nowa_oferte(QString of);
    void uruchom(bool t);
    void wybierz_zwyciezce_wyswietl_okno(QString wZ);
    void przyszlyOferty(QString o);
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();

private:

    OczekujZwyciezcy* ocz = nullptr;
    NowaAukcja *nowa;
    zlozOferte *oknooferty;
    WybierzZwyciezce *wyborzwyciezcy;
    static QString ZMIENNA_ODSWIEZ;  //można ustawić coś innego jako nazwę pola na liście, na którym dwuklik skutkuje odświeżeniem listy
    static QString nr_aktywnej_aukcji; //ostatni dwuklik na danej aukcji
    Ui::OknoGlowne *ui;
    QList<QString> listaAukcji;
    QHash<QString, polaAukcji> bazaAktywnychAukcji;
    QList<polaAukcji> listaAktywnychAukcji; //pierwsze - nr aukcji, drugie - warunki aukcji
    QString przygotuj_dane_aukcji_do_wyslania(polaAukcji &pA);
    polaAukcji konwertuj_do_struktury(QString wpis);
    Sterownik& _sterownik;
    Start& _start;
};

#endif // OKNOGLOWNE_H
