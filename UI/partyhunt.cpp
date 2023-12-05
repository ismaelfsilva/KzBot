#include "partyhunt.h"
#include "mainwindow.h"
#include "ui_hudstatuses.h"
#include "ui_partyhunt.h"
#include "../Settings/globals.h"
#include "../Objects/client.h"
#include <QMessageBox>

PartyHunt::PartyHunt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PartyHunt)
{
    ui->setupUi(this);

    this->scriptConfig = Globals::getScriptConfig();

    scriptConfig->KnightTargetRules.clear();
    scriptConfig->TargetRules.clear();


    // Target Rules
    ActionRule* ultimateSpell = scriptConfig->addTargetRule("ultimateSpell", ActionType::Spell, nullptr);
    scriptConfig->setPartyHuntUltimateHealth(ultimateSpell->maxCreatureHp);

    ActionRule* areaSpell = scriptConfig->addTargetRule("areaSpell", ActionType::Spell, nullptr);

    ActionRule* waveA = scriptConfig->addTargetRule("waveA", ActionType::Spell, nullptr);
    waveA->centerKnight = true;
    ActionRule* waveB = scriptConfig->addTargetRule("waveB", ActionType::Spell, nullptr);
    waveB->centerKnight = true;
    ActionRule* areaRune = scriptConfig->addTargetRule("areaRune", ActionType::Rune, "Avalanche Rune");

    ActionRule* singleTargetA = scriptConfig->addTargetRule("singleTargetA", ActionType::Rune, "Sudden Death Rune");
    singleTargetA->isDefaultValue = false;
    ActionRule* singleTargetB = scriptConfig->addTargetRule("singleTargetB", ActionType::Rune, "Sudden Death Rune");
    singleTargetB->isDefaultValue = false;
    ActionRule* msDebuff = scriptConfig->addTargetRule("msDebuff", ActionType::Spell, nullptr);
    msDebuff->centerKnight = true;


    // Knight Target Rules;
    ActionRule* exoriGran = scriptConfig->addKnightTargetRule("exoriGran", ActionType::Spell, "exori gran");
    exoriGran->enabled = true;
    ActionRule* exoriMed = scriptConfig->addKnightTargetRule("exoriMed", ActionType::Spell, "exori mas");
    exoriMed->enabled = true;
    ActionRule* exori = scriptConfig->addKnightTargetRule("exori", ActionType::Spell, "exori");
    exori->enabled = true;


    ActionRule* utamoTempo = scriptConfig->addKnightTargetRule("utamoTempo", ActionType::Spell, "utamo tempo");
    ActionRule* utitoTempo = scriptConfig->addKnightTargetRule("utitoTempo", ActionType::Spell, "utito tempo");
    ActionRule* exetaRes = scriptConfig->addKnightTargetRule("exetaRes", ActionType::Spell, "exeta res");

    PartyHunt::ResetUI();
    PartyHunt::UpdateUI();
}

PartyHunt::~PartyHunt()
{
    delete ui;
}

void PartyHunt::ResetUI()
{
    ui->ultimateSpellStatus->setChecked(false);
    ui->areaSpellStatus->setChecked(false);
    ui->waveAStatus->setChecked(false);
    ui->waveBStatus->setChecked(false);
    ui->areaRuneStatus->setChecked(false);
    ui->singleTargetAStatus->setChecked(false);
    ui->singleTargetBStatus->setChecked(false);
    ui->msDebuffStatus->setChecked(false);

    ui->ultimateSpellInput->setText("");
    ui->areaSpellInput->setText("");
    ui->waveAInput->setText("");
    ui->waveBInput->setText("");
    ui->areaRuneInput->setCurrentText("Avalanche Rune");
    ui->singleTargetAInput->setCurrentText("Sudden Death Rune");
    ui->singleTargetBInput->setCurrentText("Sudden Death Rune");
    ui->msDebuffInput->setText("");

    ui->ultimateSpellCreatureQty->setText("");
    ui->areaSpellCreatureQty->setText("");
    ui->waveACreatureQty->setText("");
    ui->waveBCreatureQty->setText("");
    ui->areaRuneCreatureQty->setText("");
    ui->singleTargetACreatureQty->setText("1");
    ui->singleTargetBCreatureQty->setText("1");
    ui->msDebuffCreatureQty->setText("");

    ui->waveATurn->setChecked(false);
    ui->waveBTurn->setChecked(false);

    ui->ultimateSpellMaxHp->setText("100");
    ui->singleTargetAMaxHp->setText("100");
    ui->singleTargetBMaxHp->setText("100");

    ui->knightSpellRotation->setChecked(false);
    ui->knightExetaRes->setChecked(false);
    ui->knightUtamoTempoStatus->setChecked(false);
    ui->knightUtitoTempoStatus->setChecked(false);
    ui->knightUtamoTempoHp->setText("");
    ui->knightUtitoTempoHp->setText("");
}

