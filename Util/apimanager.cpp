#include "apimanager.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDebug>

ApiManager::ApiManager(QObject *parent) : QObject(parent)
{
    m_publicKey = readPublicKey(":/public_key.pem");
}

void ApiManager::authenticate(const QString &username, const QString &password)
{
    QUrl url("https://yourserveraddress:3333/api/authenticate");
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["username"] = username;
    json["password"] = password;
    QByteArray jsonData = QJsonDocument(json).toJson(QJsonDocument::Compact);

    QNetworkReply *reply = m_networkManager.post(request, jsonData);
    connect(reply, &QNetworkReply::finished, this, &ApiManager::handleAuthenticationFinished);
}

void ApiManager::verifyLicense(const QString &token, const QString &licenseKey)
{
    QUrl url("https://yourserveraddress:3333/api/verify_license");
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", token.toUtf8());

    QJsonObject json;
    json["licenseKey"] = licenseKey;
    QByteArray jsonData = QJsonDocument(json).toJson(QJsonDocument::Compact);

    QNetworkReply *reply = m_networkManager.post(request, jsonData);
    connect(reply, &QNetworkReply::finished, this, &ApiManager::handleLicenseVerificationFinished);
}

void ApiManager::handleAuthenticationFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObj = jsonDoc.object();
        QString token = jsonObj["token"].toString();
        emit authenticationFinished(token, true);

        // Example usage: verify license key after successful authentication
        verifyLicense(token, "your_license_key_here");

    } else {
        emit authenticationFinished(QString(), false);
    }

    reply->deleteLater();
}

void ApiManager::handleLicenseVerificationFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObj = jsonDoc.object();
        QByteArray signature = QByteArray::fromBase64(jsonObj["signature"].toString().toUtf8());
        QJsonObject dataObj = jsonObj["data"].toObject();
        QByteArray data = QJsonDocument(dataObj).toJson(QJsonDocument::Compact);

        bool validSignature = verifySignature(data, signature, m_publicKey);

        if (validSignature) {
            bool validLicense = dataObj["validLicense"].toBool();
            QString message = dataObj["message"].toString();
            emit licenseVerificationFinished(validLicense, message);
        } else {
            qDebug() << "Signature verification failed";
        }

    } else {
        emit licenseVerificationFinished(false, "License verification request failed");
    }

    reply->deleteLater();
}

RSA *ApiManager::readPublicKey(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Unable to open public key file:" << filename;
        return nullptr;
    }

    QByteArray publicKeyPEM = file.readAll();
    file.close();

    BIO *bio = BIO_new_mem_buf(publicKeyPEM.constData(), publicKeyPEM.size());
    RSA *rsa = PEM_read_bio_RSA_PUBKEY(bio, nullptr, nullptr, nullptr);
    BIO_free(bio);

    return rsa;
}

bool ApiManager::verifySignature(const QByteArray &data, const QByteArray &signature, RSA *publicKey)
{
    if (!publicKey) {
        return false;
    }

    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    bool result = false;

    EVP_PKEY* evp_key = EVP_PKEY_new();
    EVP_PKEY_set1_RSA(evp_key, publicKey);

    if (EVP_DigestVerifyInit(mdctx, nullptr, EVP_sha256(), nullptr, evp_key) == 1) {
        if (EVP_DigestVerifyUpdate(mdctx, data.constData(), data.size()) == 1) {
            result = (EVP_DigestVerifyFinal(mdctx, reinterpret_cast<const unsigned char *>(signature.constData()), signature.size()) == 1);
        }
    }

    EVP_MD_CTX_free(mdctx);
    EVP_PKEY_free(evp_key);
    return result;
}
