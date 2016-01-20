#include "podprotokol4.h"
#include <QMessageBox>
Podprotokol4::Podprotokol4(Szyfrowanie& szyf, Tcp& tcp, Baza& baza) : Podprotokol(szyf, tcp, baza)
{

}

bool Podprotokol4::wykonaj(){
    //to co ma wykonać podprot 4
    return true;
}
bool Podprotokol4::wykonajUczestnik(){
    qDebug() << "Odsyłam klucz";
       qDebug() << ( SZYFR_TCP->odbierzLinie());
        SZYFR_TCP->wyslijSzyfrowane(_baza.kluczGAP,"PODPROTOKOL40|");
    QByteArray podpis, klucz, dane = SZYFR_TCP->odbierzSzyfrowane(_baza.KluczPrywatny);
    podziel(dane,klucz, podpis);
    if(_szyfrowanie.sprawdzPodpis(_baza.kluczGAP,podpis,klucz)){
       podpis = _szyfrowanie.podpisz(_baza.KluczPrywatny,klucz);
       dane = scal(klucz,podpis);
    SZYFR_TCP->wyslijSzyfrowane(_baza.kluczGAP,"PODPROTOKOL41|"+dane);
    }
}
bool Podprotokol4::wykonajFirma(){
    qDebug() << "Odsyłam klucz firmy";
       qDebug() << ( SZYFR_TCP->odbierzLinie());
       QByteArray podpis = _szyfrowanie.podpisz(_baza.KluczPrywatny,_baza.czescKluczaPrzetargu);
       QByteArray dane = scal(_baza.czescKluczaPrzetargu,podpis);
    SZYFR_TCP->wyslijSzyfrowane(_baza.kluczGAP,"PODPROTOKOL41|"+dane);

    return czekajNaOferty();
}
bool Podprotokol4::czekajNaOferty(){
    qDebug() << "Czekam na oferty";
       qDebug() << ( SZYFR_TCP->odbierzLinie());
       QByteArray podpis, ofertyZpodpisami, oferty, dane = SZYFR_TCP->odbierzSzyfrowane(_baza.KluczPrywatny);
       podziel(dane,ofertyZpodpisami, podpis);
       if(_szyfrowanie.sprawdzPodpis(_baza.kluczGAP,podpis,ofertyZpodpisami)){
            _baza.ofertyDoRozpatrzenia = ofertyZpodpisami;
            qDebug() << ofertyZpodpisami;
            return true;
       }
       else return false;
}

bool Podprotokol4::odeslijZwyciezce(QString dane){
    qDebug() << "Odsyłam zwyciezce";
    QString odpowiedz =  dane + SEPARATOR1 + _baza.numerRejestracyjny + SEPARATOR1 + _baza.numerFirmy;
     QByteArray podpis = _szyfrowanie.podpisz(_baza.KluczPrywatny,odpowiedz.toLatin1());
     QByteArray tmp = scal(odpowiedz.toLatin1(),podpis);
     SZYFR_TCP->wyslijSzyfrowane(_baza.kluczGAP,"PODPROTOKOL42|"+tmp);
}
bool Podprotokol4::odbierzWynik(){
    //while ( SZYFR_TCP->odbierzLinie() != "ZWYCIEZCA\n");
     QByteArray dane = ( SZYFR_TCP->odbierzLinie());
     qDebug() << "KONIEC";
     QMessageBox::information(0,"Rozstrzygnięcie aukcji", "Zwycięzcą aukcji został: " + dane );
}

Podprotokol4::~Podprotokol4(){

}
