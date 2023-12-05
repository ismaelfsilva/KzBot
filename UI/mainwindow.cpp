#include "mainwindow.h"
#include "clientmanager.h"
#include "confighelper.h"
#include "healer.h"
#include "partyhunt.h"
#include "pvptools.h"
#include "qapplication.h"
#include "qsettings.h"
#include "ui_configchooser.h"
#include "toolstab.h"
#include "ui_hudstatuses.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <iostream>
#include "../Settings/globals.h"
#include "../Threads/updater.h"
#include "../Util/kzhelper.h"
#include <QFile>
#include <QMessageBox>
#include <QXmlStreamWriter>
#include <ui_healer.h>
#include <chrono>
#include <QFileDialog>
#include "../Objects/keybinding.h"
#include "../Objects/client.h"
#include "../Objects/battlelist.h"
#include "../Objects/game.h"
#include "../Objects/chat.h"
#include "../Addresses/client.h"
#include "../Addresses/inventory.h"
#include "../Addresses/inventoryitem.h"
#include "ui_partyhunt.h"
#include "ui_pvptools.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qRegisterMetaType<HWND>("HWND");
    Globals::UpdateSpells();
    hudStatuses = new HUDStatuses();
    hudPvP = new HUDPvP();

    QTabBar *tabBar = ui->tabWidget->tabBar();
    generalStatusCheckBox = new QCheckBox("Status", this);
    connect(generalStatusCheckBox, &QCheckBox::clicked, this, [this](bool arg1) {
        if (arg1)
        {
            if (Globals::isSet)
            {
                Objects::KeyBinding* keyBinding = Objects::Client::getKeyBindingByKey(VK_F13);
                if (keyBinding == nullptr || keyBinding->getText().length() < 50)
                {
                    generalStatusCheckBox->click();
                    ConfigHelper* configHelper = new ConfigHelper();
                    configHelper->show();
                    configHelper->setFocus();
                }
                else
                {
                    Globals::getScriptConfig()->setGeneralStatus(arg1);
                    hudStatuses->ui->generalStatus->setChecked(arg1);
                }

                delete keyBinding;
            }
            else
                generalStatusCheckBox->click();
        }
        else
        {
            Globals::getScriptConfig()->setGeneralStatus(arg1);
            hudStatuses->ui->generalStatus->setChecked(arg1);
        }
    });
    ui->tabWidget->setCornerWidget(generalStatusCheckBox);


    // Healer
    healer = new Healer(this);
    int healerTabId = ui->tabWidget->addTab(healer, healer->windowTitle());
    healerCheckBox = new QCheckBox(this);
    connect(healerCheckBox, &QCheckBox::stateChanged, this, [this](int arg1) {
        Globals::getScriptConfig()->setHealerStatus(arg1);
        hudStatuses->ui->healerStatus->setChecked(arg1);
    });
    tabBar->setTabButton(healerTabId, QTabBar::LeftSide, healerCheckBox);

    // Tools
    tools = new ToolsTab(this);
    int toolsTabId = ui->tabWidget->addTab(tools, tools->windowTitle());
    toolsCheckBox = new QCheckBox(this);
    connect(toolsCheckBox, &QCheckBox::stateChanged, this, [this](int arg1) {
        Globals::getScriptConfig()->setToolsStatus(arg1);
        hudStatuses->ui->toolsStatus->setChecked(arg1);
    });
    tabBar->setTabButton(toolsTabId, QTabBar::LeftSide, toolsCheckBox);

    // PvP Tools
    pvpTools = new PvpTools(this);
    int pvpToolsTabId = ui->tabWidget->addTab(pvpTools, pvpTools->windowTitle());
    pvpToolsCheckBox = new QCheckBox(this);
    connect(pvpToolsCheckBox, &QCheckBox::stateChanged, this, [this](int arg1) {
        Globals::getScriptConfig()->setPvPToolsStatus(arg1);
        hudStatuses->ui->pvpStatus->setChecked(arg1);
    });
    tabBar->setTabButton(pvpToolsTabId, QTabBar::LeftSide, pvpToolsCheckBox);

    // Party Hunt
    partyHunt = new PartyHunt(this);
    int partyHuntTabId = ui->tabWidget->addTab(partyHunt, partyHunt->windowTitle());
    partyHuntCheckBox = new QCheckBox(this);
    connect(partyHuntCheckBox, &QCheckBox::stateChanged, this, [this](int arg1) {
        Globals::getScriptConfig()->setPartyHuntStatus(arg1);
        hudStatuses->ui->targetingStatus->setChecked(arg1);
    });
    tabBar->setTabButton(partyHuntTabId, QTabBar::LeftSide, partyHuntCheckBox);

    // Threading Area
    this->updaterThread = new Threads::Updater();



    configChooser = new ConfigChooser();

    connect(hudStatuses, &HUDStatuses::changeStatus, this, &MainWindow::changeStatusSignal);

    connect(updaterThread, &Threads::Updater::hasFocus, this, &MainWindow::onTibiaClientFocusChange);
    connect(configChooser, &ConfigChooser::loadSetting, this, &MainWindow::loadSettingSignal);
    connect(updaterThread, &Threads::Updater::loadSetting, this, &MainWindow::loadSettingSignal);
    connect(updaterThread, &Threads::Updater::changeStatus, this, &MainWindow::changeStatusSignal);



    hudStatuses->ui->chatNaviStatus->setChecked(Globals::getScriptConfig()->getPvPChatNaviStatus());

    LoadSetting("Settings/default.xml");
}