void PartyHunt::UpdateUI()
{
    // Knight Area
    ActionRule* exetaRes = scriptConfig->getKnightTargetRule("exetaRes");
    ActionRule* utamoTempo = scriptConfig->getKnightTargetRule("utamoTempo");
    ActionRule* utitoTempo = scriptConfig->getKnightTargetRule("utitoTempo");

    ui->knightSpellRotation->setChecked(scriptConfig->getPartyHuntUseEKCombo());
    ui->knightExetaRes->setChecked(exetaRes->enabled);
    ui->knightUtamoTempoStatus->setChecked(utamoTempo->enabled);
    ui->knightUtitoTempoStatus->setChecked(utitoTempo->enabled);
    if (utamoTempo->maxHp != 100)
        ui->knightUtamoTempoHp->setText(QString::number(utamoTempo->maxHp));
    if (utitoTempo->minHp != 0)
        ui->knightUtitoTempoHp->setText(QString::number(utamoTempo->minHp));

    // Spell Caster
    ActionRule* ultimateSpell = scriptConfig->getTargetRule("ultimateSpell");
    ActionRule* areaSpell = scriptConfig->getTargetRule("areaSpell");
    ActionRule* waveA = scriptConfig->getTargetRule("waveA");
    ActionRule* waveB = scriptConfig->getTargetRule("waveB");
    ActionRule* areaRune = scriptConfig->getTargetRule("areaRune");
    ActionRule* singleTargetA = scriptConfig->getTargetRule("singleTargetA");
    ActionRule* singleTargetB = scriptConfig->getTargetRule("singleTargetB");
    ActionRule* msDebuff = scriptConfig->getTargetRule("msDebuff");

    ui->ultimateSpellStatus->setChecked(ultimateSpell->enabled);
    ui->areaSpellStatus->setChecked(areaSpell->enabled);
    ui->waveAStatus->setChecked(waveA->enabled);
    ui->waveBStatus->setChecked(waveB->enabled);
    ui->areaRuneStatus->setChecked(areaRune->enabled);
    ui->singleTargetAStatus->setChecked(singleTargetA->enabled);
    ui->singleTargetBStatus->setChecked(singleTargetB->enabled);
    ui->msDebuffStatus->setChecked(msDebuff->enabled);

    if (ultimateSpell->spell != nullptr)
        ui->ultimateSpellInput->setText(QString::fromStdString(ultimateSpell->spell->words));
    if (areaSpell->spell != nullptr)
        ui->areaSpellInput->setText(QString::fromStdString(areaSpell->spell->words));
    if (waveA->spell != nullptr)
        ui->waveAInput->setText(QString::fromStdString(waveA->spell->words));
    if (waveB->spell != nullptr)
        ui->waveBInput->setText(QString::fromStdString(waveB->spell->words));
    if (areaRune->spell != nullptr)
        ui->areaRuneInput->setCurrentText(QString::fromStdString(areaRune->spell->name));
    if (singleTargetA->spell != nullptr && singleTargetA->spell->itemId > 0)
        ui->singleTargetAInput->setCurrentText(QString::fromStdString(singleTargetA->spell->name));
    else if (singleTargetA->spell != nullptr)
        ui->singleTargetAInput->setCurrentText(QString::fromStdString(singleTargetA->spell->words));

    if (singleTargetB->spell != nullptr && singleTargetB->spell->itemId > 0)
        ui->singleTargetBInput->setCurrentText(QString::fromStdString(singleTargetB->spell->name));
    else if (singleTargetB->spell != nullptr)
        ui->singleTargetBInput->setCurrentText(QString::fromStdString(singleTargetB->spell->words));

    if (msDebuff->spell != nullptr)
        ui->msDebuffInput->setText(QString::fromStdString(msDebuff->spell->words));

    if (ultimateSpell->creatureCount > 0)
        ui->ultimateSpellCreatureQty->setText(QString::number(ultimateSpell->creatureCount));
    if (areaSpell->creatureCount > 0)
        ui->areaSpellCreatureQty->setText(QString::number(areaSpell->creatureCount));
    if (waveA->creatureCount > 0)
        ui->waveACreatureQty->setText(QString::number(waveA->creatureCount));
    if (waveB->creatureCount > 0)
        ui->waveBCreatureQty->setText(QString::number(waveB->creatureCount));
    if (areaRune->creatureCount > 0)
        ui->areaRuneCreatureQty->setText(QString::number(areaRune->creatureCount));
    if (msDebuff->creatureCount > 0)
        ui->msDebuffCreatureQty->setText(QString::number(msDebuff->creatureCount));

    ui->waveATurn->setChecked(waveA->turn);
    ui->waveBTurn->setChecked(waveB->turn);

    if (ultimateSpell->maxCreatureHp > 0)
        ui->ultimateSpellMaxHp->setText(QString::number(ultimateSpell->maxCreatureHp));
    if (singleTargetA->maxCreatureHp > 0)
        ui->singleTargetAMaxHp->setText(QString::number(singleTargetA->maxCreatureHp));
    if (singleTargetB->maxCreatureHp > 0)
        ui->singleTargetBMaxHp->setText(QString::number(singleTargetB->maxCreatureHp));

    // Others
    ui->autoTargetStatus->setChecked(scriptConfig->getPartyHuntAutoTargetStatus());
    ui->checkBox->setChecked(scriptConfig->getPartyHuntUseTargetNext());
}

