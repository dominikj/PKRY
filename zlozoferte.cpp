#include "zlozoferte.h"
#include "ui_zlozoferte.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QCoreApplication>
#include <QMessageBox>

zlozOferte::zlozOferte(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::zlozOferte)
{
    ui->setupUi(this);
    przygotuj();
}

void zlozOferte::przygotuj()
{
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);
    ui->tableWidget->setColumnCount(2);
}

void zlozOferte::wez_dane_aukcji(QString nr_aukcji, QString nazwa_aukcji, QDateTime data_zak, QList<QString> kryteria)
{
    numer_aukcji = nr_aukcji;
    ui->label_2->setText(nazwa_aukcji);
    ui->label_4->setText(data_zak.toString(QString("dd:MM:yyyy hh:mm:ss")));
    ui->tableWidget->setRowCount(kryteria.count());
    for(int i = 0; i < kryteria.count(); i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setFlags(Qt::ItemIsSelectable);
        item->setText(kryteria[i]);
        ui->tableWidget->setItem(i,0,item);
    }
}

zlozOferte::~zlozOferte()
{
    delete ui;
}

void zlozOferte::on_pushButton_2_clicked()
{
    this->close();
}

void zlozOferte::on_pushButton_clicked()
{
    bool czy_wszystko_wpisane = true;
    QString oferta;
    int liczba_wierszy = ui->tableWidget->rowCount();
    for(int i = 0; i < liczba_wierszy; i++)
    {
        QTableWidgetItem *item = ui->tableWidget->item(i,1);
        if(item == 0)
        {
            QString alert = "Nie wpisano wartości dla kryterium nr " + QString::number(i+1);
            QMessageBox::critical(this,"Oj",alert);
            czy_wszystko_wpisane = false;
            break;
        }
    }
    if(czy_wszystko_wpisane == true)
    {
        oferta = "nr_aukcji=" + numer_aukcji + "::";
        for(int i = 0; i < liczba_wierszy; i++){
            if(i == liczba_wierszy-1)
            {
                oferta = oferta + ui->tableWidget->item(i,0)->text() + "=" + ui->tableWidget->item(i,1)->text();
            }
            else
                oferta = oferta + ui->tableWidget->item(i,0)->text() + "=" + ui->tableWidget->item(i,1)->text() + "::";
        }
        /*
         * W TYM MIEJSCU TRZEBA PRZEKAZAĆ DANE DO SERWERA I POCZEKAC, CZY NASZA OFERTA ZOSTAŁA PRZYJĘTA
         * oferta - OFo podprotokol nr 3
         */
        QMessageBox::critical(this,"Oj",oferta);
        this->close();
    }
}
