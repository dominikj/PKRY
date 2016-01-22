#ifndef WYBIERZZWYCIEZCE_H
#define WYBIERZZWYCIEZCE_H

#include <QDialog>
#include <QString>
#include "sterownik/oczekujzwyciezcy.h"
struct oferta {
    QString NRo;
    QString Non;
};

namespace Ui {
class WybierzZwyciezce;
}
/**
 * @brief Okno wyboru zwycięzcy
 */
class WybierzZwyciezce : public QDialog
{
    Q_OBJECT

public:
    explicit WybierzZwyciezce(QWidget *parent = 0);
    void przekaz_liste_ofert(QString string_lista_ofert);
    ~WybierzZwyciezce();

signals:
    void info_dla_sterownika(QString);

public slots:
    void wyswietl_okno(QString dane);


private slots:
    void on_pushButton_clicked();

private:
    QString numer_aukcji;
    QList<QString> lista_ofert;
    QList<QString> lista_numerow_oferentow;
    void wyswietl_oferty();
    Ui::WybierzZwyciezce *ui;
    std::vector<oferta> oferty;
};

#endif // WYBIERZZWYCIEZCE_H
