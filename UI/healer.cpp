#include "healer.h"
#include "mainwindow.h"
#include "ui_healer.h"
#include "../Settings/globals.h"
#include "../Settings/actionrule.h"
#include "../Settings/scriptconfig.h"
#include "../Objects/client.h"
#include "ui_hudstatuses.h"
#include <QTableWidget>
#include <iostream>


Healer::Healer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Healer)
{
    ui->setupUi(this);

    this->scriptConfig = Globals::getScriptConfig();

    scriptConfig->HealRules.clear();


    ActionRule* foodA = scriptConfig->addHealRule("foodA", ActionType::Item, "blueberry cupcake");
    foodA->delayType1 = DelayType::CupcakeMp;
    foodA->delayType2 = DelayType::Food;
    foodA->alwaysUse = true;
    ActionRule* foodB = scriptConfig->addHealRule("foodB", ActionType::Item, "blessed steak");
    foodB->delayType1 = DelayType::NpcFood;
    foodB->delayType2 = DelayType::Food;
    foodB->alwaysUse = true;

    ActionRule* spellLo = scriptConfig->addHealRule("spellLo", ActionType::Spell, nullptr);
    spellLo->maxHp = 0;

    ActionRule* magicShieldSpell = scriptConfig->addHealRule("magicShieldSpell", ActionType::Spell, "utamo vita");
    magicShieldSpell->maxMagicShield = 0;
    magicShieldSpell->maxHp = 0;
    magicShieldSpell->minHp = 0;
    magicShieldSpell->delayType1 = DelayType::Utamo;

    ActionRule* magicShieldPotion = scriptConfig->addHealRule("magicShieldPotion", ActionType::Item, "magic shield potion");
    magicShieldPotion->maxMagicShield = 0;
    magicShieldPotion->maxHp = 0;
    magicShieldPotion->minHp = 0;
    magicShieldPotion->alwaysUse = true;
    magicShieldPotion->delayType1 = DelayType::Utamo;

    ActionRule* spellMed = scriptConfig->addHealRule("spellMed", ActionType::Spell, nullptr);
    spellMed->maxHp = 0;

    ActionRule* spellHi = scriptConfig->addHealRule("spellHi", ActionType::Spell, nullptr);
    spellHi->maxHp = 0;

    ActionRule* avatar = scriptConfig->addHealRule("avatar", ActionType::Spell, nullptr);
    avatar->isDefaultValue = false;
    avatar->maxHp = 0;
    avatar->maxMp = 0;

    ActionRule* hpPotionLo = scriptConfig->addHealRule("hpPotionLo", ActionType::Item, "supreme health potion");
    hpPotionLo->maxHp = 0;
    ActionRule* hpPotionHi = scriptConfig->addHealRule("hpPotionHi", ActionType::Item, "ultimate health potion");
    hpPotionHi->maxHp = 0;

    ActionRule* strongHealFriend = scriptConfig->addHealRule("strongHealFriend", ActionType::Spell, "exura gran sio");
    strongHealFriend->maxCreatureHp = (0);
    strongHealFriend->delayType1 = DelayType::Heal;

    ActionRule* healFriend = scriptConfig->addHealRule("healFriend", ActionType::Spell, "exura sio");
    healFriend->delayType1 = DelayType::Heal;

    ActionRule* uhRune = scriptConfig->addHealRule("uhRune", ActionType::Item, "ultimate healing rune");
    uhRune->delayType1 = DelayType::Heal;

    ActionRule* mpPotion = scriptConfig->addHealRule("mpPotion", ActionType::Item, "ultimate mana potion");
    mpPotion->maxMp = 0;

    ActionRule* exanaVitaSpell = scriptConfig->addHealRule("exanaVitaSpell", ActionType::Spell, "exana vita");
    exanaVitaSpell->minMagicShield = 1;
    exanaVitaSpell->minHp = 0;
    exanaVitaSpell->maxMp = 0;

    scriptConfig->setHealerStatus(false);

    ResetUI();
    UpdateUI();
}

Healer::~Healer()
{
    delete ui;
}

void Healer::on_spellHiHp_textChanged(const QString &arg1)
{
    ActionRule *rule = scriptConfig->getHealRule("spellHi");
    rule->maxHp = arg1.toInt();
    rule->isDefaultValue = false;

    rule->enabled = rule->maxHp > 0 && rule->spell != nullptr;
}


