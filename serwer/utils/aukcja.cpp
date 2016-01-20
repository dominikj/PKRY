#include "aukcja.h"

Aukcja::Aukcja()
{
connect(&timer,SIGNAL(timeout()),this,SLOT(czasSieSkonczyl()));
}

 void Aukcja::czasSieSkonczyl(){
     emit zakonczonaAukcja(this);
 }
