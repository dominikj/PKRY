#ifndef NOWAAUKCJA_H
#define NOWAAUKCJA_H

#include <QDialog>

namespace Ui {
class NowaAukcja;
}

class NowaAukcja : public QDialog
{
    Q_OBJECT

public:
    explicit NowaAukcja(QWidget *parent = 0);
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
