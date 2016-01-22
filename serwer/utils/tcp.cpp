#include "tcp.h"
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
Tcp::~Tcp() {
    _gniazdo->close();
}