MainWindow::~MainWindow()
{
    delete ui;
    updaterThread->Stop();
    Globals::closeHandle();
}


void MainWindow::on_Form_StartUp()
{
    this->show();

    ClientManager *clientManager = new ClientManager(this);
    clientManager->show();
    clientManager->CheckFirstClient();

    updaterThread->Start();
}

void MainWindow::on_actionSelect_Client_triggered()
{
    ClientManager *clientManager = new ClientManager(this);
    clientManager->show();
}

void MainWindow::on_actionDefault_triggered()
{
    SaveSetting("Settings/default.xml", true);
}

void MainWindow::SaveSetting(QString fileName, bool errorMessage)
{
    QFile file(fileName);

    if (file.exists() && errorMessage) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("Confirm"), tr("File already exists. Do you want to overwrite?"),
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::No) {
            return;
        }
    }

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QXmlStreamWriter writer(&file);
        writer.setAutoFormatting(true);
        writer.writeStartDocument();
        Globals::getScriptConfig()->Serialize(writer);
        writer.writeEndDocument();
        file.close();
    }
}


void MainWindow::on_actionDefault_2_triggered()
{
    LoadSetting("Settings/default.xml", true);
}

void MainWindow::changeStatusSignal(const QString& statusName)
{
    if (statusName == "generalStatus")
    {
        generalStatusCheckBox->click();
        Beep(1000, 500);
    }




    else if (statusName == "healerStatus")
        healerCheckBox->click();
    else if (statusName == "exanaVitaStatus")
        Globals::getScriptConfig()->getHealRule("exanaVitaSpell")->enabled = !Globals::getScriptConfig()->getHealRule("exanaVitaSpell")->enabled;
    else if (statusName == "healFriendStatus")
    {
        Globals::getScriptConfig()->getHealRule("strongHealFriend")->enabled = !Globals::getScriptConfig()->getHealRule("strongHealFriend")->enabled;
        Globals::getScriptConfig()->getHealRule("healFriend")->enabled = !Globals::getScriptConfig()->getHealRule("healFriend")->enabled;
        Globals::getScriptConfig()->getHealRule("uhRune")->enabled = !Globals::getScriptConfig()->getHealRule("uhRune")->enabled;
    }



    else if (statusName == "toolsStatus")
        toolsCheckBox->click();
    else if (statusName == "autoSSAStatus")
        Globals::getScriptConfig()->getToolsRule("stoneSkinAmuletEquip")->enabled = !Globals::getScriptConfig()->getToolsRule("stoneSkinAmuletEquip")->enabled;
    else if (statusName == "autoMRStatus")
        Globals::getScriptConfig()->getToolsRule("mightRingEquip")->enabled = !Globals::getScriptConfig()->getToolsRule("mightRingEquip")->enabled;






    else if (statusName == "pvpStatus")
        pvpToolsCheckBox->click();
    else if (statusName == "gotoTargetStatus")
        pvpTools->ui->checkBox_2->click();
    else if (statusName == "comboUEStatus")
        pvpTools->ui->checkBox_10->click();
    else if (statusName == "chatNaviStatus")
    {
        Game::m_lastSeenChatMessage = 0;
        Globals::getScriptConfig()->setPvPChatNaviStatus(!Globals::getScriptConfig()->getPvPChatNaviStatus());
    }



    else if (statusName == "targetingStatus")
        partyHuntCheckBox->click();
    else if (statusName == "autoTargetStatus")
        partyHunt->ui->autoTargetStatus->click();

}

void MainWindow::loadSettingSignal(QString fileName)
{
    QString finalFileName = fileName;
    if (finalFileName.endsWith("Name"))
        finalFileName = finalFileName.replace("Name", ".xml");

    bool loadSuccess = LoadSetting("Settings/" + finalFileName);
    if (!loadSuccess)
    {
        QApplication::beep();
        return;
    }
    else
    {
        if (finalFileName == "default.xml")
            configChooser->ui->defaultName->setChecked(true);
        else if (finalFileName == "tank.xml")
            configChooser->ui->tankName->setChecked(true);
        else if (finalFileName == "swap.xml")
            configChooser->ui->swapName->setChecked(true);
        else if (finalFileName == "hunt.xml")
            configChooser->ui->huntName->setChecked(true);
        else if (finalFileName == "boss.xml")
            configChooser->ui->bossName->setChecked(true);
    }


    Beep(1000, 500);
}

