#include "tcp.h"

void Tcp::wyslij(QByteArray dane){
_gniazdo->write(dane);
}

QByteArray Tcp::odbierz(){
  //FIXME: Nie można wysłać symbolu końca danych, więc skróciłem timeout :/ :/
    _gniazdo->waitForReadyRead(200);
    return _gniazdo->readAll();
}

void Tcp::zamknij(){
    _gniazdo->close();
}
