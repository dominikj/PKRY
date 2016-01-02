#ifndef NOWAAUKCJA_H
#define NOWAAUKCJA_H

#include <QDialog>
#include <QString>
#include <QDateTime>
#include <QList>

namespace Ui {
class NowaAukcja;
}

class NowaAukcja : public QDialog
{
    Q_OBJECT

public:
    struct polaAukcji{
        QString nazwa_aukcji;
        QString opis_aukcji;
        QDateTime data_rozpoczecia;
        QDateTime data_zakonczenia;
        QList<QString> lista_kryteriow;
    };
    polaAukcji pola_aukcji;
    explicit NowaAukcja(QWidget *parent = 0);
    void zwrocPola(QString &test);
    ~NowaAukcja();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::NowaAukcja *ui;
};

#endif // NOWAAUKCJA_H
