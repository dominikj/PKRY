#ifndef STEROWNIK_H
#define STEROWNIK_H
#include "podprotokoly/podprotokol1.h"
#include "podprotokoly/podprotokol2.h"
#include "podprotokoly/podprotokol3.h"
#include "podprotokoly/podprotokol4.h"
#include "utils/baza.h"
#include "utils/szyfrowanie.h"
#include "utils/proxytcp.h"
#include "utils/uzytkownik.h"
#include <deque>
#include "utils/tcpserwer.h"

typedef std::deque<Uzytkownik*>::iterator UzytkIt;
typedef std::deque<Uzytkownik*> UzytkLista;

class Sterownik : public QObject
{
    Q_OBJECT
public:
    explicit Sterownik(QObject *parent = 0){
       if (_baza.zaladujUzytkownikow("users.txt") == false)
           throw std::exception();
        _serw = new TcpSerwer (listaUzytkownikow, 10099,this, _szyfr,0);
        _podprot1 = new Podprotokol1(_szyfr,_baza);

    }

public slots:
void koniecPoloczenia(Uzytkownik*);
void przyszlyDane(Uzytkownik*);

private:
 Podprotokol1* _podprot1 =nullptr;
 Podprotokol2* _podprot2 =nullptr;
 Podprotokol3* _podprot3 =nullptr;
 Podprotokol4* _podprot4 =nullptr;
 Baza _baza;
 Szyfrowanie _szyfr;
TcpSerwer* _serw;
UzytkLista listaUzytkownikow;
};

#endif // STEROWNIK_H
