#ifndef PARTYHUNT_H
#define PARTYHUNT_H

#include <QWidget>
#include "../Settings/scriptconfig.h"

namespace Ui {
class PartyHunt;
}

class PartyHunt : public QWidget
{
    Q_OBJECT

public:
    explicit PartyHunt(QWidget *parent = nullptr);
    ~PartyHunt();
    Ui::PartyHunt *ui;

    void UpdateUI();
    void ResetUI();
private slots:
    void on_ultimateSpellStatus_stateChanged(int arg1);

    void on_ultimateSpellInput_textChanged(const QString &arg1);

    void on_ultimateSpellCreatureQty_textChanged(const QString &arg1);

    void on_ultimateSpellMaxHp_textChanged(const QString &arg1);

    void on_areaSpellStatus_stateChanged(int arg1);

    void on_areaSpellInput_textChanged(const QString &arg1);

    void on_areaSpellCreatureQty_textChanged(const QString &arg1);

    void on_waveAStatus_stateChanged(int arg1);

    void on_waveAInput_textChanged(const QString &arg1);

    void on_waveACreatureQty_textChanged(const QString &arg1);

    void on_waveATurn_stateChanged(int arg1);

    void on_waveBStatus_stateChanged(int arg1);

    void on_waveBInput_textChanged(const QString &arg1);

    void on_waveBCreatureQty_textChanged(const QString &arg1);

    void on_waveBTurn_stateChanged(int arg1);

    void on_areaRuneStatus_stateChanged(int arg1);

    void on_areaRuneInput_currentTextChanged(const QString &arg1);

    void on_areaRuneCreatureQty_textChanged(const QString &arg1);

    void on_singleTargetAStatus_stateChanged(int arg1);

    void on_singleTargetAInput_currentTextChanged(const QString &arg1);

    void on_singleTargetACreatureQty_textChanged(const QString &arg1);

    void on_singleTargetAMaxHp_textChanged(const QString &arg1);

    void on_singleTargetBStatus_stateChanged(int arg1);

    void on_singleTargetBInput_currentTextChanged(const QString &arg1);

    void on_singleTargetBCreatureQty_textChanged(const QString &arg1);

    void on_singleTargetBMaxHp_textChanged(const QString &arg1);

    void on_singleTargetAInput_currentIndexChanged(int index);

    void on_singleTargetBInput_currentIndexChanged(int index);

    void on_msDebuffStatus_stateChanged(int arg1);

    void on_msDebuffInput_textChanged(const QString &arg1);

    void on_msDebuffCreatureQty_textChanged(const QString &arg1);

    void on_autoTargetStatus_stateChanged(int arg1);

    void on_knightSpellRotation_stateChanged(int arg1);

    void on_knightExetaRes_stateChanged(int arg1);

    void on_knightUtamoTempoStatus_stateChanged(int arg1);

    void on_knightUtitoTempoStatus_stateChanged(int arg1);

    void on_knightUtamoTempoHp_textChanged(const QString &arg1);

    void on_knightUtitoTempoHp_textChanged(const QString &arg1);

    void on_checkBox_clicked(bool checked);

private:
    ScriptConfig *scriptConfig;
};

#endif // PARTYHUNT_H
