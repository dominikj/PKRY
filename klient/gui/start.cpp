#include "start.h"
#include "ui_start.h"
#include <QMessageBox>
#include <iostream>
#include "utils/tcp.h"
#include "utils/szyfrowanie.h"
#include "sterownik/sterownik.h"

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
