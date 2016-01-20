#ifndef OKNOGLOWNE_H
#define OKNOGLOWNE_H

#include <QMainWindow>
#include <QList>
#include <QHash>
#include <QString>
#include <QListWidgetItem>
#include "nowaaukcja.h"
#include "zlozoferte.h"
#include "wybierzzwyciezce.h"
#include "start.h"
class Sterownik;
class zlozOferte;
namespace Ui {
class OknoGlowne;
}

/*!
 * Klasa OknoGlowne jest odpowiedzialna za obsługę i wyświetlania głównego okna programu. Jest to okno, które wyświetla się użytkownikowi po jego poprawnym zalogowaniu. Znajdują się tutaj także metody do zażądania komunikacji z serwerem (poprzez Sterownik), w tej także klasie dokonuje się większość operacji na danych tekstowych (formatowanie tekstu, jego separacja na komponenty itp.)
 */
class OknoGlowne : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * Struktura polaAukcji zapewnia podział logiczny niezbędnych składowych każdej aukcji. Jest to użyteczne i usprawnia pracę z obsługą tych danych (wyświetlanie, przetwarzanie na potrzeby interakcji z użytkownikiem). Ma jedynie związek na maszynie klienta/firmy, do GAPa przesyłane są te pola w postaci przetworzonej do QStringa
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
     * Konstruktor klasy OknoGlowne.
     * \param parent - rodzic w strukturze Qt. Tutaj pusty.
     * \param ster - przyjmuje referencję na sterownik, niezbędna do obsługi działań "na zewnątrz".
     * \param st -  przyjmuje referencję na okno startowe. Jest to potrzebne, by okno startowe mogło zawiadomić okno główne o poprawnie przeprowadzonym procesie logowania do GAPa i wymusić jego wyświetlenie.
     */
    explicit OknoGlowne(QWidget *parent, Sterownik& ster, Start& st);
    /*!
     * Wskaźnik na okno z możliwością tworzenia nowego przetargu.
     */
    NowaAukcja *nowa;
    /*!
     * Wskaźnik na okno z możliwością wzięcia udziału w przetargu.
     */
    zlozOferte *oknooferty;
    /*!
     * Wskaźnik na okno z możliwością wyboru najlepszej oferty.
     */
    WybierzZwyciezce *wyborzwyciezcy;
    /*!
     * Pod tą zmieną kryje się słowo (lub kilka słów) które będą się wyświetlać jako pierwszy element na liście aukcji. Jego kliknięcie spowoduje uaktualnienie posiadanej listy aukcji - wymuszone zostanie pobranie aktualnego stanu z GAPa.
     */
    static QString ZMIENNA_ODSWIEZ;  //można ustawić coś innego jako nazwę pola na liście, na którym dwuklik skutkuje odświeżeniem listy
    /*!
     * Przechowuje numer aukcji, na którą ostatni raz kliknięto - pomocne przy obsłudze żądań użytkownika.
     */
    static QString nr_aktywnej_aukcji; //ostatni dwuklik na danej aukcji
    /*!
     * Funkcja pobiera listę aukcji z GAPa i zapełnia nimi okno przeznaczone do wyświetlenia listy aukcji.
     */
    void zapelnij_liste_aukcji(QString );   //tutaj dostanie listę aukcji z GAPa
    /*!
     * Wymusza operacje niezbędne do wyświetlenia użytkownikowi aktualnego stanu wszystkich dostępnych aukcji.
     */
    void odswiez_liste_aukcji();    //jakby coś miało się zmienić i trzeba było pobrać nową listę z GAPa
    ~OknoGlowne();

signals:
    /*!
     * Sygnał wysyłany przez OknoGlowne w momencie otrzymania informacji od GAPa przez Sterownik o stanie wysłanego żądnia (utworzenia aukcji, wzięcia w niej udziału bądź konieczności wyboru zwycięzcy).
     * \param odp - komunikat zwrotny od serwera.
     * \param powodzenie - informacja o statusie operacji.
     */
    void odpowiedz_serwera(QString odp, bool powodzenie);