void Healer::on_spellMedHp_textChanged(const QString &arg1)
{
    ActionRule *rule = scriptConfig->getHealRule("spellMed");
    rule->maxHp = arg1.toInt();
    rule->isDefaultValue = false;

    rule->enabled = rule->maxHp > 0 && rule->spell != nullptr;
}


void Healer::on_spellLoHp_textChanged(const QString &arg1)
{
    ActionRule *rule = scriptConfig->getHealRule("spellLo");
    rule->maxHp = arg1.toInt();
    rule->isDefaultValue = false;

    rule->enabled = rule->maxHp > 0 && rule->spell != nullptr;
}


void Healer::on_hpPotionHiHp_textChanged(const QString &arg1)
{
    ActionRule *rule = scriptConfig->getHealRule("hpPotionHi");
    rule->maxHp = arg1.toInt();
    rule->isDefaultValue = false;

    rule->enabled = rule->maxHp > 0 && rule->spell != nullptr;
}


void Healer::on_hpPotionLoHp_textChanged(const QString &arg1)
{
    ActionRule *rule = scriptConfig->getHealRule("hpPotionLo");
    rule->maxHp = arg1.toInt();
    rule->isDefaultValue = false;

    rule->enabled = rule->maxHp > 0 && rule->spell != nullptr;
}


void Healer::on_mpPotionMp_textChanged(const QString &arg1)
{
    ActionRule *rule = scriptConfig->getHealRule("mpPotion");
    rule->maxMp = arg1.toInt();
    rule->isDefaultValue = false;

    rule->enabled = rule->maxMp > 0 && rule->spell != nullptr;
}

void Healer::on_healFriendEkStatus_stateChanged(int arg1)
{
    scriptConfig->setHealFriendStatus(Vocation::Knight, arg1);

    ActionRule *healFriend = scriptConfig->getHealRule("healFriend");
    ActionRule *uhRune = scriptConfig->getHealRule("uhRune");

    bool status = scriptConfig->getHealFriendStatus(Vocation::Knight) ||
        scriptConfig->getHealFriendStatus(Vocation::Paladin) ||
        scriptConfig->getHealFriendStatus(Vocation::Druid) ||
        scriptConfig->getHealFriendStatus(Vocation::Sorcerer);

    scriptConfig->setHealFriendGeneralStatus(status);
    healFriend->enabled = status;
    uhRune->enabled = status;


    QObject* parentPtr = this->parent();
    while (parentPtr->parent() != nullptr)
        parentPtr = parentPtr->parent();
    ((MainWindow*)parentPtr)->hudStatuses->ui->healFriendStatus->setChecked(status);
}


void Healer::on_healFriendEkHp_textChanged(const QString &arg1)
{
    scriptConfig->setHealFriendHealth(Vocation::Knight, arg1.toInt());
}


void Healer::on_healFriendRpStatus_stateChanged(int arg1)
{
    scriptConfig->setHealFriendStatus(Vocation::Paladin, arg1);

    ActionRule *healFriend = scriptConfig->getHealRule("healFriend");
    ActionRule *uhRune = scriptConfig->getHealRule("uhRune");

    bool status = scriptConfig->getHealFriendStatus(Vocation::Knight) ||
                  scriptConfig->getHealFriendStatus(Vocation::Paladin) ||
                  scriptConfig->getHealFriendStatus(Vocation::Druid) ||
                  scriptConfig->getHealFriendStatus(Vocation::Sorcerer);

    scriptConfig->setHealFriendGeneralStatus(status);
    healFriend->enabled = status;
    uhRune->enabled = status;


    QObject* parentPtr = this->parent();
    while (parentPtr->parent() != nullptr)
        parentPtr = parentPtr->parent();
    ((MainWindow*)parentPtr)->hudStatuses->ui->healFriendStatus->setChecked(status);
}


void Healer::on_healFriendRpHp_textChanged(const QString &arg1)
{
    scriptConfig->setHealFriendHealth(Vocation::Paladin, arg1.toInt());
}