// Ultimate Spell
void PartyHunt::on_ultimateSpellStatus_stateChanged(int arg1)
{
    ActionRule* targetRule = scriptConfig->getTargetRule("ultimateSpell");
    targetRule->isDefaultValue = false;
    targetRule->enabled = (arg1);
}


void PartyHunt::on_ultimateSpellInput_textChanged(const QString &arg1)
{
    ActionRule* targetRule = scriptConfig->getTargetRule("ultimateSpell");
    targetRule->isDefaultValue = false;
    targetRule->spell = Globals::getSpell(arg1.toStdString());
}


void PartyHunt::on_ultimateSpellCreatureQty_textChanged(const QString &arg1)
{
    ActionRule* targetRule = scriptConfig->getTargetRule("ultimateSpell");
    targetRule->isDefaultValue = false;
    targetRule->creatureCount = (arg1.toInt());
}


void PartyHunt::on_ultimateSpellMaxHp_textChanged(const QString &arg1)
{
    ActionRule* targetRule = scriptConfig->getTargetRule("ultimateSpell");
    targetRule->maxCreatureHp = (arg1.toInt());
    targetRule->isDefaultValue = false;
    scriptConfig->setPartyHuntUltimateHealth(targetRule->maxCreatureHp);
}

// Area Spell
void PartyHunt::on_areaSpellStatus_stateChanged(int arg1)
{
    ActionRule* targetRule = scriptConfig->getTargetRule("areaSpell");
    targetRule->isDefaultValue = false;
    targetRule->enabled = (arg1);
}


void PartyHunt::on_areaSpellInput_textChanged(const QString &arg1)
{
    ActionRule* targetRule = scriptConfig->getTargetRule("areaSpell");
    targetRule->isDefaultValue = false;
    targetRule->spell = Globals::getSpell(arg1.toStdString());
}


void PartyHunt::on_areaSpellCreatureQty_textChanged(const QString &arg1)
{
    ActionRule* targetRule = scriptConfig->getTargetRule("areaSpell");
    targetRule->isDefaultValue = false;
    targetRule->creatureCount = (arg1.toInt());
}

// Wave A

void PartyHunt::on_waveAStatus_stateChanged(int arg1)
{
    ActionRule* targetRule = scriptConfig->getTargetRule("waveA");
    targetRule->isDefaultValue = false;
    targetRule->enabled = (arg1);
}


void PartyHunt::on_waveAInput_textChanged(const QString &arg1)
{
    ActionRule* targetRule = scriptConfig->getTargetRule("waveA");
    targetRule->isDefaultValue = false;
    targetRule->spell = Globals::getSpell(arg1.toStdString());
}


void PartyHunt::on_waveACreatureQty_textChanged(const QString &arg1)
{
    ActionRule* targetRule = scriptConfig->getTargetRule("waveA");
    targetRule->isDefaultValue = false;
    targetRule->creatureCount = (arg1.toInt());
}


