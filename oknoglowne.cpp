#include "oknoglowne.h"
#include "ui_oknoglowne.h"
#include <QList>
#include <QString>
#include <QListWidgetItem>
#include <QWidget>
#include <QMessageBox>
#include <QStringList>
#include "zlozoferte.h"
#include "tcp.h"
#include "szyfrowanie.h"
#include "sterownik.h"


QString OknoGlowne::ZMIENNA_ODSWIEZ = "ODŚWIEŻ...";
QString OknoGlowne::nr_aktywnej_aukcji = "0";

OknoGlowne::OknoGlowne(QWidget *parent, Sterownik &ster, Start& st) :
    QMainWindow(parent),
    ui(new Ui::OknoGlowne),
    _sterownik(ster),
    _start(st)
{
    ui->setupUi(this);
    connect(&_start,SIGNAL(uruchom(bool)),this,SLOT(uruchom(bool)));
    QList<QString> listaAukcji;
    pierwsze_miejsce_na_liscie_odswieza_liste_aukcji();
    QString test = "nr_aukcji=101;nazwa=Test struktury aukcji;opis=Ten przetarg ma za zadanie sprawdzic, czy taka struktura danych moze bezbolesnie istniec. Lorem ipsum, costam costam.;data_roz=03:01:2016 18:26:35;data_zak=03:01:2016 18:31:35;kryteria={uroda,wdziek,powab,sila,masa,biala,rasa,dobre uczynnki,bicek,kolor,folklor,ksztalt,zapach}::nr_aukcji=291;nazwa=Budowa mostu Krasińskiego;opis=Budowa mostu Krasińskiego. Cena 90%, liczba ofert 5%, czas 5%.;data_roz=03:01:2016 18:26:35;data_zak=03:02:2016 18:31:35;kryteria={cena,liczba ofert w ostatnich dwóch latach,czas wykonania}";
    zapelnij_liste_aukcji(test);
}

OknoGlowne::~OknoGlowne()
{
    delete ui;
}

void OknoGlowne::uruchom(bool t)
{
    this->show();
}

void OknoGlowne::pierwsze_miejsce_na_liscie_odswieza_liste_aukcji()
{
    /*!
     * Pierwsze miejsce na liście aukcji zarezerwowane jest dla opcji odświeżenia listy
     */

    ui->listWidget->addItem(OknoGlowne::ZMIENNA_ODSWIEZ);
    ui->listWidget->item(0)->setTextColor(QColor(0,75,200));
}