void Healer::on_healFriendEdStatus_stateChanged(int arg1)
{
    scriptConfig->setHealFriendStatus(Vocation::Druid, arg1);

    ActionRule *healFriend = scriptConfig->getHealRule("healFriend");
    ActionRule *uhRune = scriptConfig->getHealRule("uhRune");

    bool status = scriptConfig->getHealFriendStatus(Vocation::Knight) ||
                  scriptConfig->getHealFriendStatus(Vocation::Paladin) ||
                  scriptConfig->getHealFriendStatus(Vocation::Druid) ||
                  scriptConfig->getHealFriendStatus(Vocation::Sorcerer);

    scriptConfig->setHealFriendGeneralStatus(status);
    healFriend->enabled = status;
    uhRune->enabled = status;


    QObject* parentPtr = this->parent();
    while (parentPtr->parent() != nullptr)
        parentPtr = parentPtr->parent();
    ((MainWindow*)parentPtr)->hudStatuses->ui->healFriendStatus->setChecked(status);
}


void Healer::on_healFriendEdHp_textChanged(const QString &arg1)
{
    scriptConfig->setHealFriendHealth(Vocation::Druid, arg1.toInt());
}


void Healer::on_healFriendMsStatus_stateChanged(int arg1)
{
    scriptConfig->setHealFriendStatus(Vocation::Sorcerer, arg1);

    ActionRule *healFriend = scriptConfig->getHealRule("healFriend");
    ActionRule *uhRune = scriptConfig->getHealRule("uhRune");

    bool status = scriptConfig->getHealFriendStatus(Vocation::Knight) ||
                  scriptConfig->getHealFriendStatus(Vocation::Paladin) ||
                  scriptConfig->getHealFriendStatus(Vocation::Druid) ||
                  scriptConfig->getHealFriendStatus(Vocation::Sorcerer);

    scriptConfig->setHealFriendGeneralStatus(status);
    healFriend->enabled = status;
    uhRune->enabled = status;


    QObject* parentPtr = this->parent();
    while (parentPtr->parent() != nullptr)
        parentPtr = parentPtr->parent();
    ((MainWindow*)parentPtr)->hudStatuses->ui->healFriendStatus->setChecked(status);
}


void Healer::on_healFriendMsHp_textChanged(const QString &arg1)
{
    scriptConfig->setHealFriendHealth(Vocation::Sorcerer, arg1.toInt());
}


void Healer::on_healFriendGuild_stateChanged(int arg1)
{
    scriptConfig->setHealFriendGuild(arg1);
}


void Healer::on_healFriendParty_stateChanged(int arg1)
{
    scriptConfig->setHealFriendParty(arg1);
}


void Healer::on_healFriendList_stateChanged(int arg1)
{
    scriptConfig->setHealFriendList(arg1);
}

void Healer::on_spellHiInput_editingFinished()
{
    ActionRule *rule = scriptConfig->getHealRule("spellHi");
    rule->spell = Globals::getSpell(ui->spellHiInput->text().toStdString());
    rule->isDefaultValue = false;

    rule->enabled = rule->maxHp > 0 && rule->spell != nullptr;
}


void Healer::on_spellMedInput_editingFinished()
{
    ActionRule *rule = scriptConfig->getHealRule("spellMed");
    rule->spell = Globals::getSpell(ui->spellMedInput->text().toStdString());
    rule->isDefaultValue = false;

    rule->enabled = rule->maxHp > 0 && rule->spell != nullptr;
}


void Healer::on_spellLoInput_editingFinished()
{
    ActionRule *rule = scriptConfig->getHealRule("spellLo");
    rule->spell = Globals::getSpell(ui->spellLoInput->text().toStdString());
    rule->isDefaultValue = false;

    rule->enabled = rule->maxHp > 0 && rule->spell != nullptr;
}


void Healer::on_hpPotionHiInput_currentTextChanged(const QString &arg1)
{
    ActionRule *rule = scriptConfig->getHealRule("hpPotionHi");
    rule->spell = Globals::getSpell(arg1.toStdString());
    rule->isDefaultValue = false;

    rule->enabled = rule->maxHp > 0 && rule->spell != nullptr;
}


void Healer::on_hpPotionLoInput_currentTextChanged(const QString &arg1)
{
    ActionRule *rule = scriptConfig->getHealRule("hpPotionLo");
    rule->spell = Globals::getSpell(arg1.toStdString());
    rule->isDefaultValue = false;

    rule->enabled = rule->maxHp > 0 && rule->spell != nullptr;
}


