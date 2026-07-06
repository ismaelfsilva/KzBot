#include "toolstab.h"
#include "../Settings/globals.h"
#include "mainwindow.h"
#include "ui_hudstatuses.h"
#include "ui_toolstab.h"
#include "../Objects/inventoryitem.h"
#include "../Objects/client.h"
#include "../Objects/game.h"

ToolsTab::ToolsTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolsTab)
{
    ui->setupUi(this);

    this->scriptConfig = Globals::getScriptConfig();


    ActionRule* defaultAmuletEquip = scriptConfig->addToolsRule("defaultAmuletEquip", ActionType::Equip, nullptr);
    defaultAmuletEquip->delayType1 = DelayType::DefaultAmulet;
    ActionRule* defaultRingEquip = scriptConfig->addToolsRule("defaultRingEquip", ActionType::Equip, nullptr);
    defaultRingEquip->delayType1 = DelayType::DefaultRing;

    ActionRule* stoneSkinAmuletEquip = scriptConfig->addToolsRule("stoneSkinAmuletEquip", ActionType::Equip, "Stone Skin Amulet");
    stoneSkinAmuletEquip->maxHp = 0;
    stoneSkinAmuletEquip->maxMp = 0;
    stoneSkinAmuletEquip->delayType1 = DelayType::EquipAmulet;
    ActionRule* energyRingEquip = scriptConfig->addToolsRule("energyRingEquip", ActionType::Equip, "Energy Ring");
    energyRingEquip->maxHp = 0;
    energyRingEquip->minHp = 0;
    energyRingEquip->delayType1 = DelayType::EquipRing;
    ActionRule* mightRingEquip = scriptConfig->addToolsRule("mightRingEquip", ActionType::Equip, "Might Ring");
    mightRingEquip->maxHp = 0;
    mightRingEquip->maxMp = 0;
    mightRingEquip->delayType1 = DelayType::EquipRing;

    ActionRule* antiParalyzeSpell = scriptConfig->addToolsRule("antiParalyzeSpell", ActionType::Spell, nullptr);
    antiParalyzeSpell->onParalyzeSpell = true;
    ActionRule* hasteSpell = scriptConfig->addToolsRule("hasteSpell", ActionType::Spell, nullptr);
    hasteSpell->hasteSpell = true;

    ActionRule* manaTrainSpell = scriptConfig->addToolsRule("manaTrain", ActionType::Spell, nullptr);
    manaTrainSpell->minMp = 95;

    ResetUi();
    UpdateUi();
}

ToolsTab::~ToolsTab()
{
    delete ui;
}

void ToolsTab::updateReadInventory()
{
    ActionRule *stoneSkinAmulet = scriptConfig->getToolsRule("stoneSkinAmuletEquip");
    ActionRule *energyRing = scriptConfig->getToolsRule("energyRingEquip");
    ActionRule *mightRing = scriptConfig->getToolsRule("mightRingEquip");

    ActionRule *defaultAmuletEquip = scriptConfig->getToolsRule("defaultAmuletEquip");
    ActionRule *defaultRingEquip = scriptConfig->getToolsRule("defaultRingEquip");

    scriptConfig->setToolsReadInventory(
        stoneSkinAmulet->enabled ||
        energyRing->enabled ||
        mightRing->enabled ||
        defaultAmuletEquip->enabled ||
        defaultRingEquip->enabled
        );
}

void ToolsTab::on_ssaHp_textChanged(const QString &arg1)
{
    ActionRule *rule = scriptConfig->getToolsRule("stoneSkinAmuletEquip");
    rule->maxHp = (arg1.toInt());
    rule->isDefaultValue = false;

    rule->enabled = rule->maxHp > 0 || rule->maxMp > 0;
    updateReadInventory();


    QObject* parentPtr = this->parent();
    while (parentPtr->parent() != nullptr)
        parentPtr = parentPtr->parent();
    ((MainWindow*)parentPtr)->hudStatuses->ui->autoSSAStatus->setChecked(rule->enabled);
}

void ToolsTab::on_ssaMp_textChanged(const QString &arg1)
{
    ActionRule *rule = scriptConfig->getToolsRule("stoneSkinAmuletEquip");
    rule->maxMp = (arg1.toInt());
    rule->isDefaultValue = false;

    rule->enabled = rule->maxHp > 0 || rule->maxMp > 0;
    updateReadInventory();


    QObject* parentPtr = this->parent();
    while (parentPtr->parent() != nullptr)
        parentPtr = parentPtr->parent();
    ((MainWindow*)parentPtr)->hudStatuses->ui->autoSSAStatus->setChecked(rule->enabled);
}


void ToolsTab::on_energyRingHp_textChanged(const QString &arg1)
{
    ActionRule *rule = scriptConfig->getToolsRule("energyRingEquip");
    rule->maxHp = (arg1.toInt());
    rule->isDefaultValue = false;

    rule->enabled = rule->maxHp > 0 || rule->minMp > 0;
    updateReadInventory();
}


