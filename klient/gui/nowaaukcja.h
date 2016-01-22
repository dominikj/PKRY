#ifndef NOWAAUKCJA_H
#define NOWAAUKCJA_H
#include <QDialog>
#include <QString>
#include <QDateTime>
#include <QList>
class Sterownik;
namespace Ui {
class NowaAukcja;
}
/**
 * @brief Klasa okna nowej aukcji
 */
class NowaAukcja : public QDialog
{
    Q_OBJECT

public:
    struct polaAukcji{
        QString nazwa_aukcji;
        QString opis_aukcji;
        QDateTime data_zakonczenia;
        QList<QString> lista_kryteriow;
    };

    explicit NowaAukcja( Sterownik& ster,QWidget *parent = 0);

    polaAukcji pola_aukcji;
    void zwrocPola(QString &test);
    QString przygotuj_dane_aukcji_do_wyslania(polaAukcji &pA);
    ~NowaAukcja();

signals:
   void nowa_aukcja(polaAukcji pA);


private slots:

    void on_pushButton_3_clicked();
    void on_pushButton_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::NowaAukcja *ui;
    Sterownik& _ster;
};

#endif // NOWAAUKCJA_H
