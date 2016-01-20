#include "tcp.h"

bool Tcp::polacz()
{
    if(_gniazdo == nullptr){
        _gniazdo = new QTcpSocket(this);
        qDebug() <<"nowe połączenie";
    }
        _gniazdo->connectToHost(_adres, _port);
        if( _gniazdo->waitForConnected(200) ) {
            return true;
        }
        else
        {
            qDebug() << "Połączenie zakończono błędem";
            return false;

        }
}

void Tcp::wyslij(QByteArray dane) {
    _gniazdo->write(dane);
}

QByteArray Tcp::odbierz() {
    _gniazdo->waitForReadyRead(TIMEOUT);
    return _gniazdo->readAll();
}

void Tcp::zamknij() {
    _gniazdo->close();
}

QByteArray Tcp::odbierzLinie() {
    _gniazdo->waitForReadyRead(TIMEOUT);
    return _gniazdo->readLine();
}
Tcp::~Tcp(){
    _gniazdo->close();
}
