#ifndef TCPSERWER_H
#define TCPSERWER_H

#include <QObject>
#include <QTcpServer>
#include "tcp.h"
#include <deque>
#include <QDebug>
#include "utils/uzytkownik.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "utils/szyfrowanie.h"

class Sterownik;
typedef std::deque<Uzytkownik*>::iterator UzytkIt;
typedef std::deque<Uzytkownik*> UzytkLista;
class TcpSerwer : public QObject
{
    Q_OBJECT
public:
    explicit TcpSerwer(UzytkLista& uzytkLista, int port, Sterownik* ster, Szyfrowanie& szyfr, QObject *parent = 0): _uzytkLista(uzytkLista), _port(port), _ster(ster), _szyfr(szyfr){
        _serw = new QTcpServer(this);
        std::srand(std::time(NULL));
        connect(_serw, SIGNAL(newConnection()), this, SLOT(nowePoloczenie()));
        _serw->listen(QHostAddress::Any, 10099);
        qDebug() << "Nasłuchuje";
    }
~TcpSerwer();
signals:

public slots:
      void nowePoloczenie();
private:
      Sterownik* _ster;
    QTcpServer* _serw;
 //   UzytkIt _uzytkIt;
    UzytkLista& _uzytkLista;
    int _port;
    Szyfrowanie& _szyfr;

};

#endif // TCPSERWER_H
