#include "tcp.h"

bool Tcp::polacz()
{
    if(_gniazdo == nullptr){
        _gniazdo = new QTcpSocket(this);
        qDebug() <<"nowe połączenie";
    }   if(!_gniazdo->isOpen()){
        _gniazdo->connectToHost(_adres, _port);
    }
        if( _gniazdo->waitForConnected(200) ) {
            return true;
        }
        else
        {
            qDebug() << "Połączenie zakończono błędem";
            return false;

        }
}
/**
 * @brief wyślij dane przez połączenie tcp
 * @param dane dane do wysłania
 */
void Tcp::wyslij(QByteArray dane) {
    _gniazdo->write(dane);
}
/**
 * @brief odbiera dane z połączenia tcp
 * @return dane odebrane
 */
QByteArray Tcp::odbierz() {
    _gniazdo->waitForReadyRead(TIMEOUT);
    return _gniazdo->readAll();
}
/**
 * @brief zamyka połączenie tcp
 */
void Tcp::zamknij() {
    _gniazdo->close();
}
/**
 * @brief Odczytuje jedną linię z bufora połączenia
 * @return dane odebrane
 */
QByteArray Tcp::odbierzLinie() {
    _gniazdo->waitForReadyRead(TIMEOUT);
    return _gniazdo->readLine();
}
Tcp::~Tcp(){
    _gniazdo->close();
}
