#include "szyfrowanie.h"
#include <QDebug>
#include <memory>
#include <QFile>
#include <ctime>
#include <QDataStream>
#include <cryptopp/osrng.h>

Szyfrowanie::Szyfrowanie()
{

}
/**
 * @brief generuje parę kluczy: publiczny i prywatny
 * @return struktura kluczy
 */
Klucze Szyfrowanie::generujKlucze() {
    AutoSeeded_RNG rand;
    RSA_PrivateKey klucz(rand, KLUCZ_ROZM);
    QString pub = QString::fromStdString(X509::PEM_encode(klucz));
    QString priv = QString::fromStdString(PKCS8::PEM_encode(klucz));
    Klucze klucze = {pub.toLatin1(), priv.toLatin1()};
    return klucze;
}
/**
 * @brief Szyfruje dane
 * @param klucz klucz szyfrujący
 * @param dane dane do zaszyfrowania
 * @return dane zaszyfrowane
 */
QByteArray Szyfrowanie::szyfruj(QString klucz, QByteArray dane) {
    AutoSeeded_RNG rand;
    DataSource_Memory kluczMem(klucz.toStdString());
    X509_PublicKey *kluczRsa = X509::load_key(kluczMem);
    Botan::PK_Encryptor *enc = get_pk_encryptor(*kluczRsa, "EME1(SHA-256)");
    QByteArray tablicaDanych = dane;
    byte wiadomosc[tablicaDanych.count()];
    for (int i = 0; i < tablicaDanych.count(); i++)
    {
        wiadomosc[i] = tablicaDanych[i];
    }
    SecureVector<byte> zaszyfrowanyVector = enc->encrypt(wiadomosc, sizeof(wiadomosc), rand);
    QByteArray zaszyfrowanyTekst;

    for (uint i = 0; i < zaszyfrowanyVector.size(); i++)
    {
        zaszyfrowanyTekst[i] = zaszyfrowanyVector[i];
    }
    return zaszyfrowanyTekst;
}
/**
 * @brief deszyfruje dane
 * @param klucz klucz deszyfrujący
 * @param dane dane zaszyfrowane
 * @return dane jawne
 */
QByteArray Szyfrowanie::deszyfruj(QString klucz, QByteArray dane) {
    AutoSeeded_RNG rand;
    DataSource_Memory kluczMem(klucz.toStdString());
    PKCS8_PrivateKey *kluczRsa= PKCS8::load_key(kluczMem, rand);
    Botan::PK_Decryptor *dec = get_pk_decryptor(*kluczRsa, "EME1(SHA-256)");
    SecureVector<byte> daneVector;
    for(int i = 0; i < dane.length(); ++i ) {
        daneVector.push_back(dane[i]);
    }

    auto tekstJawnyVector = dec->decrypt(daneVector, daneVector.size());

    QByteArray tekstJawny;
    for (uint i = 0; i < tekstJawnyVector.size(); i++)
    {
        tekstJawny[i] = tekstJawnyVector[i];
    }

    return tekstJawny;

}
/**
 * @brief generuje podpis danych
 * @param klucz
 * @param dane
 * @return podpis
 */
QByteArray Szyfrowanie::podpisz(QString klucz, QByteArray dane) {
    AutoSeeded_RNG rand;
    DataSource_Memory kluczMem(klucz.toStdString());
    PKCS8_PrivateKey *kluczRsa = PKCS8::load_key(kluczMem, rand);
    Botan::PK_Signer* signer = get_pk_signer(*kluczRsa, "EMSA1(SHA-256)");
    byte wiadomosc[dane.count()];
    for (int i = 0; i < dane.count(); i++)
    {
        wiadomosc[i] = dane[i];
    }

    SecureVector<byte> podpisVector = signer->sign_message(wiadomosc, sizeof(wiadomosc),rand);
    QByteArray podpisTekst;
    for (uint i = 0; i < podpisVector.size(); i++)
    {
        podpisTekst[i] = podpisVector[i];
    }

    return podpisTekst;

}
/**
 * @brief sprawdza prawidłowość podpisu
 * @param klucz
 * @param podpis
 * @param dane
 * @return poprawny/niepoprawny podpis
 */
bool Szyfrowanie::sprawdzPodpis(QString klucz, QByteArray podpis, QByteArray dane) {
    DataSource_Memory kluczMem(klucz.toStdString());
    X509_PublicKey *kluczRsa = X509::load_key(kluczMem);
    Botan::PK_Verifier* verifier = get_pk_verifier(*kluczRsa, "EMSA1(SHA-256)");
    byte wiadomosc[dane.count()];
    for (int i = 0; i < dane.count(); i++)
    {
        wiadomosc[i] = dane[i];
    }
    byte pod[podpis.count()];
    for (int i = 0; i < podpis.count(); i++)
    {
        pod[i] = podpis[i];
    }
    bool jestPoprawny = verifier->verify_message(wiadomosc, sizeof(wiadomosc), pod, sizeof(pod));
    return jestPoprawny;
}
/**
 * @brief Generuje podział danych wg algorytmu Shamira
 * @param minimalneUczestnictwo
 * @param liczbaUdzialow
 * @param dane
 * @return fragmenty danych
 */
