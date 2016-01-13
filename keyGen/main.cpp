#include <QTime>
#include<QDate>
#include "utils/szyfrowanie.h"
#include <QApplication>
#include <QMessageBox>
#include <QFile>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
      Szyfrowanie szyf;
      Klucze kl = szyf.generujKlucze();
     QString dataCzas = QDate::currentDate().toString() + QTime::currentTime().toString();
    QFile SK("Private_key " + dataCzas );
    QFile PK("Public_key " + dataCzas);
    if (PK.open(QIODevice::Append)) {
        QDataStream out(&PK);
        out << kl.publiczny.toUtf8().toBase64();
        PK.close();
    }
    else QCoreApplication::exit();

    if (SK.open(QIODevice::Append)) {
        QDataStream out(&SK);
        out << kl.prywatny.toUtf8().toBase64();
        SK.close();
    }
     else QCoreApplication::exit();

    QMessageBox msgBox;
    msgBox.setText("Wygenerowano pare kluczy RSA 2048bit: Private_key " + dataCzas + " i Public_key " + dataCzas);
    msgBox.setWindowTitle("KeyGen");
    msgBox.exec();

     QCoreApplication::exit();
}