void OknoGlowne::zapelnij_liste_aukcji(QString lista_aukcji)
{
    /*!
     * Zapełnia listę dostępnych aukcji na podstawie danych pobranych z GAPa.
     *
     *
     */
    QStringList aukcje_lista = lista_aukcji.split("::");
    for(int i = 0; i < aukcje_lista.count(); i++)
    {
        polaAukcji stuk = konwertuj_do_struktury(aukcje_lista[i]);
        bazaAktywnychAukcji.insert(stuk.numer_aukcji,stuk);
        QString wpis;
        wpis = "(" + stuk.numer_aukcji + ") " + bazaAktywnychAukcji.value(stuk.numer_aukcji).nazwa_aukcji;
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
        if (cieta_pozycja[0] == "nr_aukcji")
        {
            struktura.numer_aukcji = cieta_pozycja[1];
        }
        else if(cieta_pozycja[0] == "nazwa")
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
    ui->plainTextEdit->clear();
    if(item->text() == OknoGlowne::ZMIENNA_ODSWIEZ)
    {
        //odswiez_liste_aukcji();
        ui->plainTextEdit->insertPlainText("Działa");
    }
    else
    {
      QString nr_aukcji = item->text().mid(1,item->text().indexOf(")")-1);
      OknoGlowne::nr_aktywnej_aukcji = nr_aukcji;
      ui->plainTextEdit->insertPlainText("Nazwa aukcji: " + bazaAktywnychAukcji.value(nr_aukcji).nazwa_aukcji + "\n");
      ui->plainTextEdit->insertPlainText("Opis aukcji: " + bazaAktywnychAukcji.value(nr_aukcji).opis_aukcji + "\n");
      ui->plainTextEdit->insertPlainText("Data rozpoczęcia: " + bazaAktywnychAukcji.value(nr_aukcji).data_rozpoczecia.toString(QString("dd:MM:yyyy hh:mm:ss")) + "\n");
      ui->plainTextEdit->insertPlainText("Data zakończenia: " + bazaAktywnychAukcji.value(nr_aukcji).data_zakonczenia.toString(QString("dd:MM:yyyy hh:mm:ss")) + "\n");
      ui->plainTextEdit->insertPlainText("Kryteria:");
      ui->plainTextEdit->insertPlainText("\n");
      foreach(QString kryt, bazaAktywnychAukcji.value(nr_aukcji).lista_kryteriow)
      {
        ui->plainTextEdit->insertPlainText("*" + kryt + "\n");
      }
      ui->plainTextEdit->insertPlainText("\n");
      ui->plainTextEdit->insertPlainText("Numer aukcji: " + bazaAktywnychAukcji.value(nr_aukcji).numer_aukcji);
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
    QString _nowaAukcja = przygotuj_dane_aukcji_do_wyslania(pA);
    if(_sterownik.wykonajPodProt2(_nowaAukcja) == true)
        QMessageBox::information(this,"OK","Aukcja dodana");
}

void OknoGlowne::on_pushButton_clicked()
{
    /*!
     * Przygotowuje dialog z możliwością złożenia oferty
     */
    if(OknoGlowne::nr_aktywnej_aukcji != "0")
    {
        oknooferty = new zlozOferte();
        polaAukcji test = bazaAktywnychAukcji.value(OknoGlowne::nr_aktywnej_aukcji);
        oknooferty->wez_dane_aukcji(test.numer_aukcji,test.nazwa_aukcji,test.data_zakonczenia,test.lista_kryteriow);
        oknooferty->setModal(true);
        connect(oknooferty,SIGNAL(skladanie_oferty(QString)),this,SLOT(zlap_nowa_oferte(QString)));
        connect(this,SIGNAL(odpowiedz_serwera(QString,bool)),oknooferty,SLOT(odpowiedz_od_serwera(QString,bool)));
        oknooferty->exec();
    }
}

void OknoGlowne::zlap_nowa_oferte(QString of)
{
    QMessageBox::critical(this,"Oj",of);

    //tutaj przerzucic do sterownika i dalej
    //if odpowiedz od serwera ok (albo nie)
    emit odpowiedz_serwera("Nie zlozysz oferty serwerowi, ktorego nie ma.",false);
}

void OknoGlowne::on_pushButton_3_clicked()
{
    wyborzwyciezcy = new WybierzZwyciezce();
    wyborzwyciezcy->setModal(true);
    wyborzwyciezcy->exec();
}

QString OknoGlowne::przygotuj_dane_aukcji_do_wyslania(polaAukcji &pA)
{
    /*!
     * Wstępnie zwalidowane dane przygotowuje w postaci stringa do wysłania na serwer
     * \brief wynik
     */
    QString wynik;
    wynik = wynik + "nazwa=" + pA.nazwa_aukcji + ";";
    wynik = wynik + "opis=" + pA.opis_aukcji + ";";
    wynik = wynik + "data_roz=" + pA.data_rozpoczecia.toString(QString("dd:MM:yyyy hh:mm:ss")) + ";";
    wynik = wynik + "data_zak=" + pA.data_zakonczenia.toString(QString("dd:MM:yyyy hh:mm:ss")) + ";";
    wynik = wynik + "kryteria={";
    for(int i = 0; i < pA.lista_kryteriow.count();i++)
    {
        if (i == pA.lista_kryteriow.count()-1)
        {
            wynik = wynik + pA.lista_kryteriow[i];
        }
        else
            wynik = wynik + pA.lista_kryteriow[i] + ",";
    }
    wynik = wynik + "}";
    QMessageBox::critical(this,"Oj",wynik);
    return wynik;
}
