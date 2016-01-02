#include "podprotokol1.h"
#include <ctime>


Podprotokol1::Podprotokol1()
{

}

void Podprotokol1::generacja_stempla_czasowego()
{
    T_nrc = static_cast<long int> (std::time(0));
}
