#ifndef TCP_H
#define TCP_H
#include <QString>
#include <QtNetwork/QTcpSocket>
#include <QMainWindow>
#include <iostream>
#define TIMEOUT 200
class Tcp: public QObject
{
    Q_OBJECT
public:
    Tcp(int port, QString adres):_port(port), _adres(adres){
        _gniazdo = NULL;
    }
    bool polacz();
    void wyslij(QByteArray);
    QByteArray odbierz();
    void zamknij();
    QByteArray odbierzLinie();
    QTcpSocket* const gniazdo() const { return _gniazdo;}
    ~Tcp();
protected:
    int _port;
    QString _adres;
    QTcpSocket * _gniazdo = nullptr;
};

#endif // TCP_H
