#include "tcp.h"

bool tcp::polacz()
{
_gniazdo = new QTcpSocket(this);
_gniazdo->connectToHost(_adres, _port);
    if( _gniazdo->waitForConnected() ) {
        return true;
    }
    else
        return false;
}

void tcp::wyslij(QByteArray dane){
_gniazdo->write(dane);
}

QString tcp::odbierz(){
    _gniazdo->waitForReadyRead();
    return _gniazdo->readAll();
}

void tcp::zamknij(){
    _gniazdo->close();
}
