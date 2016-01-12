#ifndef TCP_H
#define TCP_H
#include <QByteArray>
#include <QtNetwork/QTcpSocket>
#include <QMainWindow>
#include <iostream>
class Tcp: public QObject
{
    Q_OBJECT
public:
    Tcp(QTcpSocket* gniazdo): _gniazdo(gniazdo){
    }
    void wyslij(QByteArray);
    QByteArray odbierz();
    void zamknij();
    QTcpSocket* const gniazdo() const { return _gniazdo;}
protected:
    int _port;
    QString _adres;
    QTcpSocket * _gniazdo;
};

#endif // TCP_H
