#ifndef AUKCJA_H
#define AUKCJA_H
#include <QString>
/**
 * @brief Klasa modelująca pojedynczą aukcję
 */
class Aukcja
{
public:
    Aukcja();
    /**
     * @brief numer aukcji
     */
    QByteArray numer;
    /**
     * @brief data i czas zakończenia aukcji
     */
    QByteArray dataZakonczenia;
    /**
     * @brief parametry aukcji
     */
    QByteArray parametry;
    /**
     * @brief klucz publiczny aukcji
     */
    QByteArray kluczPublicznyAucji;

};

#endif // AUKCJA_H
