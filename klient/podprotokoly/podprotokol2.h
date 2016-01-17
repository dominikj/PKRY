#ifndef PODPROTOKOL2_H
#define PODPROTOKOL2_H
#include "podprotokol.h"
#include <QString>

/*!
 * Klasa odpowiedzialna za realizację podprotokołu nr 2 - stworzenia nowej aukcji.
 */
class Podprotokol2 : public Podprotokol
{
public:
    /*!
     * Konstruktor klasy Podprotokol2.
     */
    Podprotokol2(Szyfrowanie& szyf, Tcp& tcp, Baza& baza);
    /*!
     * Implementacja funkcji odpowiedzialnej za wykonanie podprotokołu.
     * \return - zwraca true w przypadku pomyślnego wykonania podprotokołu. W przeciwnym wypadku false.
     */
    virtual bool wykonaj();
    ~Podprotokol2();

private:
    /*!
     * Funkcja podpisujące dokument.
     */
    void podpisywanie_dokumentu();
    /*!
     * Funkcja zapewniająca kodowanie asymetryczne.
     */
    void kodowanie_asymetryczne();
    /*!
     * Funkcja zapewniająca odkodowanie asymetryczne.
     */
    void odkodowanie_asymetryczne();
    /*!
     * Funkcja służąca weryfikacji podpisu.
     */
    void weryfikacja_podpisu();
    /*!
     * Funkcja generująca liczbę pseudolosową.
     */
    void generacja_PKG();
    /*!
     * Funkcja generująca stempel czasowy.
     */
    void generacja_stempla_czasowego();

    /*!
     * Pole tekstowe przechowujące numer "zezwolenia" na utworzenie aukcji
     */
    QString N_f;
    /*!
     * Pole tekstowe przechowujące warunki przetargu
     */
    QString WP_f; //
    /*!
     * Pole tekstowe przechowujące klucz prywatny firmy
     */
    QString SK_f; // !!!CZY TO NIE JEST TO SAMO CO SK_c w podprotokol1???
    /*!
     * Pole tekstowe przechowujące numer rejestracyjny uzytkownika
     */
    QString NR_f; // (znowu dubel z podprot1)
    /*!
     * Pole tekstowe przechowujące stempel czasowy numeru rejestracyjnego
     */
    QString T_nrf; // (znowu dubel z podprot1)
    /*!
     * Pole tekstowe przechowujące część klucza dla firmy
     */
    QString klucz_publiczny_przetargu_F; //

};

#endif // PODPROTOKOL2_H
