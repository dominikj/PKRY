#include "nowaaukcja.h"
#include "ui_nowaaukcja.h"
#include <QInputDialog>
#include <QMessageBox>

NowaAukcja::NowaAukcja(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NowaAukcja)
{
    /*!
     * Konstruktor okna dialogowego z możliwością dodania nowej aukcji. Ustawia pola daty na obecny dzień i godzinę.
     *
     */
    ui->setupUi(this);
    ui->dateTimeEdit->setMinimumDate(QDate::currentDate());
    ui->dateTimeEdit_2->setMinimumDate(QDate::currentDate());
    ui->dateTimeEdit->setMinimumDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_2->setMinimumDateTime(QDateTime::currentDateTime());
}

NowaAukcja::~NowaAukcja()
{
    delete ui;
}

void NowaAukcja::on_pushButton_3_clicked()
{
    /*!
      * Po otwarciu okna dialogowego z dodaniem nowej aukcji, umożliwia powrót do menu głównego.
      *
      */
    this->close();
}

void NowaAukcja::on_pushButton_clicked()
{
    /*!
     * Wyświetla okno dialogowe z możliwością dodania nowego kryterium przetargu.
     *
     */
    bool ok;
    QString nowe_kryterium = QInputDialog::getText(this,tr("Dodaj nowe kryterium"),tr("Podaj nazwę dla kryterium:"),QLineEdit::Normal,QString("Nowe kryterium"),&ok);
    if(ok && !nowe_kryterium.isEmpty())
    {
        ui->listWidget->addItem(nowe_kryterium);
    }
}

void NowaAukcja::on_pushButton_4_clicked()
{
    /*!
     * Usuwa wybrane kryterium z listy kryteriów przetargu.
     */
    //delete ui->listWidget->takeItem(ui->listWidget->selectedItems().count());
    QListWidgetItem *it = ui->listWidget->item(ui->listWidget->currentRow());
    delete it;
}

void NowaAukcja::on_pushButton_2_clicked()
{
    /*!
     * Po kliknięciu następuje mała walidacja wpisanych pól, następnie dane są pobierane i wysyłane do GAPa.
     */
    if(ui->lineEdit_2->text().isEmpty())
    {
        QMessageBox::critical(this,"Oj","Numer aukcji jest niezbędny, by mogła zostać ona stworzona na serwerze.");
    }
    else if(ui->lineEdit->text().isEmpty())
    {
        QMessageBox::critical(this,"Oj","Aukcja nie może pozostać anonimowa. Proszę, wpisz jej nazwę.");
    }
    else if(ui->dateTimeEdit->dateTime()>ui->dateTimeEdit_2->dateTime())
    {
        QMessageBox::critical(this,"Oj","Aukcja nie może zakończyć się przed jej rozpoczęciem. Proszę, zwróć uwagę na ustawione daty.");
    }
    else if(ui->listWidget->count() < 1)
    {
        QMessageBox::critical(this,"Oj","Co to za przetarg, kiedy nie ma kryterium? Proszę, dodaj co najmniej jedno.");
    }
    else
    {
        pola_aukcji.numer_aukcji = ui->lineEdit_2->text();
        pola_aukcji.nazwa_aukcji = ui->lineEdit->text();
        pola_aukcji.opis_aukcji = ui->textEdit->toPlainText();
        pola_aukcji.data_rozpoczecia = ui->dateTimeEdit->dateTime();
        pola_aukcji.data_zakonczenia = ui->dateTimeEdit_2->dateTime();
//        QString nazwa_aukcji = ui->lineEdit->text();
//        QString opis_aukcji = ui->textEdit->toPlainText();
//        QDateTime data_rozpoczecia = ui->dateTimeEdit->dateTime();
//        QDateTime data_zakonczenia = ui->dateTimeEdit_2->dateTime();
//        QList<QString> lista_kryteriow;
        for(int i = 0; i < ui->listWidget->count(); i++)
        {
            pola_aukcji.lista_kryteriow.append(ui->listWidget->item(i)->text());
        }
        //Teraz to trzeba jakoś zserializować i przesłać jako WPf
        //przygotuj_dane_aukcji_do_wyslania(pola_aukcji);
        emit nowa_aukcja(pola_aukcji);
        this->close();
    }
}

//QString NowaAukcja::przygotuj_dane_aukcji_do_wyslania(polaAukcji &pA)
//{
//    /*!
//     * Wstępnie zwalidowane dane przygotowuje w postaci stringa do wysłania na serwer
//     * \brief wynik
//     */
//    QString wynik;
//    wynik = wynik + "nazwa=" + pA.nazwa_aukcji + ";";
//    wynik = wynik + "opis=" + pA.opis_aukcji + ";";
//    wynik = wynik + "data_roz=" + pA.data_rozpoczecia.toString(QString("dd:MM:yyyy hh:mm:ss")) + ";";
//    wynik = wynik + "data_zak=" + pA.data_zakonczenia.toString(QString("dd:MM:yyyy hh:mm:ss")) + ";";
//    wynik = wynik + "kryteria={";
//    for(int i = 0; i < pA.lista_kryteriow.count();i++)
//    {
//        if (i == pA.lista_kryteriow.count()-1)
//        {
//            wynik = wynik + pA.lista_kryteriow[i];
//        }
//        else
//            wynik = wynik + pA.lista_kryteriow[i] + ",";
//    }
//    wynik = wynik + "}";
//    QMessageBox::critical(this,"Oj",wynik);
//    return wynik;
//}
