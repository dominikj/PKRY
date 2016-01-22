#include "oknoglowne.h"
#include "ui_oknoglowne.h"
#include <QList>
#include <QString>
#include <QListWidgetItem>
#include <QWidget>
#include <QMessageBox>
#include <QStringList>
#include "zlozoferte.h"
#include "utils/tcp.h"
#include "utils/szyfrowanie.h"
#include "sterownik/sterownik.h"
#include <QObject>

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
    ui->listWidget->addItem(OknoGlowne::ZMIENNA_ODSWIEZ);
    ui->listWidget->item(0)->setTextColor(QColor(0,75,200));
}

OknoGlowne::~OknoGlowne()
{
    delete ui;
}
/**
 * @brief Funkcja wykonywana przy uruchomieniu aplikacji
 * @param t
 */
void OknoGlowne::uruchom(bool t)
{
    this->show();
    ui->textEdit->insertPlainText(_sterownik.daneKonsola());
}
/**
 * @brief Funckja odpowiedzialna za odświeżanie listy ofert
 * @param item
 */
void OknoGlowne::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    ui->textEdit->insertPlainText(_sterownik.daneKonsola());
    ui->textEdit->repaint();

    QString itemText;
    std::vector<Aukcja> aukcje;

    if((itemText= item->text()) == ZMIENNA_ODSWIEZ)
    {
        ui->listWidget->clear();
        ui->listWidget->addItem(ZMIENNA_ODSWIEZ);


    if(ocz != nullptr)
        ocz->blokada = true; // teraz nie nasłuchujemy ofert/ogłoszenia zwycięzcy

    ui->plainTextEdit->clear();
    nr_aktywnej_aukcji = "0";
    try {
        aukcje =  _sterownik.pobierzAukcjeZSerwera();
    }
    catch(...) {
         QMessageBox::critical(this,"Błąd","Nie udało się pobrać danych z serwera");
        return;
    }
    }
    else{ aukcje = _sterownik.pobierzAukcje(); }

    for(auto au : aukcje) {
        auto dane = au.parametry;
        QByteArrayList pola = dane.split(';');
        if( itemText == ZMIENNA_ODSWIEZ) {
            QString tmp = pola.at(0).split('=').at(1);
            tmp = tmp.replace("\v",";");
            tmp = tmp.replace("\e","::");
            ui->listWidget->addItem("(" + au.numer + ")" + tmp);
        }
        else if (itemText.split(")").at(0).mid(1,-1) == au.numer ) {
            nr_aktywnej_aukcji = au.numer;
            polaAukcji pAukc;
            pAukc.numer_aukcji = nr_aktywnej_aukcji;
            pAukc.nazwa_aukcji = pola.at(0).split('=').at(1);
            pAukc.nazwa_aukcji = pAukc.nazwa_aukcji.replace("\v",";");
            pAukc.nazwa_aukcji = pAukc.nazwa_aukcji.replace("\e","::");
            ui->plainTextEdit->insertPlainText("Nazwa aukcji: " +  pAukc.nazwa_aukcji  + "\n");
            pAukc.opis_aukcji = pola.at(1).split('=').at(1);
            pAukc.opis_aukcji = pAukc.opis_aukcji.replace("\v",";");
            pAukc.opis_aukcji = pAukc.opis_aukcji.replace("\e","::");
            ui->plainTextEdit->insertPlainText("Opis aukcji: " +  pAukc.opis_aukcji + "\n");
            pAukc.data_zakonczenia =  pola.at(2).split('=').at(1);
            ui->plainTextEdit->insertPlainText("Data zakończenia: " +  pAukc.data_zakonczenia + "\n");
            pAukc.lista_kryteriow = pola.at(3).split('=').at(1).mid(1,pola.at(3).split('=').at(1).size() -2).split(',');
            QString tmp = pola.at(3).split('=').at(1);
            tmp = tmp.replace("\v",",");
            tmp = tmp.replace("\e","::");
            ui->plainTextEdit->insertPlainText("Kryteria:" + tmp);
            ui->plainTextEdit->insertPlainText("\n");
            bazaAktywnychAukcji.clear();
            bazaAktywnychAukcji.insert(nr_aktywnej_aukcji, pAukc);
        }
    }
    if(ocz != nullptr)
        ocz->blokada = false;
}

void OknoGlowne::on_pushButton_2_clicked()
{
    /*!
     * Odpowiada za obsługę kliknięć tworzących nowe przetargi.
     *
     */
   // destroyed(ocz);
    if(ocz != nullptr)
    ocz->blokada=true;
    nowa = new NowaAukcja(_sterownik,0);
    connect(nowa,SIGNAL(nowa_aukcja(polaAukcji)),this,SLOT(zlap_nowa_aukcje(polaAukcji)));
    nowa->setModal(true);
    nowa->exec();

}

