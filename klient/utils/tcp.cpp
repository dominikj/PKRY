#include "tcp.h"

bool Tcp::polacz()
{
    if(_gniazdo == nullptr || !_gniazdo->isOpen()){
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
    return true;
}

void Tcp::wyslij(QByteArray dane){
_gniazdo->write(dane);
}

QByteArray Tcp::odbierz(){
    _gniazdo->waitForReadyRead(TIMEOUT);
    return _gniazdo->readAll();
}

void Tcp::zamknij(){
    _gniazdo->close();
}

QByteArray Tcp::odbierzLinie(){
    _gniazdo->waitForReadyRead(TIMEOUT);
    return _gniazdo->readLine();
}