void Healer::on_mpPotionInput_currentTextChanged(const QString &arg1)
{
    ActionRule *rule = scriptConfig->getHealRule("mpPotion");
    rule->spell = Globals::getSpell(arg1.toStdString());
    rule->isDefaultValue = false;

    rule->enabled = rule->maxMp > 0 && rule->spell != nullptr;
}

void Healer::ResetUI()
{
    // RESET UI
    ui->spellHiInput->setText("");
    ui->spellMedInput->setText("");
    ui->spellLoInput->setText("");

    ui->spellHiHp->setText("");
    ui->spellMedHp->setText("");
    ui->spellLoHp->setText("");

    ui->hpPotionHiInput->setCurrentIndex(0);
    ui->hpPotionLoInput->setCurrentIndex(0);
    ui->mpPotionInput->setCurrentIndex(0);


    ui->avatarHp->setText("");
    ui->avatarMp->setText("");
    ui->foodAInput->setCurrentIndex(1);
    ui->foodAValue->setText("");
    ui->foodBInput->setCurrentIndex(0);
    ui->foodBValue->setText("");

    ui->hpPotionHiHp->setText("");
    ui->hpPotionLoHp->setText("");
    ui->mpPotionMp->setText("");

    ui->healFriendGranSioHp->setText("");

    ui->exanaVitaHp->setText("");
    ui->exanaVitaMp->setText("");

    ui->utamoVitaHp->setText("");
    ui->utamoVitaMp->setText("");
    ui->utamoVitaShield->setText("");

    ui->magicPotionHp->setText("");
    ui->magicPotionMp->setText("");
    ui->magicPotionShield->setText("");

    ui->healFriendEkHp->setText("");
    ui->healFriendRpHp->setText("");
    ui->healFriendEdHp->setText("");
    ui->healFriendMsHp->setText("");
}

