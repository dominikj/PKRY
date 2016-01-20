#ifndef WYBIERZZWYCIEZCE_H
#define WYBIERZZWYCIEZCE_H

#include <QDialog>
#include <QString>

namespace Ui {
class WybierzZwyciezce;
}
/*!
 * Klasa odpowiada za stworzenie okna z wyborem zwycięzcy.
 */
class WybierzZwyciezce : public QDialog
{
    Q_OBJECT

public:
    /*!
     * Konstruktor klasy WybierzZwyciezce.
     */
    explicit WybierzZwyciezce(QWidget *parent = 0);
    /*!
     * Funkcja poprzez którą obiekt tworzący instancję klasy WybierzZwyciezce może przekazać dane oferentów do wyświetlenia.
     * \param string_lista_ofert - oferty wszystkich biorących udział w przetargu.
     */
    void przekaz_liste_ofert(QString string_lista_ofert);
    ~WybierzZwyciezce();

signals:
    /*!
     * Sygnał emitowany do Sterownika o wyborze zwycięzcy.
     * \param zwyciezca - zawiera informację o zwycięzcy.
     * \param wzieci_pod_uwage - zawiera informację o uczestnikach biorących udział.
     */
    void info_dla_sterownika(QString zwyciezca, QString wzieci_pod_uwage);

public slots:
    /*!
     * \brief wyswietl_okno - wymusza wyświetlenie okna dialogowego tej klasy.
     * \param dane - tutaj są przekazywane te same dane, które mogą zostać przekazane przez funkcję przekaz_liste_ofert(). Różnica polega na tym kto tworzy instancję tej klasy i jakie ma zamiary.
     */
    void wyswietl_okno(QString dane);
    /*!
     * Slot dla odpowiedzi serwera o stanie wysłanej informacji o wyborze zwycięzcy.
     * \param odpowiedz - zawiera odpowiedź serwera.
     */
    void odpowiedz_serwera(QString odpowiedz);

private slots:
    /*!
     * Wymusza wysłanie informacji o zwycięzcy i o ofertach biorących udział.
     */
    void on_pushButton_clicked();

private:
  //  Sterownik& _ster;
    /*!
     * Pole tekstowe przechowujące informację o numerze rozstrzyganej aukcji.
     */
    QString numer_aukcji;
    /*!
     * Lista zawierająca przesłane oferty.
     */
    QList<QString> lista_ofert;
    /*!
     * Lista zawierająca numery oferentów. Odpowiada liście numer_aukcji.
     */
    QList<QString> lista_numerow_oferentow;
    /*!
     * Powoduje wypisanie w polu tekstowym ofert, które zostały przekazane do obiektu.
     */
    void wyswietl_oferty();
    /*!
     * Wskaźnik na user interface.
     */
    Ui::WybierzZwyciezce *ui;
};

#endif // WYBIERZZWYCIEZCE_H
