
#include "nowaaukcja.h"
#include "ui_nowaaukcja.h"
#include <QInputDialog>
#include <QMessageBox>
#include "sterownik/sterownik.h"
/**
 * @brief konstruktor
 * @param ster referencja na sterownik aplikacji
 * @param parent
 */
NowaAukcja::NowaAukcja( Sterownik& ster, QWidget *parent) : QDialog(parent), _ster(ster), ui(new Ui::NowaAukcja)
{
    ui->setupUi(this);
    ui->dateTimeEdit_2->setMinimumDate(QDate::currentDate());
    ui->dateTimeEdit_2->setMinimumDateTime(QDateTime::currentDateTime());
}

NowaAukcja::~NowaAukcja()
{
    delete ui;
}
/**
 * @brief Funkcja wywoływana przy naciśnięciu przycisku Wróć
 */
void NowaAukcja::on_pushButton_3_clicked()
{

    this->close();
}
/**
 * @brief Funkcja wywoływana przy naciśnięciu przycisku dodania nowego kryterium
 */
void NowaAukcja::on_pushButton_clicked()
{
    bool ok;
    QString nowe_kryterium = QInputDialog::getText(this,tr("Dodaj nowe kryterium"),tr("Podaj nazwę dla kryterium:"),QLineEdit::Normal,QString("Nowe kryterium"),&ok);
    if(ok && !nowe_kryterium.isEmpty())
    {
        ui->listWidget->addItem(nowe_kryterium);
    }
}
/**
 * @brief Funkcja Uruchamiana przy naciśnięciu przycisku usuwającego kryterium
 */
void NowaAukcja::on_pushButton_4_clicked()
{
    QListWidgetItem *it = ui->listWidget->item(ui->listWidget->currentRow());
    delete it;
}
/**
 * @brief Funkcja wysyłająca zgłoszenie nowej aukcji do GAP
 */
void NowaAukcja::on_pushButton_2_clicked()
{
    if(ui->lineEdit->text().isEmpty())
    {
        QMessageBox::critical(this,"Oj","Aukcja nie może pozostać anonimowa. Proszę, wpisz jej nazwę.");
    }
    else if(ui->listWidget->count() < 1)
    {
        QMessageBox::critical(this,"Oj","Co to za przetarg, kiedy nie ma kryterium? Proszę, dodaj co najmniej jedno.");
    }
    else
    {
        pola_aukcji.nazwa_aukcji = ui->lineEdit->text();
        pola_aukcji.opis_aukcji = ui->textEdit->toPlainText();
        pola_aukcji.data_zakonczenia = ui->dateTimeEdit_2->dateTime();
        pola_aukcji.lista_kryteriow.clear();
        for(int i = 0; i < ui->listWidget->count(); i++)
        {
            pola_aukcji.lista_kryteriow.append(ui->listWidget->item(i)->text());
        }
        //Teraz to trzeba jakoś zserializować i przesłać jako WPf
        if( _ster.dodajAukcje(przygotuj_dane_aukcji_do_wyslania(pola_aukcji))) {
            QMessageBox::information(this,"OK","Aukcja dodana");
            emit nowa_aukcja(pola_aukcji);
            this->close();
        }
        else {
            QMessageBox::critical(this,"Bład","Odrzucono aukcję");
        }
    }
}
/**
 * @brief Wstępne przygotowanie oferty do transmisji
 * @param pA
 * @return
 */
QString NowaAukcja::przygotuj_dane_aukcji_do_wyslania(polaAukcji &pA)
{

    QString wynik;
    pA.nazwa_aukcji =  pA.nazwa_aukcji.replace(";","\v");
    pA.nazwa_aukcji =  pA.nazwa_aukcji.replace("::","\e");
    wynik = wynik + "nazwa=" + pA.nazwa_aukcji + ";";
    pA.opis_aukcji = pA.opis_aukcji.replace(";","\v");
    pA.opis_aukcji = pA.opis_aukcji.replace("::","\e");
    wynik = wynik + "opis=" + pA.opis_aukcji + ";";
    wynik = wynik + "data_zak=" + pA.data_zakonczenia.toString(QString("dd:MM:yyyy hh:mm:ss")) + ";";
    wynik = wynik + "kryteria={";
    for(int i = 0; i < pA.lista_kryteriow.count(); i++)
    {
        pA.lista_kryteriow[i] = pA.lista_kryteriow[i].replace(",","\v");
        pA.lista_kryteriow[i] = pA.lista_kryteriow[i].replace("::","\e");
        if (i == pA.lista_kryteriow.count()-1)
        {
            wynik = wynik + pA.lista_kryteriow[i];
        }
        else
            wynik = wynik + pA.lista_kryteriow[i] + ",";
    }
    wynik = wynik + "}";
    QMessageBox::critical(this,"Dane aukcji",wynik);

    return wynik;
}

