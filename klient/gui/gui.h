#ifndef GUI_H
#define GUI_H
#pragma once
#include "start.h"
#include "oknoglowne.h"
class Sterownik;
class GUI
{

public:
    GUI(Sterownik& ster) : _sterownik(ster), _logowanie(0,ster), _oknoglowne(0,ster,_logowanie){
        _wyborzwyciezcy = new WybierzZwyciezce(0);
    }
    void uruchom();
    WybierzZwyciezce *_wyborzwyciezcy;

private:
    Start _logowanie;
    OknoGlowne _oknoglowne;
    Sterownik& _sterownik;
};

#endif // GUI_H
