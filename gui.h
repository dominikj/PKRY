#ifndef GUI_H
#define GUI_H
#include "start.h"
class Sterownik;
class GUI
{
public:
    GUI(Sterownik& ster) : _sterownik(ster), _logowanie(0,ster){}
    void uruchom(){ _logowanie.show();}
private:
    Start _logowanie;
    Sterownik& _sterownik;
};

#endif // GUI_H
