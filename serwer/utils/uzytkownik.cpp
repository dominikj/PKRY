#include "uzytkownik.h"

void Uzytkownik::koniecPoloczenia(){
    emit poloczenieZamkniete(this);
}

void Uzytkownik::daneWBuforze(){
    emit przyszyDane(this);
}