bool MainWindow::LoadSetting(QString fileName, bool errorMessage)
{
    QFile file(fileName);
    if (!file.exists())
    {
        if (errorMessage)
            QMessageBox::critical(this, tr("File is Missing"), "System couldn't find file " + fileName + " in the Settings folder.");
        return false;
    }

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QXmlStreamReader reader(&file);

        healer->ResetUI();
        tools->ResetUi();
        partyHunt->ResetUI();

        Globals::getScriptConfig()->Deserialize(reader);
        file.close();

        healer->UpdateUI();
        tools->UpdateUi();
        partyHunt->UpdateUI();
        pvpTools->UpdateUi();
        this->UpdateUi();

        hudStatuses->ui->chatNaviStatus->setChecked(Globals::getScriptConfig()->getPvPChatNaviStatus());
        return true;
    }
    return false;
}

void MainWindow::UpdateUi()
{
    healerCheckBox->setChecked(Globals::getScriptConfig()->getHealerStatus());
    toolsCheckBox->setChecked(Globals::getScriptConfig()->getToolsStatus());
    pvpToolsCheckBox->setChecked(Globals::getScriptConfig()->getPvPToolslsStatus());
    partyHuntCheckBox->setChecked(Globals::getScriptConfig()->getPartyHuntStatus());

    generalStatusCheckBox->setChecked(Globals::getScriptConfig()->getGeneralStatus());
}


void MainWindow::onTibiaClientFocusChange(const HWND& focusedHWnd)
{
    bool hasFocus = focusedHWnd == Globals::getHWnd() || focusedHWnd == (HWND)this->winId()  || focusedHWnd == (HWND)configChooser->winId()
                    || focusedHWnd == (HWND)hudStatuses->winId() || focusedHWnd == (HWND)hudPvP->winId();
    if (hasFocus)
    {
        if (configChooser->isHidden() && configChooser->_isVisible)
            configChooser->show();

        if (hudStatuses->isHidden() && hudStatuses->_isVisible)
            hudStatuses->show();

        if (hudPvP->isHidden() && hudPvP->_isVisible)
            hudPvP->show();
    }
    else if (!hasFocus)
    {
        if (!configChooser->isHidden())
            configChooser->hide();

        if (!hudStatuses->isHidden())
            hudStatuses->hide();

        if (!hudPvP->isHidden())
            hudPvP->hide();
    }
}

void MainWindow::on_actionTank_triggered()
{
    SaveSetting("Settings/tank.xml", true);
}


void MainWindow::on_actionTank_2_triggered()
{
    LoadSetting("Settings/tank.xml", true);
}


void MainWindow::on_actionSwap_triggered()
{
    SaveSetting("Settings/swap.xml", true);
}


void MainWindow::on_actionSwap_2_triggered()
{
    LoadSetting("Settings/swap.xml", true);
}


void MainWindow::on_actionHunt_triggered()
{
    SaveSetting("Settings/hunt.xml", true);
}


void MainWindow::on_actionHunt_2_triggered()
{
    LoadSetting("Settings/hunt.xml", true);
}


void MainWindow::on_actionBoss_triggered()
{
    SaveSetting("Settings/boss.xml", true);
}


void MainWindow::on_actionBoss_2_triggered()
{
    LoadSetting("Settings/boss.xml", true);
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionPress_Kz_Key_triggered()
{
    Util::KzHelper::SendKey(VK_F13);
}


void MainWindow::on_actionOther_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Load Script"), "",
                                                    tr("Xml File (*.xml);;All Files (*)"));


    if (fileName.isEmpty())
        return;
    else
    {
        configChooser->ui->otherName->setChecked(true);
        LoadSetting(fileName, true);
    }
}

void MainWindow::on_actionOther_2_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Script"), "",
                                                    tr("Xml File (*.xml);;All Files (*)"));

    if (fileName.isEmpty())
        return;
    else
    {
        configChooser->ui->otherName->setChecked(true);
        SaveSetting(fileName, true);
    }
}





void MainWindow::on_actionInitial_Config_triggered()
{
    ConfigHelper* configHelper = new ConfigHelper(this);
    configHelper->show();
}


void MainWindow::on_actionLogout_triggered()
{
    QSettings mySettings("KzSoft", "KzBot - Tibia");
    mySettings.setValue("remember", false);
    mySettings.setValue("email", NULL);
    mySettings.setValue("password", NULL);
    mySettings.setValue("loginauto", NULL);
    mySettings.sync();
    QApplication::quit();
}


void MainWindow::on_actionStatus_triggered()
{
    hudStatuses->_isVisible = true;
    hudStatuses->show();
}


void MainWindow::on_actionPvP_triggered()
{
    hudPvP->_isVisible = true;
    hudPvP->show();
}


void MainWindow::on_actionConfig_Selector_triggered()
{
    configChooser->_isVisible = true;
    configChooser->show();
}


void MainWindow::on_actionv0_1_10_0_triggered()
{
}

