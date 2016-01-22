#ifndef AUKCJA_H
#define AUKCJA_H
#include <QObject>
#include <vector>
#include <QDateTime>
#include <QTimer>

class Uzytkownik;
/**
 * @brief sktuktura pojedynczej oferty
 */
struct Oferta{
    QString nazwaUczestnika;
    QByteArray oferta;
    QString numerUczestnika;
    bool uzyte = false;
};
/**
 * @brief klasa pojedyczej aukcji
 */
class Aukcja : public QObject
{
    Q_OBJECT
public:
    int numerAukcji;
    int numerFirmy;
    bool czyFirmaOdpytana = false;
    QByteArray kluczPublicznyAukcji;
    QByteArray kluczPrywatnyAukcjiCzescGAP;
    QByteArray kluczPrywatnyAukcjiCzescFirma;
    QByteArray kluczPrywatnyAukcjiCzescUczestnicy;
    QDateTime zakonczenie;
    QString firmaNazwa;
    QByteArray parametry;
    std::vector<Oferta> oferty;
    QTimer timer;
    Aukcja();
signals:
 void zakonczonaAukcja(Aukcja*);
public slots:
 void czasSieSkonczyl();
};

#endif // AUKCJA_H
