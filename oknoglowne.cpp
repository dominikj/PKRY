#include "oknoglowne.h"
#include "ui_oknoglowne.h"
#include <QList>
#include <QString>
#include <QListWidgetItem>
#include <QWidget>
#include <QMessageBox>


QString OknoGlowne::ZMIENNA_ODSWIEZ = "ODŚWIEŻ...";

OknoGlowne::OknoGlowne(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OknoGlowne)
{
    ui->setupUi(this);
    QList<QString> listaAukcji;
    pierwsze_miejsce_na_liscie_odswieza_liste_aukcji();
    zapelnij_liste_aukcji();
}

OknoGlowne::~OknoGlowne()
{
    delete ui;
}

void OknoGlowne::pierwsze_miejsce_na_liscie_odswieza_liste_aukcji()
{
    /*!
     * Pierwsze miejsce na liście aukcji zarezerwowane jest dla opcji odświeżenia listy
     */

    ui->listWidget->addItem(OknoGlowne::ZMIENNA_ODSWIEZ);
    ui->listWidget->item(0)->setTextColor(QColor(0,75,200));
}

void OknoGlowne::zapelnij_liste_aukcji()
{
    /*!
     * Zapełnia listę dostępnych aukcji na podstawie danych pobranych z GAPa.
     */
    for(int i = 0; i < 5; i++)
    {
        ui->listWidget->addItem("Aukcja numer " + QString::number(i));
    }
}

void OknoGlowne::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    if(item->text() == OknoGlowne::ZMIENNA_ODSWIEZ)
    {
        //odswiez_liste_aukcji();
        ui->plainTextEdit->insertPlainText("Działa");
    }

}

void OknoGlowne::on_pushButton_2_clicked()
{
    /*!
     * Odpowiada za obsługę kliknięć tworzących nowe przetargi.
     *
     */
//    NowaAukcja dodaj_aukcje(this);
//    dodaj_aukcje.setModal(true);
    nowa = new NowaAukcja();
    nowa->setModal(true);
    connect(nowa,SIGNAL(nowa_aukcja(polaAukcji)),this,SLOT(zlap_nowa_aukcje(polaAukcji)));
    nowa->exec();

}

void OknoGlowne::zlap_nowa_aukcje(polaAukcji pA)
{
    /*!
      * Przechwytuje dane z okna dialogowego do stworzenia aukcji.
      */
    ui->plainTextEdit->insertPlainText(pA.nazwa_aukcji);
    ui->plainTextEdit->insertPlainText("\n");
    ui->plainTextEdit->insertPlainText(pA.opis_aukcji);
}
