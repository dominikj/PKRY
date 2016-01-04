#ifndef ZLOZOFERTE_H
#define ZLOZOFERTE_H

#include <QDialog>
#include <QString>
#include <QDateTime>
#include <QList>
#include "oknoglowne.h"
class OknoGlowne;

namespace Ui {
class zlozOferte;
}

class zlozOferte : public QDialog
{
    Q_OBJECT

public:
    void wez_dane_aukcji(QString nazwa_aukcji, QDateTime data_zak, QList<QString> kryteria);
    explicit zlozOferte(QWidget *parent = 0);
    ~zlozOferte();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::zlozOferte *ui;
    void przygotuj();
};

#endif // ZLOZOFERTE_H
