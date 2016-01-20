#ifndef NOWAAUKCJA_H
#define NOWAAUKCJA_H

#include <QDialog>
#include <QString>
#include <QDateTime>
#include <QList>

namespace Ui {
class NowaAukcja;
}

/*!
 * Klasa NowaAukcja odpowiada za stworzenie i obsługę zdarzeń związanych z dodaniem nowego przetargu do systemu.
 */
class NowaAukcja : public QDialog
{
    Q_OBJECT

public:
    /*!
     * Struktura polaAukcji zapewnia podział logiczny niezbędnych składowych każdej aukcji. Jest to użyteczne i usprawnia pracę z obsługą tych danych (wyświetlanie, przetwarzanie na potrzeby interakcji z użytkownikiem). Ma jedynie związek na maszynie klienta/firmy, do GAPa przesyłane są te pola w postaci przetworzonej do QStringa.
     */
    struct polaAukcji{
        QString numer_aukcji;
        QString nazwa_aukcji;
        QString opis_aukcji;
        QDateTime data_rozpoczecia;
        QDateTime data_zakonczenia;
        QList<QString> lista_kryteriow;
    };
    /*!
     * Utworzenie zmiennej do obsługi pól nowotworzonej aukcji.
     */
    polaAukcji pola_aukcji;
    /*!
     * Konstruktor klasy NowaAukcja.
     */
    explicit NowaAukcja(QWidget *parent = 0);
    /*!
     * Brak opisu.
     * \param test
     */
    void zwrocPola(QString &test);
//     /*!
//      * Zamienia dane z postaci struktury do QStringa, który można przetworzyć przez pola szyfrujące.
//      */
//    QString przygotuj_dane_aukcji_do_wyslania(polaAukcji &pA);
    ~NowaAukcja();

signals:
    /*!
    * Sygnał o stworzeniu nowej aukcji przekazywany do Sterownika.
    * \param pA - parametr zawiera parametry nowotworzonego przetargu.
    */
   void nowa_aukcja(polaAukcji pA);


private slots:
    /*!
     * Po otwarciu okna dialogowego z dodaniem nowej aukcji, umożliwia powrót do menu głównego.
     */
    void on_pushButton_3_clicked();
    /*!
     * Wyświetla okno dialogowe z możliwością dodania nowego kryterium przetargu.
     */
    void on_pushButton_clicked();
    /*!
     * Usuwa wybrane kryterium z listy kryteriów przetargu.
     */
    void on_pushButton_4_clicked();
    /*!
     * Po kliknięciu następuje mała walidacja wpisanych pól, następnie dane są pobierane i wysyłane do GAPa.
     */
    void on_pushButton_2_clicked();

private:
    /*!
     * Wskaźnik na user interface.
     */
    Ui::NowaAukcja *ui;
};

#endif // NOWAAUKCJA_H
