#include "sterownik.h"

/*Sterownik::~Sterownik(){
    if (_podprot1 != nullptr)
        delete _podprot1;
}
*/
void Sterownik::koniecPoloczenia(Uzytkownik* uz){
std::deque<Uzytkownik*>::iterator i = listaUzytkownikow.begin();

for(; i < listaUzytkownikow.end(); ++i){
if(**i == *uz)
listaUzytkownikow.erase(i);


}
qDebug() << "Użytkownik: " << uz->numerWew << " rozłączył się";
}

void Sterownik::przyszlyDane(Uzytkownik *uz){
    qDebug() << "Odebrano dane od użytkownika:" << uz->numerWew;
  //  qDebug() << uz->poloczenie()->odbierz();
     //   uz->poloczenie()->wyslij("OK");
    qDebug() << dynamic_cast<ProxyTcp*>(uz->poloczenie())->odbierzSzyfrowane(_baza.kluczGAPPrywatny);
}
