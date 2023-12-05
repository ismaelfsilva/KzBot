#ifndef TOOLSTAB_H
#define TOOLSTAB_H

#include "../Settings/globals.h"
#include <QWidget>

namespace Ui {
class ToolsTab;
}

class ToolsTab : public QWidget
{
    Q_OBJECT

public:
    explicit ToolsTab(QWidget *parent = nullptr);
    ~ToolsTab();

    void UpdateUi();
    void ResetUi();
    void updateReadInventory();
private slots:
    void on_antiParalyzeSpellInput_editingFinished();
    void on_hasteSpellInput_editingFinished();

    void on_defaultAmuletInput_editingFinished();
    void on_defaultRingInput_editingFinished();

    void on_ssaHp_textChanged(const QString &arg1);
    void on_ssaMp_textChanged(const QString &arg1);

    void on_energyRingHp_textChanged(const QString &arg1);
    void on_energyRingMp_textChanged(const QString &arg1);

    void on_mightRingHp_textChanged(const QString &arg1);
    void on_mightRingMp_textChanged(const QString &arg1);

    void on_defaultAmuletRefresh_clicked();

    void on_defaultRingRefresh_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_3_stateChanged(int arg1);

    void on_checkBox_5_stateChanged(int arg1);

    void on_lineEdit_editingFinished();

    void on_lineEdit_2_editingFinished();

    void on_checkBox_4_stateChanged(int arg1);

    void on_lineEdit_3_editingFinished();

private:
    ScriptConfig *scriptConfig;
    Ui::ToolsTab *ui;
};

#endif // TOOLSTAB_H