void PartyHunt::on_waveATurn_stateChanged(int arg1)
{
    ActionRule* targetRule = scriptConfig->getTargetRule("waveA");
    targetRule->isDefaultValue = false;
    targetRule->turn = (arg1);
}

// Wave B



void PartyHunt::on_waveBStatus_stateChanged(int arg1)
{
    ActionRule* targetRule = scriptConfig->getTargetRule("waveB");
    targetRule->isDefaultValue = false;
    targetRule->enabled = (arg1);
}


void PartyHunt::on_waveBInput_textChanged(const QString &arg1)
{
    ActionRule* targetRule = scriptConfig->getTargetRule("waveB");
    targetRule->isDefaultValue = false;
    targetRule->spell = Globals::getSpell(arg1.toStdString());
}


void PartyHunt::on_waveBCreatureQty_textChanged(const QString &arg1)
{
    ActionRule* targetRule = scriptConfig->getTargetRule("waveB");
    targetRule->isDefaultValue = false;
    targetRule->creatureCount = (arg1.toInt());
}


void PartyHunt::on_waveBTurn_stateChanged(int arg1)
{
    ActionRule* targetRule = scriptConfig->getTargetRule("waveB");
    targetRule->isDefaultValue = false;
    targetRule->turn = (arg1);
}

// Area Rune



void PartyHunt::on_areaRuneStatus_stateChanged(int arg1)
{
    ActionRule* targetRule = scriptConfig->getTargetRule("areaRune");
    targetRule->isDefaultValue = false;
    targetRule->enabled = (arg1);
    scriptConfig->setPartyHuntAreaRune(arg1);
}


void PartyHunt::on_areaRuneInput_currentTextChanged(const QString &arg1)
{
    ActionRule* targetRule = scriptConfig->getTargetRule("areaRune");
    targetRule->isDefaultValue = false;
    targetRule->spell = Globals::getSpell(arg1.toStdString());
}


void PartyHunt::on_areaRuneCreatureQty_textChanged(const QString &arg1)
{
    ActionRule* targetRule = scriptConfig->getTargetRule("areaRune");
    targetRule->isDefaultValue = false;
    targetRule->creatureCount = (arg1.toInt());
}

// Single Target A

void PartyHunt::on_singleTargetAStatus_stateChanged(int arg1)
{
    ActionRule* targetRule = scriptConfig->getTargetRule("singleTargetA");
    targetRule->isDefaultValue = false;
    targetRule->enabled = (arg1);
}


void PartyHunt::on_singleTargetAInput_currentTextChanged(const QString &arg1)
{
    ActionRule* targetRule = scriptConfig->getTargetRule("singleTargetA");
    targetRule->isDefaultValue = false;
    targetRule->spell = Globals::getSpell(arg1.toStdString());
}



void PartyHunt::on_singleTargetAInput_currentIndexChanged(int index)
{
    ActionRule* targetRule = scriptConfig->getTargetRule("singleTargetA");
    targetRule->isDefaultValue = false;
    targetRule->spell = Globals::getSpell(ui->singleTargetAInput->currentText().toStdString());
}



void PartyHunt::on_singleTargetACreatureQty_textChanged(const QString &arg1)
{
    ActionRule* targetRule = scriptConfig->getTargetRule("singleTargetA");
    targetRule->isDefaultValue = false;
    targetRule->creatureCount = (arg1.toInt());
}


void PartyHunt::on_singleTargetAMaxHp_textChanged(const QString &arg1)
{
    ActionRule* targetRule = scriptConfig->getTargetRule("singleTargetA");
    targetRule->isDefaultValue = false;
    targetRule->maxCreatureHp = (arg1.toInt());
}

// Single Target B



void PartyHunt::on_singleTargetBStatus_stateChanged(int arg1)
{
    ActionRule* targetRule = scriptConfig->getTargetRule("singleTargetB");
    targetRule->isDefaultValue = false;
    targetRule->enabled = (arg1);
}


void PartyHunt::on_singleTargetBInput_currentTextChanged(const QString &arg1)
{
    ActionRule* targetRule = scriptConfig->getTargetRule("singleTargetB");
    targetRule->isDefaultValue = false;
    targetRule->spell = Globals::getSpell(arg1.toStdString());
}


