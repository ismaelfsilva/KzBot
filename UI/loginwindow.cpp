#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "mainwindow.h"
#include "../Settings/globals.h"

#include <QMessageBox>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <filesystem>
#include <iomanip>
#include <openssl/evp.h>
#include <QMessageAuthenticationCode>

#include <iostream>
#include <QSettings>

#include <fstream>
#include <sstream>
#include <openssl/sha.h>

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);


    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);

    std::string hash = calculateFileHash(path);
    Globals::hash = hash;
    std::cout << "Current Hash: " << Globals::hash << std::endl;

    QSettings mySettings("KzSoft", "KzBot - Tibia");
    mySettings.sync();
    if(!mySettings.value("remember").isNull() && mySettings.value("remember").toBool()) {
        ui->checkBox->setChecked(true);
        if(!mySettings.value("email").isNull()) {
            ui->lineEdit->setText(mySettings.value("email").toString());
        }
        if(!mySettings.value("password").isNull()) {
            ui->lineEdit_2->setText(mySettings.value("password").toString());
        }

        if(!mySettings.value("loginauto").isNull() && mySettings.value("loginauto").toBool()) {
            ui->checkBox_2->setChecked(true);

            ui->pushButton->setEnabled(false);
            LoginWindow::doLogin(this->ui->lineEdit->text(), this->ui->lineEdit_2->text());
            ui->pushButton->setEnabled(true);
        }
    }
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

// Faz a solicitação de login ao servidor PHP
void LoginWindow::doLogin(QString email, QString password) {
    QUrl url("https://tibia.kzsoft.com.br/login.php");

    QByteArray postData;
    postData.append("email=").append(QUrl::toPercentEncoding(email));
    postData.append("&password=").append(QUrl::toPercentEncoding(password));
    postData.append("&product_id=").append(QUrl::toPercentEncoding(QString::number(4)));
    postData.append("&hash=").append(QUrl::toPercentEncoding(QString::fromStdString(Globals::hash)));

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QNetworkReply *reply = manager->post(request, postData);



    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() != QNetworkReply::NoError) {
            QMessageBox::critical(this, tr("Authentication Failed"), tr("There was an error while trying to authenticate. Please try again later. If this error persists, contact support and inform code 0x01."));
            return;
        }

        QByteArray response = reply->readAll();

        QJsonParseError error;
        QJsonDocument document = QJsonDocument::fromJson(response, &error);


        if (error.error != QJsonParseError::NoError) {
            QMessageBox::critical(this, tr("Authentication Failed"), tr("There was an error while trying to authenticate. Please try again later. If this error persists, contact support and inform code 0x02."));
            return;
        }

        QJsonObject object = document.object();

        if (!object.value("error").isNull() && object.value("error").toString().length() > 0)
        {
            QMessageBox::critical(this, tr("Authentication Failed"), object.value("error").toString());
            return;
        }

        QString loginMessage = object.value("message").toString();
        QString signature = object.value("signature").toString();
        QJsonObject userObject = object.value("user").toObject();

        int userId = userObject.value("user_id").toString().toInt();
        QString username = userObject.value("username").toString();
        QString email = userObject.value("email").toString();
        int timestamp = userObject.value("timestamp").toInt();


        std::vector<QByteArray> keys = {
                                   "7p9Fj6Aq0Wt4vRg3Dn2L",
                                   "3zX5dMv7Hb1Jk9Pc8NfR",
                                   "2wG4yEh5Sj3Vt6Ub1QxP",
                                   "9lK6nTf3Xj8Hc7Zm5VbR",
                                   "1bN4vGh2Dm7Kt9Qc3XwS",
                                   "8rZ7lBt5Ym3Fk2Nj1HvG",
                                   "4wT3rSf2Jl6Bn1Qc9VgH",
                                   "5nH2jMf6Xb3Dv1Rg7KtP",
                                   "6q0Wt4Yh8Jc7Vb9Nm2Lp",
                                   "2fD5gR7nH1kT3jM4bVx"
        };

        // Verificar a assinatura digital do token
        QByteArray privateKey = keys[userId % 10];
        // Converter payload em QByteArray
        QByteArray input = QJsonDocument(userObject).toJson(QJsonDocument::Compact);
        QByteArray calculatedSignature = QMessageAuthenticationCode::hash(input, privateKey, QCryptographicHash::Sha256).toHex();

        if (signature != calculatedSignature) {
            QMessageBox::critical(this, tr("Authentication Failed"), tr("There was an error while trying to authenticate. Please try again later. If this error persists, contact support and inform code 0x03."));
            return;
        }

        Globals::setUsername(username);
        Globals::setEmail(email);
        Globals::setPassword(password);
        Globals::setUserId(userId);
        Globals::setLoginTimestamp(timestamp);
        Globals::setUserSignature(signature);
        Globals::setUserObject(userObject);

        QSettings mySettings("KzSoft", "KzBot - Tibia");
        if (ui->checkBox->isChecked())
        {
            mySettings.setValue("remember", true);
            mySettings.setValue("email", email);
            mySettings.setValue("password", password);
            mySettings.setValue("loginauto", ui->checkBox_2->isChecked());
        }
        else
        {
            mySettings.setValue("remember", false);
            mySettings.setValue("email", NULL);
            mySettings.setValue("password", NULL);
            mySettings.setValue("loginauto", NULL);
        }
        mySettings.sync();

        if (!loginMessage.isEmpty())
            QMessageBox::information(this, "KzBot", loginMessage);

        emit loginSignal();
        close();

        // Token válido, fazer login do usuário
    });

}

void LoginWindow::on_pushButton_clicked()
{
    ui->pushButton->setEnabled(false);
    LoginWindow::doLogin(this->ui->lineEdit->text(), this->ui->lineEdit_2->text());
    ui->pushButton->setEnabled(true);
}


void LoginWindow::on_lineEdit_returnPressed()
{
    ui->pushButton->setEnabled(false);
    ui->pushButton->click();
    ui->pushButton->setEnabled(true);
}


void LoginWindow::on_lineEdit_2_returnPressed()
{
    ui->pushButton->setEnabled(false);
    ui->pushButton->click();
    ui->pushButton->setEnabled(true);
}

std::string LoginWindow::calculateFileHash(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return "";
    }

    // Cálculo do valor da hash
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);

    char buffer[4096];
    while (file.read(buffer, sizeof(buffer))) {
        SHA256_Update(&sha256, buffer, file.gcount());
    }
    SHA256_Final(hash, &sha256);

    // Conversão do valor da hash para uma string hexadecimal
    std::ostringstream oss;
    for (unsigned char c : hash) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c);
    }

    return oss.str();
}
