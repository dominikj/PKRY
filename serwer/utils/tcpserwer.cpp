#include "tcpserwer.h"
#include "sterownik/sterownik.h"
void TcpSerwer::nowePoloczenie() {
    QTcpSocket *gniazdo = _serw->nextPendingConnection();
    Uzytkownik* tmp = new Uzytkownik(0,(new ProxyTcp(gniazdo,_szyfr)));
    tmp->numerWew = std::rand();
    QObject::connect(tmp, SIGNAL(poloczenieZamkniete(Uzytkownik*)),_ster,SLOT(koniecPoloczenia(Uzytkownik*)));
    QObject::connect(tmp, SIGNAL(przyszyDane(Uzytkownik*)),_ster,SLOT(przyszlyDane(Uzytkownik*)));
    qDebug() << "Użytkownik: "<< tmp->numerWew<<" nawiązał połączenie";
    _uzytkLista.push_back(tmp);
}
TcpSerwer::~TcpSerwer() {
    _serw->close();
}
