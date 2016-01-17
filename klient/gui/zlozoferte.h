#ifndef ZLOZOFERTE_H
#define ZLOZOFERTE_H

#include <QDialog>
#include <QString>
#include <QDateTime>
#include <QList>
#include "oknoglowne.h"
class OknoGlowne;

namespace Ui {
class zlozOferte;
}

/*!
 * Klasa odpowiedzialna za okno dialogowe składanie nowej oferty w przetargu.
 */
class zlozOferte : public QDialog
{
    Q_OBJECT

public:
    /*!
     * Pobiera informacje o aktualnie zaznaczonym przetargu w oknie głównym.
     * \param nr_aukcji - numer zaznaczonego przetargu.
     * \param nazwa_aukcji - nazwa zaznaczonego przetargu.
     * \param data_zak - data zakończenia zaznaczonego przetargu.
     * \param kryteria - kryteria brane pod uwagę w zaznaczonym przetargu.
     */
    void wez_dane_aukcji(QString nr_aukcji, QString nazwa_aukcji, QDateTime data_zak, QList<QString> kryteria);
    /*!
     * Konstruktor klasy zlozOferte.
     * \param parent
     */
    explicit zlozOferte(QWidget *parent = 0);
    ~zlozOferte();

signals:
    /*!
     * Sygnał emitowany do Sterownika ze stworzoną ofertą.
     * \param of - oferta oferenta zamieniona do QStringa.
     */
    void skladanie_oferty(QString of);

private slots:
    /*!
     * Zamyka okno składania oferty.
     */
    void on_pushButton_2_clicked();
    /*!
     * Po kliknięciu pobiera dane z pól, waliduje, przetwarza do QStringa i przekazuje do Sterownika do wysłania.
     */
    void on_pushButton_clicked();
    /*!
     * Przechwytuje wiadomość od GAPa o stanie składanej oferty.
     * \param odp - odpowiedź tekstowa od serwera.
     * \param powodzenie - zmienna typu bool; true - złożenie zakończone powodzeniem.
     */
    void odpowiedz_od_serwera(QString odp, bool powodzenie);

private:
    /*!
     * \brief ui
     */
    Ui::zlozOferte *ui;
    /*!
     * Pole tekstowe przechowujące numer aukcji.
     */
    QString numer_aukcji;
    /*!
     * Przygotowuje pewne elementy okna do prawidłowego wyświetlania.
     */
    void przygotuj();
};

#endif // ZLOZOFERTE_H