void Healer::UpdateUI()
{


    ActionRule *spellHi = scriptConfig->getHealRule("spellHi");
    ActionRule *spellMed = scriptConfig->getHealRule("spellMed");
    ActionRule *spellLo = scriptConfig->getHealRule("spellLo");

    ActionRule *hpPotionHi = scriptConfig->getHealRule("hpPotionHi");
    ActionRule *hpPotionLo = scriptConfig->getHealRule("hpPotionLo");
    ActionRule *mpPotion = scriptConfig->getHealRule("mpPotion");

    ActionRule *avatar = scriptConfig->getHealRule("avatar");
    ActionRule *foodA = scriptConfig->getHealRule("foodA");
    ActionRule *foodB = scriptConfig->getHealRule("foodB");

    ActionRule *healFriend = scriptConfig->getHealRule("healFriend");
    ActionRule *strongHealFriend = scriptConfig->getHealRule("strongHealFriend");
    ActionRule *uhRune = scriptConfig->getHealRule("uhRune");

    ActionRule *exanaVitaSpell = scriptConfig->getHealRule("exanaVitaSpell");
    ActionRule *utamoPotion = scriptConfig->getHealRule("magicShieldPotion");
    ActionRule *utamoSpell = scriptConfig->getHealRule("magicShieldSpell");

    // Healer
    //// Spells
    if (spellHi->spell != nullptr)
        ui->spellHiInput->setText(QString::fromStdString(spellHi->spell->words));

    if (spellMed->spell != nullptr)
        ui->spellMedInput->setText(QString::fromStdString(spellMed->spell->words));

    if (spellLo->spell != nullptr)
        ui->spellLoInput->setText(QString::fromStdString(spellLo->spell->words));


    if (spellLo->maxHp != 0)
        ui->spellLoHp->setText(QString::number(spellLo->maxHp));
    if (spellMed->maxHp != 0)
        ui->spellMedHp->setText(QString::number(spellMed->maxHp));
    if (spellHi->maxHp != 0)
        ui->spellHiHp->setText(QString::number(spellHi->maxHp));

    //// Potions
    if (hpPotionHi->spell != nullptr)
        ui->hpPotionHiInput->setCurrentIndex(ui->hpPotionHiInput->findText(QString::fromStdString(hpPotionHi->spell->name), Qt::MatchFixedString));
    if (hpPotionLo->spell != nullptr)
        ui->hpPotionLoInput->setCurrentIndex(ui->hpPotionLoInput->findText(QString::fromStdString(hpPotionLo->spell->name), Qt::MatchFixedString));
    if (mpPotion->spell != nullptr)
        ui->mpPotionInput->setCurrentIndex(ui->mpPotionInput->findText(QString::fromStdString(mpPotion->spell->name), Qt::MatchFixedString));

    if (hpPotionHi->maxHp > 0)
        ui->hpPotionHiHp->setText(QString::number(hpPotionHi->maxHp));
    if (hpPotionLo->maxHp > 0)
        ui->hpPotionLoHp->setText(QString::number(hpPotionLo->maxHp));
    if (mpPotion->maxMp > 0)
        ui->mpPotionMp->setText(QString::number(mpPotion->maxMp));

    // Heal Friend
    if (scriptConfig->getHealFriendHealth(Vocation::Knight) > 0)
        ui->healFriendEkHp->setText(QString::number(scriptConfig->getHealFriendHealth(Vocation::Knight)));
    if (scriptConfig->getHealFriendHealth(Vocation::Paladin) > 0)
    ui->healFriendRpHp->setText(QString::number(scriptConfig->getHealFriendHealth(Vocation::Paladin)));
    if (scriptConfig->getHealFriendHealth(Vocation::Druid) > 0)
    ui->healFriendEdHp->setText(QString::number(scriptConfig->getHealFriendHealth(Vocation::Druid)));
    if (scriptConfig->getHealFriendHealth(Vocation::Sorcerer) > 0)
    ui->healFriendMsHp->setText(QString::number(scriptConfig->getHealFriendHealth(Vocation::Sorcerer)));

    ui->healFriendEkStatus->setChecked(scriptConfig->getHealFriendStatus(Vocation::Knight));
    ui->healFriendRpStatus->setChecked(scriptConfig->getHealFriendStatus(Vocation::Paladin));
    ui->healFriendEdStatus->setChecked(scriptConfig->getHealFriendStatus(Vocation::Druid));
    ui->healFriendMsStatus->setChecked(scriptConfig->getHealFriendStatus(Vocation::Sorcerer));

    ui->healFriendGuild->setChecked(scriptConfig->getHealFriendGuild());
    ui->healFriendParty->setChecked(scriptConfig->getHealFriendParty());
    ui->healFriendList->setChecked(scriptConfig->getHealFriendList());

    ui->healFriendGranSioStatus->setChecked(strongHealFriend->enabled);
    if (strongHealFriend->maxCreatureHp > 0)
        ui->healFriendGranSioHp->setText(QString::number(strongHealFriend->maxCreatureHp));

    // Emergency
    if (avatar->maxHp > 0)
        ui->avatarHp->setText(QString::number(avatar->maxHp));
    if (avatar->maxMp > 0)
        ui->avatarMp->setText(QString::number(avatar->maxMp));

    if (foodA->spell != nullptr)
        ui->foodAInput->setCurrentIndex(ui->foodAInput->findText(QString::fromStdString(foodA->spell->name), Qt::MatchFixedString));
    if (foodB->spell != nullptr)
        ui->foodBInput->setCurrentIndex(ui->foodBInput->findText(QString::fromStdString(foodB->spell->name), Qt::MatchFixedString));

    if ((foodA->maxHp < 100 || foodA->maxMp < 100) && (foodA->maxHp + foodA->maxMp - 100 > 0))
        ui->foodAValue->setText(QString::number(foodA->maxHp + foodA->maxMp - 100));
    if ((foodB->maxHp < 100 || foodB->maxMp < 100) && (foodB->maxHp + foodB->maxMp - 100 > 0))
        ui->foodBValue->setText(QString::number(foodB->maxHp + foodB->maxMp - 100));


    // Magic Shield Manager
    if (exanaVitaSpell->minHp > 0)
        ui->exanaVitaHp->setText(QString::number(exanaVitaSpell->minHp));
    if (exanaVitaSpell->maxMp > 0)
        ui->exanaVitaMp->setText(QString::number(exanaVitaSpell->maxMp));

    if (utamoSpell->maxHp > 0)
        ui->utamoVitaHp->setText(QString::number(utamoSpell->maxHp));
    if (utamoSpell->minMp > 0)
        ui->utamoVitaMp->setText(QString::number(utamoSpell->minMp));
    if (utamoSpell->maxMagicShield > 0)
        ui->utamoVitaShield->setText(QString::number(utamoSpell->maxMagicShield));

    if (utamoPotion->maxHp > 0)
        ui->magicPotionHp->setText(QString::number(utamoPotion->maxHp));
    if (utamoPotion->minMp > 0)
        ui->magicPotionMp->setText(QString::number(utamoPotion->minMp));
    if (utamoPotion->maxMagicShield > 0)
        ui->magicPotionShield->setText(QString::number(utamoPotion->maxMagicShield));
}


