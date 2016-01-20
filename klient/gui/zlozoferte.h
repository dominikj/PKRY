#ifndef ZLOZOFERTE_H
#define ZLOZOFERTE_H

#include <QDialog>
#include <QString>
#include <QDateTime>
#include <QList>

namespace Ui {
class zlozOferte;
}

class zlozOferte : public QDialog
{
    Q_OBJECT

public:
    void wez_dane_aukcji(QString nr_aukcji, QString nazwa_aukcji, QString data_zak, QByteArrayList kryteria);
    explicit zlozOferte(QWidget *parent = 0);
    ~zlozOferte();

signals:
    void skladanie_oferty(QString of);

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void odpowiedz_od_serwera(QString odp, bool powodzenie);

private:
    Ui::zlozOferte *ui;
    QString numer_aukcji;
    void przygotuj();
};

#endif // ZLOZOFERTE_H
