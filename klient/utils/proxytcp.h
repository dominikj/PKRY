#ifndef PROXYTCP_H
#define PROXYTCP_H
#include "tcp.h"
#include "szyfrowanie.h"

class ProxyTcp : public Tcp
{
public:
    ProxyTcp(int port, QString adres, Szyfrowanie& szyfr) :  Tcp(port,adres), _szyfr(szyfr){}
    void wyslijSzyfrowane(QString klucz, QByteArray dane);
    QString odbierzSzyfrowane(QString klucz);

private:
    Szyfrowanie& _szyfr;

};

#endif // PROXYTCP_H
