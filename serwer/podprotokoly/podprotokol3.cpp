#include "podprotokol3.h"

Podprotokol3::Podprotokol3(Szyfrowanie& szyf, Tcp& tcp, Baza& baza) : Podprotokol(szyf, tcp, baza)
{

}

bool Podprotokol3::wykonaj(){
    //to co ma wykonać podprot 3
    return true;
}
Podprotokol3::~Podprotokol3(){

}
