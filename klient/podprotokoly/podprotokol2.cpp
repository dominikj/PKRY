#include "podprotokol2.h"

Podprotokol2::Podprotokol2(Szyfrowanie& szyf, Tcp& tcp, Baza& baza) : Podprotokol(szyf, tcp, baza)
{

}

bool Podprotokol2::wykonaj(){
    //to co ma wykonać podprot 2
    return true;
}
Podprotokol2::~Podprotokol2(){

}
