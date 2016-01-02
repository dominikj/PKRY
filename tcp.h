#ifndef TCP_H
#define TCP_H
#include <QString>
#include <QtNetwork/QTcpSocket>
#include <QMainWindow>
#include <iostream>
class tcp: public QObject
{
    Q_OBJECT
public:
    tcp(int port, QString adres):_port(port), _adres(adres){
        _gniazdo = NULL;
    }
    bool polacz();
    void wyslij(QByteArray);
    QString odbierz();
    void zamknij();

private:
    int _port;
    QString _adres;
    QTcpSocket * _gniazdo;
};

#endif // TCP_H
