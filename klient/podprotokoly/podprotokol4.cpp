#include "podprotokol4.h"
#include <QMessageBox>
Podprotokol4::Podprotokol4(Szyfrowanie& szyf, Tcp& tcp, Baza& baza) : Podprotokol(szyf, tcp, baza){}
/**
 * @brief Wykonuje scenariusz podprotokołu 4 po stronie klienta, gdy ten jest uczestnikiem
 * @return sukces/porażka operacji
 */
bool Podprotokol4::wykonajUczestnik(){

    QByteArray podpis, klucz, dane;
       qDebug() << ( SZYFR_TCP->odbierzLinie());
       try{
        SZYFR_TCP->wyslijSzyfrowane(_baza.kluczGAP,"PODPROTOKOL40|");
       }
       catch(...){
           emit wyswietlKonsola(QString("Błąd transmisji"));
          return false;
       }
      try{
           dane = SZYFR_TCP->odbierzSzyfrowane(_baza.KluczPrywatny);
       }
       catch(...){
           emit wyswietlKonsola(QString("Błąd transmisji"));
          return false;
       }
    podziel(dane,klucz, podpis);
    if(_szyfrowanie.sprawdzPodpis(_baza.kluczGAP,podpis,klucz)){
       podpis = _szyfrowanie.podpisz(_baza.KluczPrywatny,klucz);
       dane = scal(klucz,podpis);
       try{
    SZYFR_TCP->wyslijSzyfrowane(_baza.kluczGAP,"PODPROTOKOL41|"+dane);
       }
       catch(...){
           emit wyswietlKonsola(QString("Błąd transmisji"));
          return false;
       }
    }
    else {
         emit wyswietlKonsola(QString("Błedny podpis"));
        return false;
    }
   emit wyswietlKonsola(QString("Odsyłam odebrany fragment klucza: ") + dane.mid(0,200));
}
/**
 * @brief Wykonuje scenariusz podprotokołu 4 po stronie klienta, gdy ten jest firmą
 * @return sukces/porażka operacji
 */
bool Podprotokol4::wykonajFirma(){
    qDebug() << "Odsyłam klucz firmy";
       qDebug() << ( SZYFR_TCP->odbierzLinie());
       QByteArray podpis = _szyfrowanie.podpisz(_baza.KluczPrywatny,_baza.czescKluczaPrzetargu);
       QByteArray dane = scal(_baza.czescKluczaPrzetargu,podpis);
       try{
    SZYFR_TCP->wyslijSzyfrowane(_baza.kluczGAP,"PODPROTOKOL41|"+dane);
       }
       catch(...){
           emit wyswietlKonsola(QString("Błąd transmisji"));
          return false;
       }
       emit wyswietlKonsola(QString("Odsyłam odebrany fragment klucza dla firmy: ") + dane.mid(0,200));
    return czekajNaOferty();
}
/**
 * @brief pobiera  z gap oferty
 * @return
 */
bool Podprotokol4::czekajNaOferty(){
        if(SZYFR_TCP->odbierzLinie() == "WAZNY\n"){
       QByteArray podpis, ofertyZpodpisami, dane = SZYFR_TCP->odbierzSzyfrowane(_baza.KluczPrywatny);
       podziel(dane,ofertyZpodpisami, podpis);
       if(_szyfrowanie.sprawdzPodpis(_baza.kluczGAP,podpis,ofertyZpodpisami)){
            _baza.ofertyDoRozpatrzenia = ofertyZpodpisami;
               emit wyswietlKonsola(QString("Otrzymano oferty: ") + ofertyZpodpisami);
            return true;
       }
       else {
            emit wyswietlKonsola(QString("Błędny podpis"));
           return false;
       }
        }
        else{
            QMessageBox::information(0,"Rozstrzygnięcie aukcji", "Przetarg unieważniony" );
            return false;
        }
        return true;

}
/**
 * @brief Przesyła dane o zwycięzcy do GAP
 * @param dane zwycięzcy
 * @return
 */
bool Podprotokol4::odeslijZwyciezce(QString dane){
    QString odpowiedz =  dane + SEPARATOR1 + _baza.numerRejestracyjny + SEPARATOR1 + _baza.numerFirmy;
     QByteArray podpis = _szyfrowanie.podpisz(_baza.KluczPrywatny,odpowiedz.toLatin1());
     QByteArray tmp = scal(odpowiedz.toLatin1(),podpis);
     try{
     SZYFR_TCP->wyslijSzyfrowane(_baza.kluczGAP,"PODPROTOKOL42|"+tmp);
     }
     catch(...){
         emit wyswietlKonsola(QString("Błąd transmisji"));
        return false;
     }
      emit wyswietlKonsola(QString("Odesłałem zwycięzcę: ") + odpowiedz);
     return true;
}
/**
 * @brief Odbiera wynik aukcji z GAP
 * @return
 */
bool Podprotokol4::odbierzWynik(){
     QByteArray dane = ( SZYFR_TCP->odbierzLinie());
     qDebug() << "KONIEC";
     QMessageBox::information(0,"Rozstrzygnięcie aukcji", "Zwycięzcą aukcji został: " + dane );
     return true;
}

Podprotokol4::~Podprotokol4(){

}
