#ifndef HEALER_H
#define HEALER_H

#include <QWidget>
#include "../Settings/globals.h"

namespace Ui {
class Healer;
}

class Healer : public QWidget
{
    Q_OBJECT

public:
    explicit Healer(QWidget *parent = nullptr);
    ~Healer();
    void UpdateUI();
    void ResetUI();
private slots:
    // Inputs
    void on_spellHiInput_editingFinished();
    void on_spellMedInput_editingFinished();
    void on_spellLoInput_editingFinished();
    void on_hpPotionHiInput_currentTextChanged(const QString &arg1);
    void on_hpPotionLoInput_currentTextChanged(const QString &arg1);
    void on_mpPotionInput_currentTextChanged(const QString &arg1);

    // Health
    void on_spellHiHp_textChanged(const QString &arg1);
    void on_spellMedHp_textChanged(const QString &arg1);
    void on_spellLoHp_textChanged(const QString &arg1);
    void on_hpPotionHiHp_textChanged(const QString &arg1);
    void on_hpPotionLoHp_textChanged(const QString &arg1);

    // Mana
    void on_mpPotionMp_textChanged(const QString &arg1);

    // Heal Friend
    void on_healFriendEkStatus_stateChanged(int arg1);
    void on_healFriendEkHp_textChanged(const QString &arg1);

    void on_healFriendRpStatus_stateChanged(int arg1);
    void on_healFriendRpHp_textChanged(const QString &arg1);

    void on_healFriendEdStatus_stateChanged(int arg1);
    void on_healFriendEdHp_textChanged(const QString &arg1);

    void on_healFriendMsStatus_stateChanged(int arg1);
    void on_healFriendMsHp_textChanged(const QString &arg1);

    void on_healFriendGuild_stateChanged(int arg1);
    void on_healFriendParty_stateChanged(int arg1);
    void on_healFriendList_stateChanged(int arg1);

    void on_healFriendGranSioStatus_stateChanged(int arg1);

    void on_healFriendGranSioHp_textChanged(const QString &arg1);

    // Mana Shield
    void on_exanaVitaMp_textChanged(const QString &arg1);
    void on_exanaVitaHp_textChanged(const QString &arg1);

    void on_magicPotionMp_textChanged(const QString &arg1);
    void on_magicPotionHp_textChanged(const QString &arg1);

    void on_utamoVitaMp_textChanged(const QString &arg1);
    void on_utamoVitaHp_textChanged(const QString &arg1);

    void on_utamoVitaShield_textChanged(const QString &arg1);

    void on_magicPotionShield_textChanged(const QString &arg1);

    void on_avatarHp_textChanged(const QString &arg1);

    void on_avatarMp_textChanged(const QString &arg1);

    void on_foodAInput_currentTextChanged(const QString &arg1);

    void on_foodBInput_currentTextChanged(const QString &arg1);

    void on_foodAValue_textChanged(const QString &arg1);

    void on_foodBValue_textChanged(const QString &arg1);

private:
    Ui::Healer *ui;
    ScriptConfig *scriptConfig;
};

#endif // HEALER_H