void ToolsTab::on_energyRingMp_textChanged(const QString &arg1)
{
    ActionRule *rule = scriptConfig->getToolsRule("energyRingEquip");
    rule->minMp = (arg1.toInt());
    rule->isDefaultValue = false;

    rule->enabled = rule->maxHp > 0 || rule->minMp > 0;
    updateReadInventory();
}


void ToolsTab::on_mightRingHp_textChanged(const QString &arg1)
{
    ActionRule *rule = scriptConfig->getToolsRule("mightRingEquip");
    rule->maxHp = (arg1.toInt());
    rule->isDefaultValue = false;

    rule->enabled = rule->maxHp > 0 || rule->maxMp > 0;
    updateReadInventory();

    QObject* parentPtr = this->parent();
    while (parentPtr->parent() != nullptr)
        parentPtr = parentPtr->parent();
    ((MainWindow*)parentPtr)->hudStatuses->ui->autoMRStatus->setChecked(rule->enabled);
}


void ToolsTab::on_mightRingMp_textChanged(const QString &arg1)
{
    ActionRule *rule = scriptConfig->getToolsRule("mightRingEquip");
    rule->maxMp = (arg1.toInt());
    rule->isDefaultValue = false;

    rule->enabled = rule->maxHp > 0 || rule->maxMp > 0;
    updateReadInventory();


    QObject* parentPtr = this->parent();
    while (parentPtr->parent() != nullptr)
        parentPtr = parentPtr->parent();
    ((MainWindow*)parentPtr)->hudStatuses->ui->autoMRStatus->setChecked(rule->enabled);
}

void ToolsTab::ResetUi()
{
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");

    ui->checkBox_3->setChecked(false);
    ui->checkBox_5->setChecked(false);
    ui->checkBox_4->setChecked(false);

    ui->antiParalyzeSpellInput->setText("");
    ui->hasteSpellInput->setText("");

    ui->ssaHp->setText("");
    ui->ssaMp->setText("");

    ui->energyRingHp->setText("");
    ui->energyRingMp->setText("");

    ui->mightRingHp->setText("");
    ui->mightRingMp->setText("");

    ui->defaultAmuletInput->setText("");
    ui->defaultRingInput->setText("");
}

void ToolsTab::UpdateUi()
{
    ActionRule *antiParalyzeSpell = scriptConfig->getToolsRule("antiParalyzeSpell");
    ActionRule *hasteSpell = scriptConfig->getToolsRule("hasteSpell");

    ActionRule *ssaEquip = scriptConfig->getToolsRule("stoneSkinAmuletEquip");
    ActionRule *energyEquip = scriptConfig->getToolsRule("energyRingEquip");
    ActionRule *mightEquip = scriptConfig->getToolsRule("mightRingEquip");
    ActionRule *defaultAmuletEquip = scriptConfig->getToolsRule("defaultAmuletEquip");
    ActionRule *defaultRingEquip = scriptConfig->getToolsRule("defaultRingEquip");

    ActionRule *manaTrainSpell = scriptConfig->getToolsRule("manaTrain");

    // Speed Manager
    if (antiParalyzeSpell->spell != nullptr)
        ui->antiParalyzeSpellInput->setText(QString::fromStdString(antiParalyzeSpell->spell->words));
    if (hasteSpell->spell != nullptr)
        ui->hasteSpellInput->setText(QString::fromStdString(hasteSpell->spell->words));

    // Equipment Manager
    if (ssaEquip->maxHp > 0)
        ui->ssaHp->setText(QString::number(ssaEquip->maxHp));
    if (ssaEquip->maxMp > 0)
        ui->ssaMp->setText(QString::number(ssaEquip->maxMp));

    if (energyEquip->maxHp > 0)
        ui->energyRingHp->setText(QString::number(energyEquip->maxHp));
    if (energyEquip->minMp > 0)
        ui->energyRingMp->setText(QString::number(energyEquip->minMp));

    if (mightEquip->maxHp > 0)
        ui->mightRingHp->setText(QString::number(mightEquip->maxHp));
    if (mightEquip->maxMp > 0)
        ui->mightRingMp->setText(QString::number(mightEquip->maxMp));

    if (defaultAmuletEquip->itemId > 0)
        ui->defaultAmuletInput->setText(QString::number(defaultAmuletEquip->itemId));
    if (defaultRingEquip->itemId > 0)
        ui->defaultRingInput->setText(QString::number(defaultRingEquip->itemId));

    // Mana Train

    if (manaTrainSpell->spell != nullptr)
        ui->lineEdit->setText(QString::fromStdString(manaTrainSpell->spell->words));
    ui->checkBox_5->setChecked(manaTrainSpell->enabled);

    // General
    ui->checkBox->setChecked(scriptConfig->getToolsAntiIdle());
    ui->checkBox_2->setChecked(scriptConfig->getToolsHoldPosition());
    if (scriptConfig->getToolsEatFoodId() > 0)
        ui->lineEdit_2->setText(QString::number(scriptConfig->getToolsEatFoodId()));
    ui->checkBox_3->setChecked(scriptConfig->getToolsEatFood());
    if (scriptConfig->getToolsAutoBuffItemId() > 0)
        ui->lineEdit_3->setText(QString::number(scriptConfig->getToolsAutoBuffItemId()));
    ui->checkBox_4->setChecked(scriptConfig->getToolsAutoBuff());

    updateReadInventory();
}

