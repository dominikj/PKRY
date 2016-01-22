#ifndef TCP_H
#define TCP_H
#include <QByteArray>
#include <QtNetwork/QTcpSocket>
#include <QMainWindow>
#include <iostream>
#define TIMEOUT 200
/**
 * @brief Klasa połączenia tcp
 */
class Tcp: public QObject
{
    Q_OBJECT
public:
    Tcp(QTcpSocket* gniazdo): _gniazdo(gniazdo){
    }
 virtual  ~Tcp();
    void wyslij(QByteArray);
    QByteArray odbierz();
    void zamknij();
    QByteArray odbierzLinie();
    QTcpSocket* const gniazdo() const { return _gniazdo;}
protected:
    int _port;
    QString _adres;
    QTcpSocket * _gniazdo;
};

#endif // TCP_H
