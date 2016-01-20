#ifndef PROXYTCP_H
#define PROXYTCP_H
#include "tcp.h"
#include "szyfrowanie.h"

class ProxyTcp : public Tcp
{
public:
    ProxyTcp(QTcpSocket* soc, Szyfrowanie& szyfr) :  Tcp(soc), _szyfr(szyfr){}
    void wyslijSzyfrowane(QString klucz, QByteArray dane);
    QByteArray odbierzSzyfrowane(QString klucz);

private:
    Szyfrowanie& _szyfr;

};

#endif // PROXYTCP_H
