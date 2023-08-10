#ifndef PVPTOOLS_H
#define PVPTOOLS_H

#include <QWidget>

namespace Ui {
class PvpTools;
}

class PvpTools : public QWidget
{
    Q_OBJECT

public:
    explicit PvpTools(QWidget *parent = nullptr);
    ~PvpTools();

    void UpdateUi();
private slots:
    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_3_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_combo1Leader_textChanged(const QString &arg1);

    void on_combo2Leader_textChanged(const QString &arg1);

    void on_combo3Leader_textChanged(const QString &arg1);

    void on_combo1Content_textChanged(const QString &arg1);

    void on_combo2Content_textChanged(const QString &arg1);

    void on_combo3Content_textChanged(const QString &arg1);

    void on_combo1Input_textChanged(const QString &arg1);

    void on_combo2Input_textChanged(const QString &arg1);

    void on_combo3Input_textChanged(const QString &arg1);

private:
    Ui::PvpTools *ui;
};

#endif // PVPTOOLS_H
