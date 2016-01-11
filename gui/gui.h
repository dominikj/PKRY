#ifndef GUI_H
#define GUI_H
#include "start.h"
#include "oknoglowne.h"
#include "wybierzzwyciezce.h"
class Sterownik;
class GUI
{

public:
    GUI(Sterownik& ster) : _sterownik(ster), _logowanie(0,ster), _oknoglowne(0,ster,_logowanie){}
    void uruchom();
private:
    Start _logowanie;
    OknoGlowne _oknoglowne;
    WybierzZwyciezce *_wyborzwyciezcy;
    Sterownik& _sterownik;
};

#endif // GUI_H