#include "start.h"
#include "ui_start.h"
#include <QMessageBox>
#include <iostream>

Start::Start(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Start)
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
    if(checkLoginAndPassword() == true)
        std::cout << "good";
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
    return false;
}
