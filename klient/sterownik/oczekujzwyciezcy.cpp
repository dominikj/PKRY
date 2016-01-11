#include "oczekujzwyciezcy.h"

void OczekujZwyciezcy::czekajZwyciezcy(){
QString dane = _tcp->odbierz();
emit alertZwyciezca(dane);
}
