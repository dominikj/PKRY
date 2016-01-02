#ifndef PODPROTOKOL1_H
#define PODPROTOKOL1_H
#include <stdio.h>
#include <iostream>
#include <string>

class Podprotokol1
{
public:
    Podprotokol1();
    void podpisywanie_dokumentu();
    void kodowanie_asymetryczne();
    void odkodowanie_asymetryczne();
    void weryfikacja_podpisu();
    void generacja_PKG();
    void generacja_stempla_czasowego();
    ~Podprotokol1();

private:
    std::string Dc; //dokument Dc
    int SK_cca; //prywatny klucz do podpisania
    int PK_gap; //publiczny klucz GAPa
    int SK_gap; //prywatny klucz GAPa
    int UNG; //unikalny numer uzytkownika od GAPa
    int SK_c; //klucz prywatny uzytkownika
    int PK_c; //klucz publiczny uzytkownika
    long int T_nrc; //stempel czasowy

};

#endif // PODPROTOKOL1_H
