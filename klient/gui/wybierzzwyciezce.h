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

signals:
    void info_dla_sterownika(QString zwyciezca, QString wzieci_pod_uwage);

public slots:
    void wyswietl_okno(QString dane);
    void odpowiedz_serwera(QString odpowiedz);

private slots:
    void on_pushButton_clicked();

private:
  //  Sterownik& _ster;
    QString numer_aukcji;
    QList<QString> lista_ofert;
    QList<QString> lista_numerow_oferentow;
    void wyswietl_oferty();
    Ui::WybierzZwyciezce *ui;
};

#endif // WYBIERZZWYCIEZCE_H