void PartyHunt::on_singleTargetBInput_currentIndexChanged(int index)
{
    ActionRule* targetRule = scriptConfig->getTargetRule("singleTargetB");
    targetRule->isDefaultValue = false;
    targetRule->spell = Globals::getSpell(ui->singleTargetBInput->currentText().toStdString());
}


void PartyHunt::on_singleTargetBCreatureQty_textChanged(const QString &arg1)
{
    ActionRule* targetRule = scriptConfig->getTargetRule("singleTargetB");
    targetRule->isDefaultValue = false;
    targetRule->maxCreatureHp = (arg1.toInt());
}


void PartyHunt::on_singleTargetBMaxHp_textChanged(const QString &arg1)
{
    ActionRule* targetRule = scriptConfig->getTargetRule("singleTargetB");
    targetRule->isDefaultValue = false;
    targetRule->maxCreatureHp = (arg1.toInt());
}


// MS Debuff



void PartyHunt::on_msDebuffStatus_stateChanged(int arg1)
{
    ActionRule* targetRule = scriptConfig->getTargetRule("msDebuff");
    targetRule->isDefaultValue = false;
    targetRule->enabled = (arg1);
}


void PartyHunt::on_msDebuffInput_textChanged(const QString &arg1)
{
    ActionRule* targetRule = scriptConfig->getTargetRule("msDebuff");
    targetRule->isDefaultValue = false;
    targetRule->spell = Globals::getSpell(arg1.toStdString());

}


void PartyHunt::on_msDebuffCreatureQty_textChanged(const QString &arg1)
{
    ActionRule* targetRule = scriptConfig->getTargetRule("msDebuff");
    targetRule->isDefaultValue = false;
    targetRule->creatureCount = (arg1.toInt());
}


void PartyHunt::on_autoTargetStatus_stateChanged(int arg1)
{
    scriptConfig->setPartyHuntAutoTargetStatus(arg1);
    ui->checkBox->setEnabled(arg1);

    QObject* parentPtr = this->parent();
    while (parentPtr->parent() != nullptr)
        parentPtr = parentPtr->parent();
    ((MainWindow*)parentPtr)->hudStatuses->ui->autoTargetStatus->setChecked(arg1);
}

void PartyHunt::on_knightSpellRotation_stateChanged(int arg1)
{
    scriptConfig->setPartyHuntUseEKCombo(arg1);
}


void PartyHunt::on_knightExetaRes_stateChanged(int arg1)
{
    ActionRule* knightTargetRule = scriptConfig->getKnightTargetRule("exetaRes");
    knightTargetRule->enabled = arg1;
}


void PartyHunt::on_knightUtamoTempoStatus_stateChanged(int arg1)
{
    ActionRule* knightTargetRule = scriptConfig->getKnightTargetRule("utamoTempo");
    knightTargetRule->enabled = arg1;
}


void PartyHunt::on_knightUtitoTempoStatus_stateChanged(int arg1)
{
    ActionRule* knightTargetRule = scriptConfig->getKnightTargetRule("utitoTempo");
    knightTargetRule->enabled = arg1;

}


void PartyHunt::on_knightUtamoTempoHp_textChanged(const QString &arg1)
{
    ActionRule* knightTargetRule = scriptConfig->getKnightTargetRule("utamoTempo");
    if (arg1.toInt() > 0)
        knightTargetRule->maxHp = arg1.toInt();
    else
        knightTargetRule->maxHp = 100;
}


void PartyHunt::on_knightUtitoTempoHp_textChanged(const QString &arg1)
{
    ActionRule* knightTargetRule = scriptConfig->getKnightTargetRule("utitoTempo");
    knightTargetRule->minHp = arg1.toInt();
}

void PartyHunt::on_checkBox_clicked(bool checked)
{
    if (checked)
    {
        for (Objects::KeyBinding* keyBinding : Objects::Client::getKeyBindings())
        {
            if (keyBinding->getName() == "AttackNextTarget")
            {
                scriptConfig->setPartyHuntUseTargetNext(checked);
                bool ext;
                scriptConfig->setPartyHuntTargetNextKey(keyBinding->getKey(ext));
                scriptConfig->setPartyHuntTargetNextKeyExtended(ext);

                return;
            }
        }
        QMessageBox::critical(this, tr("Hotkey Missing"), tr("Kz Bot wasn't able to detect your Target Next Hotkey, make sure it's set."));
        ui->checkBox->click();
    }
    else
        scriptConfig->setPartyHuntUseTargetNext(checked);

}