void ToolsTab::on_antiParalyzeSpellInput_editingFinished()
{
    ActionRule *rule = scriptConfig->getToolsRule("antiParalyzeSpell");
    rule->spell = Globals::getSpell(ui->antiParalyzeSpellInput->text().toStdString());
    rule->isDefaultValue = false;

    rule->enabled = rule->spell != nullptr;
}


void ToolsTab::on_hasteSpellInput_editingFinished()
{
    ActionRule *rule = scriptConfig->getToolsRule("hasteSpell");
    rule->spell = Globals::getSpell(ui->hasteSpellInput->text().toStdString());
    rule->isDefaultValue = false;

    rule->enabled = rule->spell != nullptr;
}


void ToolsTab::on_defaultAmuletInput_editingFinished()
{
    ActionRule *rule = scriptConfig->getToolsRule("defaultAmuletEquip");
    rule->itemId = ui->defaultAmuletInput->text().toInt();
    rule->isDefaultValue = false;
    rule->enabled = rule->itemId > 100;
    updateReadInventory();
}


void ToolsTab::on_defaultRingInput_editingFinished()
{
    ActionRule *rule = scriptConfig->getToolsRule("defaultRingEquip");
    rule->itemId = ui->defaultRingInput->text().toInt();
    rule->isDefaultValue = false;
    rule->enabled = rule->itemId > 100;
    updateReadInventory();
}


void ToolsTab::on_defaultAmuletRefresh_clicked()
{
    std::map<InventorySlot, Objects::InventoryItem*> inventoryItems = Objects::Client::getInventoryItems();
    if (inventoryItems.find(InventorySlot::InventorySlotNecklace) != inventoryItems.end())
        ui->defaultAmuletInput->setText(QString::number(inventoryItems[InventorySlot::InventorySlotNecklace]->getId()));
    else
        ui->defaultAmuletInput->setText(QString::number(0));

    on_defaultAmuletInput_editingFinished();

    for (std::pair<InventorySlot, Objects::InventoryItem*> item : inventoryItems)
        delete item.second;
}


void ToolsTab::on_defaultRingRefresh_clicked()
{
    std::map<InventorySlot, Objects::InventoryItem*> inventoryItems = Objects::Client::getInventoryItems();
    if (inventoryItems.find(InventorySlot::InventorySlotRing) != inventoryItems.end())
        ui->defaultRingInput->setText(QString::number(inventoryItems[InventorySlot::InventorySlotRing]->getId()));
    else
        ui->defaultRingInput->setText(QString::number(0));

    on_defaultRingInput_editingFinished();

    for (std::pair<InventorySlot, Objects::InventoryItem*> item : inventoryItems)
        delete item.second;
}


void ToolsTab::on_checkBox_stateChanged(int arg1)
{
    scriptConfig->setToolsAntiIdle(arg1);
}


void ToolsTab::on_checkBox_2_stateChanged(int arg1)
{
    scriptConfig->setToolsHoldPosition(arg1);
    scriptConfig->setToolsHoldPositionPos(Objects::Client::getPlayerCreature(Objects::Client::getDataPointer())->getPosition());
}


void ToolsTab::on_checkBox_3_stateChanged(int arg1)
{
    scriptConfig->setToolsEatFood(ui->lineEdit_2->text().toInt() > 0 && arg1);
}




void ToolsTab::on_checkBox_5_stateChanged(int arg1)
{
    ActionRule *rule = scriptConfig->getToolsRule("manaTrain");
    rule->isDefaultValue = false;

    rule->enabled = ui->checkBox_5->isChecked() && rule->spell != nullptr;
}


void ToolsTab::on_lineEdit_editingFinished()
{
    ActionRule *rule = scriptConfig->getToolsRule("manaTrain");
    rule->spell = Globals::getSpell(ui->lineEdit->text().toStdString());
    rule->isDefaultValue = false;

    rule->enabled = ui->checkBox_5->isChecked() && rule->spell != nullptr;
}


void ToolsTab::on_lineEdit_2_editingFinished()
{
    scriptConfig->setToolsEatFood(ui->lineEdit_2->text().toInt() > 0 && ui->checkBox_3->isChecked());
    scriptConfig->setToolsEatFoodId(ui->lineEdit_2->text().toInt());
}


void ToolsTab::on_checkBox_4_stateChanged(int arg1)
{
    scriptConfig->setToolsAutoBuff(ui->lineEdit_3->text().toInt() > 0 && arg1);
}


void ToolsTab::on_lineEdit_3_editingFinished()
{
    scriptConfig->setToolsAutoBuff(ui->lineEdit_3->text().toInt() > 0 && ui->checkBox_4->isChecked());
    scriptConfig->setToolsAutoBuffItemId(ui->lineEdit_3->text().toInt());
}