void Healer::on_healFriendGranSioStatus_stateChanged(int arg1)
{
    ActionRule *rule = scriptConfig->getHealRule("strongHealFriend");
    rule->enabled = arg1;
    rule->isDefaultValue = false;
}


void Healer::on_healFriendGranSioHp_textChanged(const QString &arg1)
{
    ActionRule *rule = scriptConfig->getHealRule("strongHealFriend");
    rule->maxCreatureHp = arg1.toInt();
    rule->isDefaultValue = false;
}




void Healer::on_utamoVitaHp_textChanged(const QString &arg1)
{
    ActionRule *rule = scriptConfig->getHealRule("magicShieldSpell");
    rule->maxHp = (arg1.toInt());
    rule->isDefaultValue = false;

    rule->enabled = rule->maxHp > 0;
}

void Healer::on_magicPotionHp_textChanged(const QString &arg1)
{
    ActionRule *rule = scriptConfig->getHealRule("magicShieldPotion");
    rule->maxHp = (arg1.toInt());
    rule->isDefaultValue = false;

    rule->enabled = rule->maxHp > 0;
}


void Healer::on_exanaVitaHp_textChanged(const QString &arg1)
{
    ActionRule *rule = scriptConfig->getHealRule("exanaVitaSpell");
    rule->minHp = arg1.toInt();
    rule->isDefaultValue = false;

    rule->enabled = rule->maxMp > 0 || rule->minHp > 0;



    QObject* parentPtr = this->parent();
    while (parentPtr->parent() != nullptr)
        parentPtr = parentPtr->parent();
    ((MainWindow*)parentPtr)->hudStatuses->ui->exanaVitaStatus->setChecked(rule->enabled);
}


void Healer::on_utamoVitaMp_textChanged(const QString &arg1)
{
    ActionRule *rule = scriptConfig->getHealRule("magicShieldSpell");
    rule->minMp = (arg1.toInt());
    rule->isDefaultValue = false;

    rule->enabled = rule->maxHp > 0;
}


void Healer::on_magicPotionMp_textChanged(const QString &arg1)
{
    ActionRule *rule = scriptConfig->getHealRule("magicShieldPotion");
    rule->minMp = (arg1.toInt());
    rule->isDefaultValue = false;

    rule->enabled = rule->maxHp > 0;
}


void Healer::on_exanaVitaMp_textChanged(const QString &arg1)
{
    ActionRule *rule = scriptConfig->getHealRule("exanaVitaSpell");
    rule->maxMp = (arg1.toInt());
    rule->isDefaultValue = false;

    rule->enabled = rule->maxMp > 0 || rule->minHp > 0;



    QObject* parentPtr = this->parent();
    while (parentPtr->parent() != nullptr)
        parentPtr = parentPtr->parent();
    ((MainWindow*)parentPtr)->hudStatuses->ui->exanaVitaStatus->setChecked(rule->enabled);
}

void Healer::on_utamoVitaShield_textChanged(const QString &arg1)
{
    ActionRule *rule = scriptConfig->getHealRule("magicShieldSpell");
    rule->maxMagicShield = (arg1.toInt());
    rule->isDefaultValue = false;

    rule->enabled = rule->maxHp > 0;
}


void Healer::on_magicPotionShield_textChanged(const QString &arg1)
{
    ActionRule *rule = scriptConfig->getHealRule("magicShieldPotion");
    rule->maxMagicShield = (arg1.toInt());
    rule->isDefaultValue = false;

    rule->enabled = rule->maxHp > 0;
}


void Healer::on_avatarHp_textChanged(const QString &arg1)
{
    ActionRule *rule = scriptConfig->getHealRule("avatar");
    rule->maxHp = (arg1.toInt());
    rule->maxMp = (ui->avatarMp->text().toInt());
    rule->isDefaultValue = false;

    rule->enabled = rule->maxHp > 0 || rule->maxMp > 0;
}