std::vector<QByteArray> Szyfrowanie::podzielSekret(int minimalneUczestnictwo, int liczbaUdzialow, QByteArray dane) { // TODO: Przerobić tego potworka na coś porządnego
    zapiszDoBufora(dane,QString("tmp"));
    std::string ziarno = std::to_string(std::time(NULL));
    ziarno.resize(16, ' ');

    RandomPool rng;
    rng.IncorporateEntropy((byte *)ziarno.c_str(), strlen(ziarno.c_str()));

    ChannelSwitch *przelacznikKanalow;
    FileSource zrodlo("tmp", false, new SecretSharing(rng, minimalneUczestnictwo, liczbaUdzialow, przelacznikKanalow = new ChannelSwitch));

    vector_member_ptrs<FileSink> plikowyZlew(liczbaUdzialow);
    std::string kanal;
    for (int i=0; i<liczbaUdzialow; i++)
    {
        char rozszerzenie[5] = ".000";
        rozszerzenie[1]='0'+byte(i/100);
        rozszerzenie[2]='0'+byte((i/10)%10);
        rozszerzenie[3]='0'+byte(i%10);
        plikowyZlew[i].reset(new FileSink((std::string("tmp")+rozszerzenie).c_str()));

        kanal = WordToString<word32>(i);
        plikowyZlew[i]->Put((const byte *)kanal.data(), 4);
        przelacznikKanalow->AddRoute(kanal, *plikowyZlew[i], DEFAULT_CHANNEL);
    }

    zrodlo.PumpAll();
    QFile::remove("tmp");
    return wczytajZBufora(liczbaUdzialow,"tmp.");

}
/**
 * @brief Scala dane wcześniej podzielone
 * @param minimalneUczestnictwo
 * @return scalone dane
 */
QByteArray Szyfrowanie::przywrocSekret(int minimalneUczestnictwo, std::vector<QByteArray> dane)
{
    QString nazwa;
    for (int i=0; i<minimalneUczestnictwo; i++) {
        if(i < 10)
            nazwa = QString::fromStdString("tmp.00" + std::to_string(i));
        else if(i < 100)
            nazwa = QString::fromStdString("tmp.0" + i);
        else
            nazwa = QString::fromStdString("tmp." + i);
        zapiszDoBufora(dane[i], nazwa);
    }
    SecretRecovery przywracanie(minimalneUczestnictwo, new FileSink("out.000"));
    CryptoPP::vector_member_ptrs<FileSource> zrodlaPlikowe(minimalneUczestnictwo);
    CryptoPP::SecByteBlock kanal(4);
    int i;
    for (i=0; i<minimalneUczestnictwo; i++)
    {
        if(i < 10)
            nazwa = QString::fromStdString("tmp.00" + std::to_string(i));
        else if(i < 100)
            nazwa = QString::fromStdString("tmp.0" + i);
        else
            nazwa = QString::fromStdString("tmp." + i);
        zrodlaPlikowe[i].reset(new FileSource(nazwa.toStdString().c_str(), false));
        zrodlaPlikowe[i]->Pump(4);
        zrodlaPlikowe[i]->Get(kanal, 4);
        zrodlaPlikowe[i]->Attach(new ChannelSwitch(przywracanie, std::string((char *)kanal.begin(), 4)));
    }

    while (zrodlaPlikowe[0]->Pump(256))
        for (i=1; i<minimalneUczestnictwo; i++)
            zrodlaPlikowe[i]->Pump(256);

    for (i=0; i<minimalneUczestnictwo; i++)
        zrodlaPlikowe[i]->PumpAll();
    auto sek = wczytajZBufora(1,"out.");
    return sek[0];
}


void Szyfrowanie::zapiszDoBufora(QByteArray dane, QString nazwa) {
    CryptoPP::StringSource ss( dane.toStdString(), true /*pumpAll*/, new CryptoPP::FileSink( nazwa.toStdString().c_str()) );
}

std::vector<QByteArray> Szyfrowanie::wczytajZBufora(int liczbaFragmentow, std::string prefix) {
    std::vector<QByteArray> buf;
    QString nazwa;
    for(int i = 0; i < liczbaFragmentow; ++i ) {
        if(i < 10)
            nazwa = QString::fromStdString(prefix +"00" + std::to_string(i));
        else if(i < 100)
            nazwa = QString::fromStdString(prefix  + "0" + std::to_string(i));
        else
            nazwa = QString::fromStdString(prefix  + std::to_string(i));
        std::string s;
        CryptoPP::FileSource( nazwa.toStdString().c_str(), true, new StringSink( s ) );
        buf.push_back( QByteArray::fromStdString(s));
    }
    return buf;
}
