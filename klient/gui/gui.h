#ifndef GUI_H
#define GUI_H
#pragma once
#include "start.h"
#include "oknoglowne.h"
class Sterownik;
/**
 * @brief Klasa  GUI agregująca pozostałe komponenty GUI
 */
class GUI
{

public:
    GUI(Sterownik& ster) : _logowanie(0,ster), _oknoglowne(0,ster,_logowanie),  _sterownik(ster){
    }
    void uruchom();

private:
    Start _logowanie;
    OknoGlowne _oknoglowne;
    Sterownik& _sterownik;
};

#endif // GUI_H
