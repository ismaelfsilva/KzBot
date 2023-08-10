#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

    void authenticate();
    void verifyLicense();
    bool verifySignature(const QString &data, const QString &signature, const QString &publicKeyPath);
    void doLogin(QString email, QString password);

    std::string calculateFileHash(const std::string &filename);
signals:
    void loginSignal();
private slots:
    void on_pushButton_clicked();

    void on_lineEdit_returnPressed();

    void on_lineEdit_2_returnPressed();

private:
    Ui::LoginWindow *ui;
    QString authToken;
};

#endif // LOGINWINDOW_H