void Healer::on_avatarMp_textChanged(const QString &arg1)
{
    ActionRule *rule = scriptConfig->getHealRule("avatar");
    rule->maxMp = (arg1.toInt());
    rule->maxHp = (ui->avatarHp->text().toInt());
    rule->isDefaultValue = false;

    rule->enabled = rule->maxHp > 0 || rule->maxMp > 0;
}

std::map<std::string, bool> isManaFood = {
    {"Blessed Steak", true},
    {"Consecrated Beef", true},
    {"Blueberry Cupcake", true},
    };

void Healer::on_foodAInput_currentTextChanged(const QString &arg1)
{
    ActionRule *rule = scriptConfig->getHealRule("foodA");
    rule->spell = Globals::getSpell(arg1.toStdString());
    rule->isDefaultValue = true;

    if (arg1 == "Blueberry Cupcake")
        rule->delayType1 = DelayType::CupcakeMp;
    else if (arg1 == "Strawberry Cupcake")
        rule->delayType1 = DelayType::CupcakeHp;
    else
        rule->delayType1 = DelayType::NpcFood;

    if (isManaFood[arg1.toStdString()])
    {
        rule->maxHp = 100;
        ui->foodAValueLabel->setText("Mana:");
        ui->foodAValue->setPlaceholderText("Mp%");
    }
    else
    {
        rule->maxMp = 100;
        ui->foodAValueLabel->setText("Health:");
        ui->foodAValue->setPlaceholderText("Hp%");
    }

    ui->foodAValue->setText("");
    rule->enabled = false;
}


void Healer::on_foodBInput_currentTextChanged(const QString &arg1)
{
    ActionRule *rule = scriptConfig->getHealRule("foodB");
    rule->spell = Globals::getSpell(arg1.toStdString());
    rule->isDefaultValue = true;

    if (arg1 == "Blueberry Cupcake")
        rule->delayType1 = DelayType::CupcakeMp;
    else if (arg1 == "Strawberry Cupcake")
        rule->delayType1 = DelayType::CupcakeHp;
    else
        rule->delayType1 = DelayType::NpcFood;


    if (isManaFood[arg1.toStdString()])
    {
        rule->maxHp = 100;
        ui->foodBValueLabel->setText("Mana:");
        ui->foodBValue->setPlaceholderText("Mp%");
    }
    else
    {
        rule->maxMp = 100;
        ui->foodBValueLabel->setText("Health:");
        ui->foodBValue->setPlaceholderText("Hp%");
    }

    ui->foodBValue->setText("");
    rule->enabled = false;
}


void Healer::on_foodAValue_textChanged(const QString &arg1)
{
    ActionRule *rule = scriptConfig->getHealRule("foodA");

    if (isManaFood[ui->foodAInput->currentText().toStdString()])
    {
        rule->maxHp = 100;
        rule->maxMp = (arg1.toInt());
        if (rule->maxMp == 0)
            rule->maxMp = 100;
        rule->enabled = rule->maxMp < 100;
        rule->isDefaultValue = !rule->enabled;
    }
    else
    {
        rule->maxMp = 100;
        rule->maxHp = (arg1.toInt());
        if (rule->maxHp == 0)
            rule->maxHp = 100;
        rule->enabled = rule->maxHp < 100;
        rule->isDefaultValue = !rule->enabled;
    }
}


void Healer::on_foodBValue_textChanged(const QString &arg1)
{
    ActionRule *rule = scriptConfig->getHealRule("foodB");
    rule->isDefaultValue = false;

    if (isManaFood[ui->foodBInput->currentText().toStdString()])
    {
        rule->maxHp = 100;
        rule->maxMp = (arg1.toInt());
        if (rule->maxMp == 0)
            rule->maxMp = 100;
        rule->enabled = rule->maxMp < 100;
        rule->isDefaultValue = !rule->enabled;
    }
    else
    {
        rule->maxMp = 100;
        rule->maxHp = (arg1.toInt());
        if (rule->maxHp == 0)
            rule->maxHp = 100;
        rule->enabled = rule->maxHp < 100;
        rule->isDefaultValue = !rule->enabled;
    }
}

