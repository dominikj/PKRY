#ifndef TCP_H
#define TCP_H
#include <QString>
#include <QtNetwork/QTcpSocket>
#include <QMainWindow>
#include <iostream>
class Tcp: public QObject
{
    Q_OBJECT
public:
    Tcp(int port, QString adres):_port(port), _adres(adres){
        _gniazdo = NULL;
    }
    bool polacz();
    void wyslij(QByteArray);
    QString odbierz();
    void zamknij();

protected:
    int _port;
    QString _adres;
    QTcpSocket * _gniazdo;
};

#endif // TCP_H
