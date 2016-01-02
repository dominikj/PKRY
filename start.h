#ifndef START_H
#define START_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class Start;
}

class Start : public QMainWindow
{
    Q_OBJECT

public:
    explicit Start(QWidget *parent = 0);
    ~Start();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Start *ui;
    QString serwer;
    QString login;
    QString haslo;
    bool checkLoginAndPassword();
};

#endif // START_H
