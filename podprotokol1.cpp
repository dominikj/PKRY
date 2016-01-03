#include "podprotokol1.h"
#include <ctime>


Podprotokol1::Podprotokol1(Szyfrowanie& szyf, Tcp& tcp, Baza& baza) : Podprotokol(szyf, tcp, baza){}

void Podprotokol1::generacja_stempla_czasowego()
{
    T_nrc = static_cast<long int> (std::time(0));
}

bool Podprotokol1::wykonaj(){
    //to co ma wykonać podprot 1
    return true;
}
Podprotokol1::~Podprotokol1(){

}
