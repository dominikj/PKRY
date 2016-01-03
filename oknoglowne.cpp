#include "oknoglowne.h"
#include "ui_oknoglowne.h"
#include <QList>
#include <QString>
#include <QListWidgetItem>
#include <QWidget>
#include <QMessageBox>
#include <QStringList>


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
//    for(int i = 0; i < 5; i++)
//    {
//        ui->listWidget->addItem("Aukcja numer " + QString::number(i));
//    }
//  test_start
    QString test = "nazwa=Test struktury aukcji;opis=Ten przetarg ma za zadanie sprawdzic, czy taka struktura danych moze bezbolesnie istniec. Lorem ipsum, costam costam.;data_roz=03:01:2016 18:26:35;data_zak=03:01:2016 18:31:35;kryteria={uroda,wdziek,powab}";
    polaAukcji stuk = konwertuj_do_struktury(test);
    stuk.numer_aukcji = "70088010";
    listaAktywnychAukcji.append(stuk);

//  test_end
    for(int i = 0; i < listaAktywnychAukcji.count();i++)
    {
        QString wpis;
        wpis = "(" + listaAktywnychAukcji[i].numer_aukcji + ")" + " " +listaAktywnychAukcji[i].nazwa_aukcji;
        ui->listWidget->addItem(wpis);
    }
}

OknoGlowne::polaAukcji OknoGlowne::konwertuj_do_struktury(QString wpis)
{
    polaAukcji struktura;
    QStringList cieta_struktura = wpis.split(";");
    for(int j = 0; j < cieta_struktura.count(); j++)
    {
        QStringList cieta_pozycja = cieta_struktura[j].split("=");
        if(cieta_pozycja[0] == "nazwa")
        {
            struktura.nazwa_aukcji = cieta_pozycja[1];
        }
        else if(cieta_pozycja[0] == "opis")
        {
            struktura.opis_aukcji = cieta_pozycja[1];
        }
        else if(cieta_pozycja[0] == "data_roz")
        {
            struktura.data_rozpoczecia = QDateTime::fromString(cieta_pozycja[1],QString("dd:MM:yyyy hh:mm:ss"));
        }
        else if(cieta_pozycja[0] == "data_zak")
        {
            struktura.data_zakonczenia  = QDateTime::fromString(cieta_pozycja[1],QString("dd:MM:yyyy hh:mm:ss"));
        }
        else if(cieta_pozycja[0] == "kryteria")
        {
            QString wyciete_nawiasy = cieta_pozycja[1].mid(1,cieta_pozycja[1].count()-2);
            QStringList pociete_kryteria = wyciete_nawiasy.split(",");
            for(int i = 0; i < pociete_kryteria.count();i++)
            {
                struktura.lista_kryteriow.append(pociete_kryteria[i]);
            }
        }
    }
    return struktura;
}

void OknoGlowne::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    if(item->text() == OknoGlowne::ZMIENNA_ODSWIEZ)
    {
        //odswiez_liste_aukcji();
        ui->plainTextEdit->insertPlainText("Działa");
    }
    else
    {
        //to tylko test, tu bedzie metoda zeby po kliknieciu pokazywalo dane aukcji
      ui->plainTextEdit->insertPlainText(listaAktywnychAukcji[0].nazwa_aukcji + "\n");
      ui->plainTextEdit->insertPlainText(listaAktywnychAukcji[0].opis_aukcji + "\n");
      ui->plainTextEdit->insertPlainText(listaAktywnychAukcji[0].data_rozpoczecia.toString(QString("dd:MM:yyyy hh:mm:ss")) + "\n");
      ui->plainTextEdit->insertPlainText(listaAktywnychAukcji[0].data_zakonczenia.toString(QString("dd:MM:yyyy hh:mm:ss")) + "\n");
      foreach(QString kryt, listaAktywnychAukcji[0].lista_kryteriow)
      {
        ui->plainTextEdit->insertPlainText(kryt + " ");
      }
      ui->plainTextEdit->insertPlainText("\n" + listaAktywnychAukcji[0].numer_aukcji);
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
