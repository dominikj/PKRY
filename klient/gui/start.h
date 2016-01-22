#ifndef START_H
#define START_H

#include <QMainWindow>
#include <QString>
class Sterownik;
namespace Ui {
class Start;
}
/**
 * @brief okno powitalne logowania
 */
class Start : public QMainWindow
{
    Q_OBJECT

public:
    explicit Start(QWidget *parent, Sterownik& ster);
    ~Start();


private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

signals:
    void uruchom(bool t);

private:
    static bool poprawne_logowanie;
    Ui::Start *ui;
    QString serwer;
    QString login;
    QString haslo;
    Sterownik& _sterownik;
    bool checkLoginAndPassword();
};

#endif // START_H
