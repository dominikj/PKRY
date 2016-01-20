#ifndef START_H
#define START_H

#include <QMainWindow>
#include <QString>
class Sterownik;
class OknoGlowne;
namespace Ui {
class Start;
}

/*!
 * Klasa odpowiada za wyświetlanie okna startowego.
 */
class Start : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * Konstruktor klasy Start odpowiedzialnej za wyświetlanie okna startowego.
     * \param parent - rodzic okna startowego. Tutaj brak.
     * \param ster - referencja na obiekt klasy Sterownik, wymagany do prawidłowego przetwarzania wprowadzanych przez użytkownika danych.
     */
    explicit Start(QWidget *parent, Sterownik& ster);
    /*!
     * Destruktor klasy Start.
     */
    ~Start();
    /*!
     * Zmienna statyczna poprawne_logowanie przechowuje i udostępnia informację o poprawności przeprowadzonego logowania.
     */
    static bool poprawne_logowanie;

private slots:
    /*!
     * Przycisk czyszczący wszystkie pola (tj. powoduje, że zawartość wprowadzona w nich przez użytkownika znika).
     */
    void on_pushButton_2_clicked();
    /*!
     * Uruchamia procedurę sprawdzenia danych i podjęcia próby zalogowania się do systemu.
     */
    void on_pushButton_clicked();

signals:
    /*!
     * Sygnał emitowany dla uruchomienia okna głównego (w przypadku prawidłowego logowania).
     * \param t - zmienna typu bool, true wskazuje na poprawne logowanie i wymusza wyświetlenie okna głównego.
     */
    void uruchom(bool t);

private:
    /*!
     * Wskaźnik na user interface.
     */
    Ui::Start *ui;
    /*!
     * Pole tekstowe przechowujące informację o serwerze.
     */
    QString serwer;
    /*!
     * Pole tekstowe przechowujące informację o loginie.
     */
    QString login;
    /*!
     * Pole tekstowe przechowujące informację o haśle.
     */
    QString haslo;
    /*!
     * Referencja przechowująca obiekt klasy Sterownik.
     */
    Sterownik& _sterownik;
    /*!
     * Funkcja sprawdzająca poprawność wprowadzanych danych.
     * \return jeśli wprowadzone dane są poprawne, zwraca true. W przeciwnym razie false.
     */
    bool checkLoginAndPassword();
};

#endif // START_H
