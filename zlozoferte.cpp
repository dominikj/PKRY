#include "zlozoferte.h"
#include "ui_zlozoferte.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QCoreApplication>

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

void zlozOferte::wez_dane_aukcji(QString nazwa_aukcji, QDateTime data_zak, QList<QString> kryteria)
{
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
