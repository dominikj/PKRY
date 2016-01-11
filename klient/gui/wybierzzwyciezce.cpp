#include "wybierzzwyciezce.h"
#include "ui_wybierzzwyciezce.h"
#include <QMessageBox>

WybierzZwyciezce::WybierzZwyciezce(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WybierzZwyciezce)
{
    ui->setupUi(this);
    //przekaz_liste_ofert("nr_aukcji=1111::{nr_oferenta=2222;nr_oferty=3333;kryt1=wart1;kryt2=wart2}::{nr_oferenta=4444;nr_oferty=5555;kryt1=wart3;kryt2=wart4}");
    //wyswietl_oferty();
}

//Postać stringa od GAPa:
//nr_aukcji=1111::{nr_oferenta=2222;nr_oferty=3333;kryt1=wart1;kryt2=wart2}::{nr_oferenta=4444;nr_oferty=5555;kryt1=wart3;kryt2=wart4}
void WybierzZwyciezce::przekaz_liste_ofert(QString string_lista_ofert)
{
    QStringList lista_string_lista_ofert = string_lista_ofert.split("::",QString::SkipEmptyParts);
    numer_aukcji = lista_string_lista_ofert[0];
    for(int i = 1; i < lista_string_lista_ofert.count(); i++)
    {
        QStringList oferta = lista_string_lista_ofert[i].mid(1,lista_string_lista_ofert[i].count()-2).split(";");
        //oferta -> nr_oferenta=2222, nr_oferty=333, kryt1=wart1 itd.
        QString temp = oferta[0].split("=")[1];
        lista_numerow_oferentow.append(temp);
        temp = "Numer oferty: " + oferta[1].split("=")[1];
        for(int j = 2; j < oferta.count(); j++)
        {
            temp = temp + " " + oferta[j].split("=")[0] + ": " + oferta[j].split("=")[1];
        }
        lista_ofert.append(temp);
    }
}

void WybierzZwyciezce::wyswietl_oferty()
{
    if(lista_ofert.count()==0)
    {
        QMessageBox::critical(this,"Brak ofert","Nikt się nie zgłosił. Aukcja nierozstrzygnięta.");
        this->close();
    }
    else
    {
        for(int i = 0; i < lista_ofert.count(); i++)
        {
            ui->textEdit->insertPlainText("Nr oferenta " + lista_numerow_oferentow[i]);
            ui->textEdit->insertPlainText("\n");
            ui->textEdit->insertPlainText(lista_ofert[i]);
            ui->textEdit->insertPlainText("\n");
        }
        ui->comboBox->addItems(lista_numerow_oferentow);
//        for(int i = 0; i < lista_numerow_ofert.count(); i++)
//        {

//        }
    }
}

WybierzZwyciezce::~WybierzZwyciezce()
{
    delete ui;
}

void WybierzZwyciezce::on_pushButton_clicked()
{
    QString zwycieza = ui->comboBox->currentText();
    QString oferty_wziete_pod_uwage;
    for (int i = 0; i < lista_numerow_oferentow.count(); i++)
    {
        oferty_wziete_pod_uwage = oferty_wziete_pod_uwage + ", " + lista_numerow_oferentow[i];
    }
    QMessageBox::information(this,"zwyciezca",zwycieza);
    emit info_dla_sterownika(zwycieza,oferty_wziete_pod_uwage);
    //this->close();
}

void WybierzZwyciezce::wyswietl_okno(QString dane)
{
    this->przekaz_liste_ofert(dane);
    this->wyswietl_oferty();
    this->show();
}

void WybierzZwyciezce::odpowiedz_serwera(QString odpowiedz)
{
    //JEŚLI SERWER MÓWI OK, TO ZAMYKAMY
    //JEŚLI SERWER MÓWI, ŻE NIE OK TO WRZUCAMY MESSAGEBOKSA
    //ALE NA RAZIE SERWER NIE ISTNIEJE
    this->close();
}
