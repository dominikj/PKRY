#include "szyfrowanie.h"
#include <QDebug>

Szyfrowanie::Szyfrowanie()
{
    return;
    X509_PublicKey* p =X509::load_key("skcca");
    QString s;
    s.fromStdString(
    (X509::PEM_encode(*p))
                );
    qDebug() << s;

}
Klucze Szyfrowanie::generujKlucze(){
    AutoSeeded_RNG rand;
    RSA_PrivateKey klucz(rand, 2048);
    QString pub = QString::fromStdString(X509::PEM_encode(klucz));
    QString priv = QString::fromStdString(PKCS8::PEM_encode(klucz));
    Klucze klucze = {pub, priv};
    return klucze;
}

QByteArray Szyfrowanie::szyfruj(QString klucz, QString dane){
      AutoSeeded_RNG rand;
     DataSource_Memory kluczMem(klucz.toStdString());
     X509_PublicKey *kluczRsa = X509::load_key(kluczMem);
     PK_Encryptor *enc = get_pk_encryptor(*kluczRsa, "EME1(SHA-256)");
     QByteArray tablicaDanych = dane.toLatin1();
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

QByteArray Szyfrowanie::deszyfruj(QString klucz, QByteArray dane){
    AutoSeeded_RNG rand;
    DataSource_Memory kluczMem(klucz.toStdString());
    PKCS8_PrivateKey *kluczRsa= PKCS8::load_key(kluczMem, rand);
    PK_Decryptor *dec = get_pk_decryptor(*kluczRsa, "EME1(SHA-256)");
    SecureVector<byte> daneVector;
    for(int i = 0; i < dane.length(); ++i ){
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

QByteArray Szyfrowanie::podpisz(QString klucz, QByteArray dane){
    AutoSeeded_RNG rand;
     DataSource_Memory kluczMem(klucz.toStdString());
     PKCS8_PrivateKey *kluczRsa = PKCS8::load_key(kluczMem, rand);
    PK_Signer* signer = get_pk_signer(*kluczRsa, "EMSA1(SHA-256)");
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

bool Szyfrowanie::sprawdzPodpis(QString klucz, QByteArray podpis, QByteArray dane){
    DataSource_Memory kluczMem(klucz.toStdString());
     X509_PublicKey *kluczRsa = X509::load_key(kluczMem);
    PK_Verifier* verifier = get_pk_verifier(*kluczRsa, "EMSA1(SHA-256)");
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
