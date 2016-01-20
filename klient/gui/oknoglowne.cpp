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
    QList<QString> listaAukcji;
    pierwsze_miejsce_na_liscie_odswieza_liste_aukcji();
    QString test = "nr_aukcji=101;nazwa=Test struktury aukcji;opis=Ten przetarg ma za zadanie sprawdzic, czy taka struktura danych moze bezbolesnie istniec. Lorem ipsum, costam costam.;data_roz=03:01:2016 18:26:35;data_zak=03:01:2016 18:31:35;kryteria={uroda,wdziek,powab,sila,masa,biala,rasa,dobre uczynnki,bicek,kolor,folklor,ksztalt,zapach}::nr_aukcji=291;nazwa=Budowa mostu Krasińskiego;opis=Budowa mostu Krasińskiego. Cena 90%, liczba ofert 5%, czas 5%.;data_roz=03:01:2016 18:26:35;data_zak=03:02:2016 18:31:35;kryteria={cena,liczba ofert w ostatnich dwóch latach,czas wykonania}";
  //  zapelnij_liste_aukcji(test);
}

OknoGlowne::~OknoGlowne()
{
    delete ui;
}

void OknoGlowne::uruchom(bool t)
{
    this->show();
        ui->textEdit->insertPlainText(_sterownik.daneKonsola());
}
/**
 * @brief OknoGlowne::pierwsze_miejsce_na_liscie_odswieza_liste_aukcji
 * @param sdf
 * @return
 */
void OknoGlowne::pierwsze_miejsce_na_liscie_odswieza_liste_aukcji()
{
    /**
     * Pierwsze miejsce na liście aukcji zarezerwowane jest dla opcji odświeżenia listy
     */

    ui->listWidget->addItem(OknoGlowne::ZMIENNA_ODSWIEZ);
    ui->listWidget->item(0)->setTextColor(QColor(0,75,200));
}

void OknoGlowne::zapelnij_liste_aukcji(QString lista_aukcji)
{
}

void OknoGlowne::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    ui->textEdit->insertPlainText(_sterownik.daneKonsola());
    ui->textEdit->repaint();
    if(ocz != nullptr)
    ocz->blokada = true; // teraz nie nasłuchujemy ofert/ogłoszenia zwycięzcy
    //FIXME: Teraz to za każdym razem pobieram od nowa dane, czy klikam na odśwież, czy na inną pozycję (chociaż w bazie mam zapisane aukcje... ale nie ma czasu w tym momencie na to)
    std::vector<Aukcja> aukcje;
    ui->plainTextEdit->clear();
    nr_aktywnej_aukcji = "0";
    try{  aukcje =  _sterownik.pobierzAukcje();}
    catch(...){
        return;
    }

    QString itemText;
    if((itemText= item->text()) == ZMIENNA_ODSWIEZ)
    {
        ui->listWidget->clear();
        ui->listWidget->addItem(ZMIENNA_ODSWIEZ);
    }

    for(auto au : aukcje){
    auto dane = au.parametry;
    QByteArrayList pola = dane.split(';');
     if( itemText == ZMIENNA_ODSWIEZ){
              ui->listWidget->addItem("(" + au.numer + ")" + pola.at(0).split('=').at(1));
      }
     else if (itemText.split(")").at(0).mid(1,-1) == au.numer ){
         nr_aktywnej_aukcji = au.numer;
         polaAukcji pAukc;
         pAukc.numer_aukcji = nr_aktywnej_aukcji;
         pAukc.nazwa_aukcji = pola.at(0).split('=').at(1);
     ui->plainTextEdit->insertPlainText("Nazwa aukcji: " +  pAukc.nazwa_aukcji  + "\n");
         pAukc.opis_aukcji = pola.at(1).split('=').at(1);
     ui->plainTextEdit->insertPlainText("Opis aukcji: " +  pAukc.opis_aukcji + "\n");
     pAukc.data_zakonczenia =  pola.at(2).split('=').at(1);
     ui->plainTextEdit->insertPlainText("Data zakończenia: " +  pAukc.data_zakonczenia + "\n");
     pAukc.lista_kryteriow = pola.at(3).split('=').at(1).mid(1,pola.at(3).split('=').at(1).size() -2).split(',');
     ui->plainTextEdit->insertPlainText("Kryteria:" + pola.at(3).split('=').at(1));
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

  //  QString nowaAukcja = przygotuj_dane_aukcji_do_wyslania(pA);


}

void OknoGlowne::on_pushButton_clicked()
{
    /*!
     * Przygotowuje dialog z możliwością złożenia oferty
     */
    //QString of = "nr_aukcji=213123::nr_uczes=1232112;nr_of=32423423;kryt1=sdfsdfs;kryt2=ssdfsdf";

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
    ui->textEdit->insertPlainText(_sterownik.daneKonsola());
    ui->textEdit->repaint();
   if (_sterownik.wyslijOferte(of,nr_aktywnej_aukcji)){
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
    //wynik = wynik + "data_roz=" + pA.data_rozpoczecia.toString(QString("dd:MM:yyyy hh:mm:ss")) + ";";
    wynik = wynik + "data_zak=" + pA.data_zakonczenia + ";";
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

void OknoGlowne::wybierz_zwyciezce_wyswietl_okno(QString wZ)
{
    wyborzwyciezcy = new WybierzZwyciezce();
    wyborzwyciezcy->setModal(true);
    wyborzwyciezcy->exec();
}
void OknoGlowne::przyszlyOferty(QString oferty){
       if (ocz->czyFirma){
           wyborzwyciezcy = new WybierzZwyciezce();
            connect(wyborzwyciezcy,SIGNAL(info_dla_sterownika(QString)),&_sterownik,SLOT(wyborZwyciezcy(QString)));
              wyborzwyciezcy->wyswietl_okno(_sterownik.oferty());
           wyborzwyciezcy->setModal(true);
           wyborzwyciezcy->exec();
       }
}
