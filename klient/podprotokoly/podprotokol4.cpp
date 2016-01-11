#include "podprotokol4.h"

Podprotokol4::Podprotokol4(Szyfrowanie& szyf, Tcp& tcp, Baza& baza) : Podprotokol(szyf, tcp, baza)
{

}

bool Podprotokol4::wykonaj(){
    //to co ma wykonać podprot 4
    return true;
}
Podprotokol4::~Podprotokol4(){

}
