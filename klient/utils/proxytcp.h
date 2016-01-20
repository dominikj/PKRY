#ifndef PROXYTCP_H
#define PROXYTCP_H
#include "tcp.h"
#include "szyfrowanie.h"

class ProxyTcp : public Tcp
{
public:
    bool debug = false;
    ProxyTcp(int port, QString adres, Szyfrowanie& szyfr) :  Tcp(port,adres), _szyfr(szyfr){}
    void wyslijSzyfrowane(QString klucz, QByteArray dane);
    QByteArray odbierzSzyfrowane(QString klucz);

private:
    Szyfrowanie& _szyfr;

};

#endif // PROXYTCP_H
