#include "tcp.h"

void Tcp::wyslij(QByteArray dane){
_gniazdo->write(dane);
}

QByteArray Tcp::odbierz(){
  //FIXME: Nie można wysłać symbolu końca danych, więc skróciłem timeout :/ :/
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
Tcp::~Tcp(){
    _gniazdo->close();
}
