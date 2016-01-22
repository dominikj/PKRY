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
/**
 * @brief funckja wykonywana po naciśnięciu przycisku wyczyść
 */
void Start::on_pushButton_2_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
}
/**
 * @brief Funkcja wykonywana po naciśnięciu przycisku zaloguj
 */
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

        QMessageBox::critical(this,"Niepowodzenie","Niepoprawne dane. Spróbuj ponownie.");
    }
}
/**
 * @brief Funkcja sprawdzająca poprawność danych logowania
 * @return sukces/porażka
 */
bool Start::checkLoginAndPassword()
{
    _sterownik.ustawDaneLogSer(login, haslo, serwer);
    if (_sterownik.zaloguj())
    {
        emit uruchom(true);
        poprawne_logowanie = true;
        return true;
    }
    else return false;
}
