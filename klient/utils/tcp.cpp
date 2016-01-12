#include "tcp.h"

bool Tcp::polacz()
{
_gniazdo = new QTcpSocket(this);
_gniazdo->connectToHost(_adres, _port);
    if( _gniazdo->waitForConnected() ) {
        return true;
    }
    else
    {
        qDebug() << "Połączenie zakończono błędem";
        return false;

    }
}

void Tcp::wyslij(QByteArray dane){
_gniazdo->write(dane);
}

QByteArray Tcp::odbierz(){
    _gniazdo->waitForReadyRead(200);
    return _gniazdo->readAll();
}

void Tcp::zamknij(){
    _gniazdo->close();
}