public slots:
    /*!
     * Przechwytuje dane z okna dialogowego do stworzenia aukcji w postaci struktury polaAukcji.
     */
    void zlap_nowa_aukcje(polaAukcji pA);
    /*!
     * Przechwytuje dane z okna dialogowego do wzięcia udziału w aukcji jako QString odpowiednio przygotowany.
     */
    void zlap_nowa_oferte(QString of);
    /*!
     * Jeśli logowanie było poprawne, okno startowe wymusza tutaj pokazanie okna głównego.
     */
    void uruchom(bool t);
    /*!
     * Slot do wymuszenia uruchomienia okna dialogowego z wyborem zwycięzcy.
     */
    void wybierz_zwyciezce_wyswietl_okno(QString wZ);

private slots:
    /*!
     * Obsługa zdarzenia związana z podwójnym kliknięciem na element listy auckji.
     */
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    /*!
     * Obsługa zdarzenia związana z kliknięciem przycisku "Stwórz przetarg".
     */
    void on_pushButton_2_clicked();
    /*!
     * Obsługa zdarzenia związana z kliknięciem przycisku "Weź udział".
     */
    void on_pushButton_clicked();
    /*!
     * Obsługa zdarzenia związna z kliknięciem przycisku "Wybierz zwycięzcę".
     */
    void on_pushButton_3_clicked();

private:
    /*!
     * Wskaźnik na user interface.
     */
    Ui::OknoGlowne *ui;
    /*!
     * Lista przechowująca lokalnie numery i nazwy wszystkich dostępnych aukcji.
     */
    QList<QString> listaAukcji;
    /*!
     * Struktura przechowująca loklanie dane o wszystkich dostępnych aukcjach.
     */
    QHash<QString, polaAukcji> bazaAktywnychAukcji;
    /*!
     * Trzeba przetestować, nie wiem czy nie odpad.
     */
    QList<polaAukcji> listaAktywnychAukcji; //pierwsze - nr aukcji, drugie - warunki aukcji
    /*!
     * Dodaje do konosli dane przechowywane przez Sterownik (zmienna _konsola).
     */
    void dopisz_do_konsoli();
    /*!
     * Usuwa niebezpieczne znaki dla obsługi przetargów i zastępuje je zdefiniowanymi symbolami, bądź wykonuje operację odwrotną.
     * \param tekst - tekst do zamiany
     * \param filtr_czy_defiltr - true - zamienia niebezpieczne znaki na symbole; false - zamienia symbole na niebezpieczne znaki.
     * \return - zwraca przefiltrowany QString.
     */
    QString filtr_szkodliwych_znakow(QString tekst, bool filtr_czy_defiltr);
    /*!
     * Pobiera dane aukcji w postaci struktury i przekształca ją do QStringa (ułatwia to szyfrowanie i zarządzanie po stronie GAPa).
     * \param pA - struktura wybranej aukcji.
     * \return - zwraca QString do przesłania dalej.
     */
    QString przygotuj_dane_aukcji_do_wyslania(polaAukcji &pA);
    /*!
     * Pobiera dane aukcji w postaci QString i przekształca je do struktury (ułatwia to obsługę tych danych wewnątrz aplikacji).
     * \param wpis - QString wybranej aukcji.
     * \return - zwraca strukturę aukcji.
     */
    polaAukcji konwertuj_do_struktury(QString wpis);
    /*!
     * Przyjmuje referencję nas sterownik.
     */
    Sterownik& _sterownik;
    /*!
     * Przyjmuje referencję na okno startowe.
     */
    Start& _start;
    /*!
     * Zapewnia, by na pierwszej pozycji listy aukcji była opcja odświeżenia.
     */
    void pierwsze_miejsce_na_liscie_odswieza_liste_aukcji(); //zamiast przycisku, dwuklik na pierwszy element
};

#endif // OKNOGLOWNE_H
