#include "wybierzzwyciezce.h"
#include "ui_wybierzzwyciezce.h"
#include <QMessageBox>
#include <assert.h>


WybierzZwyciezce::WybierzZwyciezce(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WybierzZwyciezce)
{
    ui->setupUi(this);
}

//Postać stringa od GAPa:
//nr_aukcji=1111::{nr_oferenta=2222;nr_oferty=3333;kryt1=wart1;kryt2=wart2}::{nr_oferenta=4444;nr_oferty=5555;kryt1=wart3;kryt2=wart4}
/**
 * @brief Funkcja obrabiająca listę ofert odebraną od GAP przed wyświetleniem
 * @param lista ofert
 */
void WybierzZwyciezce::przekaz_liste_ofert(QString string_lista_ofert)
{   qDebug() << "Wprowadzam dane";
    QStringList lista_string_lista_ofert = string_lista_ofert.split("::",QString::SkipEmptyParts);
    numer_aukcji = lista_string_lista_ofert[0];
    qDebug() << numer_aukcji;
    for(int i = 1; i < lista_string_lista_ofert.count(); i++)
    {
        oferta of;
        QStringList oferta = lista_string_lista_ofert[i].mid(1,lista_string_lista_ofert[i].count()-2).split(";");
        //oferta -> nr_oferenta=2222, nr_oferty=333, kryt1=wart1 itd.
        QString temp = oferta[0].split("=")[1];
        of.Non = temp;
        lista_numerow_oferentow.append(temp);
        qDebug() << temp;
        of.NRo = oferta[1].split("=")[1];
        oferty.push_back(of);
        for(int j = 2; j < oferta.count(); j++)
        {
            temp = temp + " " + oferta[j].split("=")[0].replace("\e","::").replace("\v",";") + ": " + oferta[j].split("=")[1].replace("\e","::").replace("\v",";");
        }
        lista_ofert.append(temp);
        qDebug() << temp;
    }
}
/**
 * @brief Funkcja wyświetlająca listę dostępnych ofert
 */
void WybierzZwyciezce::wyswietl_oferty()
{
    if(lista_ofert.count()==0)
    {
        QMessageBox::critical(this,"Brak ofert","Zbyt mało ofert. Aukcja nierozstrzygnięta.");
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
            this->show();
        }
    }
    ui->comboBox->addItems(lista_numerow_oferentow);
}

WybierzZwyciezce::~WybierzZwyciezce()
{
    delete ui;
}
/**
 * @brief Funkcja wykonywana po naciśnięciu przycisku wyboru zwycięzcy
 */
void WybierzZwyciezce::on_pushButton_clicked()
{
    QString zwycieza = ui->comboBox->currentText();
    QString zwyciezcaNR;
    QString odp;
    for(oferta of : oferty) {
        odp += of.Non +"\t";
        if(of.Non == zwycieza)
            zwyciezcaNR = of.NRo;
    }
    odp += ";" + zwyciezcaNR + "\t" +numer_aukcji.split("=").at(1);
    QMessageBox::information(this,"zwyciezca",zwycieza);
    oferty.clear();
    emit info_dla_sterownika(odp);
    this->close();
}

void WybierzZwyciezce::wyswietl_okno(QString dane)
{
    this->przekaz_liste_ofert(dane);
    this->wyswietl_oferty();
}

