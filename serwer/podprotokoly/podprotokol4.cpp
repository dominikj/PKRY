#include "podprotokol4.h"
#include "utils/uzytkownik.h"
#include "utils/proxytcp.h"
#include <unistd.h>
Podprotokol4::Podprotokol4(Szyfrowanie& szyf,Baza& baza) : Podprotokol(szyf, baza)
{

}
bool Podprotokol4::wykonaj(Uzytkownik* uz,QByteArray dane){ }
bool Podprotokol4::wykonaj(){

    for(int i = 0; i < aukcja->oferty.size(); ++i){
        if(aukcja->oferty[i].uzyte == false){
       aukcja->oferty[i].uzyte = true;
        for(Uzytkownik* uz : *uzytkownicy){ //TODO: zrobić wysyłanie tylko do użytkowników związanych z daną aukcją, nie do wszystkich
                if(uz->nazwa == aukcja->oferty[i].nazwaUczestnika){
                SZYFR_TCP(uz)->wyslij("test\n");
                qDebug() << "Proszę o klucz:" << uz->nazwa;
                return true;
                }
        }
        }
    }
    if (!aukcja->czyFirmaOdpytana){
        for(Uzytkownik* uz : *uzytkownicy){
            if(aukcja->firmaNazwa == uz->nazwa){
    SZYFR_TCP(uz)->wyslij("test\n");
    qDebug() << "Proszę o klucz:" << uz->nazwa;
    aukcja->czyFirmaOdpytana = true;
    firma = uz;
    return true;
            }
        }
    }

    wykonaj4();
    koniec:
    return true;
}

bool Podprotokol4::wykonaj2(Uzytkownik* uz){
       qDebug() << "Wysłano fragment klucza do: " << uz->nazwa;
       QByteArray Dc = fragmentyKlucza[fragmentyKlucza.size()-1];
       fragmentyKlucza.pop_back();
       QByteArray podpis = _szyfrowanie.podpisz(_baza.kluczGAPPrywatny,Dc);
       Dc = scal(Dc,podpis);
       SZYFR_TCP(uz)->wyslijSzyfrowane(uz->kluczPubliczny,Dc);
       return true;
}

bool Podprotokol4::wykonaj3(Uzytkownik* uz,QByteArray dane){
    qDebug() << "Odebrano fragment klucza";
 QByteArray odp, podpis;
        podziel(dane,odp,podpis);
         if(_szyfrowanie.sprawdzPodpis(uz->kluczPubliczny,podpis,odp)){
               if(aukcja->firmaNazwa != uz->nazwa)
             fragmentyKluczaOdebrane.push_back(odp);
               else
                   aukcja->kluczPrywatnyAukcjiCzescFirma = odp;
         }
         wykonaj();
         return true;
}
bool Podprotokol4::wykonaj4(){
      qDebug() << "Wykonuje czwarty";
    QByteArray oferty;
    QByteArray kompletnyKluczUczestnicy, kompletnyKlucz;
    std::vector<QByteArray> fragmenty;
    fragmenty.push_back(aukcja->kluczPrywatnyAukcjiCzescFirma);
    fragmenty.push_back(aukcja->kluczPrywatnyAukcjiCzescGAP);
    fragmenty.push_back(aukcja->kluczPrywatnyAukcjiCzescUczestnicy); // dla debugu
    if(fragmentyKluczaOdebrane.size() >= 2){
    kompletnyKluczUczestnicy = _szyfrowanie.przywrocSekret(2,fragmentyKluczaOdebrane);
    fragmenty.push_back(kompletnyKluczUczestnicy);
    }
    else{
        qDebug() << "Przetarg nieważny. Mniej niż 2 uczestników";
    }
    kompletnyKlucz = _szyfrowanie.przywrocSekret(3,fragmenty);
    qDebug() << "Wykonałem czwarty: " << kompletnyKlucz;
    QString tmp, tmp1;
    QByteArray Dc;
    tmp1 = "nr_aukc="+QByteArray::number(aukcja->numerAukcji);
    for(Oferta of : aukcja->oferty){
        int i = 0;
        for(; i < uzytkownicy->size(); ++i)
            if((*uzytkownicy)[i]->nazwa == of.nazwaUczestnika)
                break;

        tmp = "nr_uczes=" +of.numerUczestnika + ";nrc="+ (*uzytkownicy)[i]->numerRejestracyjny;
       (tmp  +=";"+ _szyfrowanie.deszyfruj(kompletnyKlucz,of.oferta));
         qDebug() << "Odszyfrowuję ofertę: " << tmp;
        tmp1 += "::" + tmp;
    }
    Dc = tmp1.toLatin1();
    SZYFR_TCP(firma)->wyslij("WAZNY\n");
    QByteArray podpis = _szyfrowanie.podpisz(_baza.kluczGAPPrywatny, Dc);
    Dc = scal(Dc,podpis);
    qDebug() << Dc;
    SZYFR_TCP(firma)->wyslijSzyfrowane(firma->kluczPubliczny,Dc);
    qDebug() << "Oferty przesłano";
    return true;
}
bool Podprotokol4::wykonaj5(Uzytkownik* uz, QByteArray dane){
    QByteArray daneBezpodpisu, podpis, ogloszenie;
    podziel(dane,daneBezpodpisu,podpis);
    if(_szyfrowanie.sprawdzPodpis(uz->kluczPubliczny,podpis,daneBezpodpisu)){
    qDebug() << "Odebrano zwyciezcę";
    QByteArrayList tmp = daneBezpodpisu.split(';');
       qDebug() << tmp;
    QByteArrayList tmp1 = tmp.at(1).split(SEPARATOR1);
    QString zwyciezcaImie, zwyciezcaNumer;
    for(Uzytkownik* u : *uzytkownicy){
        if(u->numerRejestracyjny.toLatin1() == tmp1.at(0)){
            zwyciezcaImie = u->nazwa;
         break;
        }
    }
    for(Oferta of : aukcja->oferty){
        if(of.nazwaUczestnika == zwyciezcaImie){
            zwyciezcaNumer = of.numerUczestnika;
            break;
        }
    }
    QByteArray tmp2 =tmp.at(0);
            tmp2 = tmp2.replace('\t', ' ');
   for(Uzytkownik* u : *uzytkownicy){
       for(Oferta of : aukcja->oferty){
           if(u->nazwa == of.nazwaUczestnika){
               qDebug() << "WYsyłam ogłoszenie do:" << u->nazwa;
   ogloszenie = zwyciezcaImie.toLatin1() + " numer: " + zwyciezcaNumer.toLatin1() + " numery pozostałych uczestników: " + tmp2 +"\n";
    //SZYFR_TCP(uz)->wyslij("ZWYCIEZCA\n");
    SZYFR_TCP(u)->wyslij(ogloszenie);
    sleep(2);
           }
   }
   }
    qDebug() << "KONIEC";
   }
}

Podprotokol4::~Podprotokol4(){

}
