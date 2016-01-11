#ifndef WYBIERZZWYCIEZCE_H
#define WYBIERZZWYCIEZCE_H

#include <QDialog>
#include <QString>

namespace Ui {
class WybierzZwyciezce;
}

class WybierzZwyciezce : public QDialog
{
    Q_OBJECT

public:
    explicit WybierzZwyciezce(QWidget *parent = 0);
    void przekaz_liste_ofert(QString string_lista_ofert);
    ~WybierzZwyciezce();

private slots:
    void on_pushButton_clicked();

private:
    QString numer_aukcji;
    QList<QString> lista_ofert;
    QList<QString> lista_numerow_oferentow;
    void wyswietl_oferty();
    Ui::WybierzZwyciezce *ui;
};

#endif // WYBIERZZWYCIEZCE_H