void OknoGlowne::zlap_nowa_aukcje(polaAukcji pA)
{
    /*!
      * Przechwytuje dane z okna dialogowego do stworzenia aukcji.
    */
    /*  qDebug() << "ZLAPALEM"; - Wywala cały system XD */
    ui->textEdit->insertPlainText(_sterownik.daneKonsola());
    ui->textEdit->repaint();
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_2->repaint();
    ui->pushButton->setEnabled(false);
    ui->pushButton->repaint();
    ocz= _sterownik.czekajNaZwyciezce();
    ocz->czyFirma = true;
    connect(ocz, SIGNAL(alertZwyciezca(QString)), this, SLOT(przyszlyOferty(QString)));


}

void OknoGlowne::on_pushButton_clicked()
{
    /*!
     * Przygotowuje dialog z możliwością złożenia oferty
     */

    if(OknoGlowne::nr_aktywnej_aukcji != "0")
    {
          // destroyed(ocz);
        if(ocz != nullptr)
        ocz->blokada=true;
        oknooferty = new zlozOferte();
        polaAukcji test = bazaAktywnychAukcji.value(OknoGlowne::nr_aktywnej_aukcji);
        oknooferty->wez_dane_aukcji(test.numer_aukcji,test.nazwa_aukcji,test.data_zakonczenia,test.lista_kryteriow);
        oknooferty->setModal(true);
        connect(oknooferty,SIGNAL(skladanie_oferty(QString)),this,SLOT(zlap_nowa_oferte(QString)));
        oknooferty->exec();
        if(ocz != nullptr)
        ocz->blokada=false;
    }
}
/**
 * @brief Funkcja odpowiedzialna za ustawienia GUI i uruchomienie wysyłania oferty do GAP
 * @param of
 */
void OknoGlowne::zlap_nowa_oferte(QString of)
{
    if(ocz != nullptr)
    ocz->blokada=true;
    ui->textEdit->repaint();
    if (_sterownik.wyslijOferte(of,nr_aktywnej_aukcji)) {
        ui->pushButton->setEnabled(false);
        ui->pushButton->repaint();
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_2->repaint();
        QMessageBox::information(this,"OK","Zaakceptowano ofertę");
        ocz= _sterownik.czekajNaZwyciezce();
        ocz->czyFirma = false;
        connect(ocz, SIGNAL(alertZwyciezca(QString)), this, SLOT(przyszlyOferty(QString)));
    }
    else
        QMessageBox::critical(this,"Bład","Odrzucono ofertę");
    ui->textEdit->insertPlainText(_sterownik.daneKonsola());
    if(ocz != nullptr)
    ocz->blokada=false;
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
    wynik = wynik + "data_zak=" + pA.data_zakonczenia + ";";
    wynik = wynik + "kryteria={";
    for(int i = 0; i < pA.lista_kryteriow.count(); i++)
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

void OknoGlowne::wybierz_zwyciezce_wyswietl_okno(QString wZ)
{
    wyborzwyciezcy = new WybierzZwyciezce();
    wyborzwyciezcy->setModal(true);
    wyborzwyciezcy->exec();
}
/**
 * @brief Funkcja jest wołana gdy przyjdą oferty do rozpatrzenia. Odpowiada za uruchomienie okna wyboru oferty
 * @param o
 */
void OknoGlowne::przyszlyOferty(QString o) {
    if (ocz->czyFirma && o != "ERR") {
        ocz->blokada = true;
        wyborzwyciezcy = new WybierzZwyciezce();
        connect(wyborzwyciezcy,SIGNAL(info_dla_sterownika(QString)),&_sterownik,SLOT(wyborZwyciezcy(QString)));
        wyborzwyciezcy->wyswietl_okno(_sterownik.oferty());
        wyborzwyciezcy->setModal(true);
        wyborzwyciezcy->exec();
        ui->pushButton->setEnabled(true);
        ui->pushButton->repaint();
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_2->repaint();
     ui->textEdit->insertPlainText(_sterownik.daneKonsola());
    }
    else if(o == "ERR"){
        qDebug()<<o;
        ui->pushButton->setEnabled(true);
        ui->pushButton->repaint();
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_2->repaint();
       ui->textEdit->insertPlainText(_sterownik.daneKonsola());
    }
    else if(ocz->czyFirma == false) {
        ui->pushButton->setEnabled(true);
        ui->pushButton->repaint();
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_2->repaint();
     ui->textEdit->insertPlainText(_sterownik.daneKonsola());
    }
    return;
}
