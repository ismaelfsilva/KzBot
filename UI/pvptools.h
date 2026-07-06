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
    Ui::PvpTools *ui;
    bool nativeEvent(const QByteArray& eventType, void* message, qintptr* result);

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

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_lineEdit_3_textChanged(const QString &arg1);

    void on_checkBox_10_stateChanged(int arg1);

    void on_checkBox_11_stateChanged(int arg1);

    void on_lineEdit_4_textChanged(const QString &arg1);

    void on_lineEdit_5_textChanged(const QString &arg1);

    void on_clearTileDest_clicked();

    void on_protSqmFlowerSource_clicked();

    void on_protSqmKey_editingFinished();

    void on_clearTileKey_editingFinished();

    void on_comboInput_textChanged(const QString &arg1);

    void on_comboKey_editingFinished();

    void on_comboStatus_stateChanged(int arg1);

private:
};

#endif // PVPTOOLS_H
