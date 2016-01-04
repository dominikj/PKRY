#include "start.h"
#include "ui_start.h"
#include <QMessageBox>
#include <iostream>
#include "tcp.h"
#include "szyfrowanie.h"
#include "sterownik.h"

bool Start::poprawne_logowanie = false;


Start::Start(QWidget *parent, Sterownik& ster) :
    QMainWindow(parent),
    ui(new Ui::Start),
    _sterownik(ster)
{
    ui->setupUi(this);
}

Start::~Start()
{
    delete ui;
}

void Start::on_pushButton_2_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
}

void Start::on_pushButton_clicked()
{

 /*   QString dane = "Testowe dane";
    Szyfrowanie sz;
    Klucze k = sz.generujKlucze();
  QByteArray d = sz.szyfruj(k.publiczny,dane);
   QByteArray s = sz.deszyfruj(k.prywatny,d);
    QByteArray g = sz.podpisz(k.prywatny,dane.toLatin1());
    qDebug() << g;
    qDebug() << sz.sprawdzPodpis(k.publiczny,g,dane.toLatin1());*/

    login = ui->lineEdit->text();
    haslo = ui->lineEdit_2->text();
    serwer = ui->lineEdit_3->text();

    if(checkLoginAndPassword() == true)
    {
        std::cout << "good";

        this->close();
    }
    else
    {
//        QMessageBox msgBox;
//        msgBox.
//                msgBox.setText("Niepoprawne dane. Spróbuj ponownie.");
//        msgBox.exec();
        QMessageBox::critical(this,"Niepowodzenie","Niepoprawne dane. Spróbuj ponownie.");
    }
}

bool Start::checkLoginAndPassword()
{
    //tutaj komunikacja z serwerem w klasie Podprotokol1
    _sterownik.ustawDaneLogSer(login, haslo, serwer);
    if(login == "1")
    {
        emit uruchom(true);
    }
    else if (_sterownik.zaloguj())
    {
        poprawne_logowanie = true;
        return true;
    }
    else return false;
}
