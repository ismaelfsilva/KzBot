#ifndef APIMANAGER_H
#define APIMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/evp.h>

class ApiManager : public QObject
{
    Q_OBJECT
public:
    explicit ApiManager(QObject *parent = nullptr);
    void authenticate(const QString &username, const QString &password);
    void verifyLicense(const QString &token, const QString &licenseKey);

signals:
    void authenticationFinished(const QString &token, bool success);
    void licenseVerificationFinished(bool validLicense, const QString &message);

private slots:
    void handleAuthenticationFinished(QNetworkReply *reply);
    void handleLicenseVerificationFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager m_networkManager;
    RSA *m_publicKey;
    RSA *readPublicKey(const QString &filename);
    bool verifySignature(const QByteArray &data, const QByteArray &signature, RSA *publicKey);
};

#endif // APIMANAGER_H
