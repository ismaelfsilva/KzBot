#ifndef CONFIGHELPER_H
#define CONFIGHELPER_H

#include <QMainWindow>

namespace Ui {
class ConfigHelper;
}

class ConfigHelper : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConfigHelper(QWidget *parent = nullptr);
    ~ConfigHelper();

private slots:
    void on_radioButton_toggled(bool checked);

    void on_radioButton_2_toggled(bool checked);

    void on_radioButton_3_toggled(bool checked);

    void on_radioButton_4_toggled(bool checked);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::ConfigHelper *ui;
};

#endif // CONFIGHELPER_H
