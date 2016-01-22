#ifndef PROXYTCP_H
#define PROXYTCP_H
#include "tcp.h"
#include "szyfrowanie.h"
/**
 * @brief Klasa rozszerzająca funkcjonalność klasy połączenia Tcp o transmisję szyfrowaną
 */
class ProxyTcp : public Tcp
{
public:
    ProxyTcp(int port, QString adres, Szyfrowanie& szyfr) :  Tcp(port,adres), _szyfr(szyfr){}

    void wyslijSzyfrowane(QString klucz, QByteArray dane);
    QByteArray odbierzSzyfrowane(QString klucz);


private:
    Szyfrowanie& _szyfr;

};

#endif // PROXYTCP_H
