#include "mainwindow.h"
#include "clientmanager.h"
#include "confighelper.h"
#include "healer.h"
#include "partyhunt.h"
#include "pvptools.h"
#include "qapplication.h"
#include "ui_configchooser.h"
#include "toolstab.h"
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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qRegisterMetaType<HWND>("HWND");
    Globals::UpdateSpells();

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
                    Globals::getScriptConfig()->setGeneralStatus(arg1);

                delete keyBinding;
            }
            else
                generalStatusCheckBox->click();
        }
        else
            Globals::getScriptConfig()->setGeneralStatus(arg1);
    });
    ui->tabWidget->setCornerWidget(generalStatusCheckBox);


    // Healer
    healer = new Healer(this);
    int healerTabId = ui->tabWidget->addTab(healer, healer->windowTitle());
    healerCheckBox = new QCheckBox(this);
    connect(healerCheckBox, &QCheckBox::stateChanged, this, [](int arg1) {
        Globals::getScriptConfig()->setHealerStatus(arg1);
    });
    tabBar->setTabButton(healerTabId, QTabBar::LeftSide, healerCheckBox);

    // Tools
    tools = new ToolsTab(this);
    int toolsTabId = ui->tabWidget->addTab(tools, tools->windowTitle());
    toolsCheckBox = new QCheckBox(this);
    connect(toolsCheckBox, &QCheckBox::stateChanged, this, [](int arg1) {
        Globals::getScriptConfig()->setToolsStatus(arg1);
    });
    tabBar->setTabButton(toolsTabId, QTabBar::LeftSide, toolsCheckBox);

    // PvP Tools
    pvpTools = new PvpTools(this);
    int pvpToolsTabId = ui->tabWidget->addTab(pvpTools, pvpTools->windowTitle());
    pvpToolsCheckBox = new QCheckBox(this);
    connect(pvpToolsCheckBox, &QCheckBox::stateChanged, this, [](int arg1) {
        Globals::getScriptConfig()->setPvPToolsStatus(arg1);
    });
    tabBar->setTabButton(pvpToolsTabId, QTabBar::LeftSide, pvpToolsCheckBox);

    // Party Hunt
    partyHunt = new PartyHunt(this);
    int partyHuntTabId = ui->tabWidget->addTab(partyHunt, partyHunt->windowTitle());
    partyHuntCheckBox = new QCheckBox(this);
    connect(partyHuntCheckBox, &QCheckBox::stateChanged, this, [](int arg1) {
        Globals::getScriptConfig()->setPartyHuntStatus(arg1);
    });
    tabBar->setTabButton(partyHuntTabId, QTabBar::LeftSide, partyHuntCheckBox);

    // Threading Area
    this->updaterThread = new Threads::Updater();











    configChooser = new ConfigChooser();
    connect(updaterThread, &Threads::Updater::hasFocus, this, &MainWindow::onTibiaClientFocusChange);
    connect(configChooser, &ConfigChooser::loadSetting, this, &MainWindow::loadSettingSignal);
    connect(updaterThread, &Threads::Updater::loadSetting, this, &MainWindow::loadSettingSignal);
    connect(updaterThread, &Threads::Updater::changeStatus, this, &MainWindow::changeStatusSignal);




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
    generalStatusCheckBox->click();
}

void MainWindow::loadSettingSignal(QString fileName)
{
    bool loadSuccess = LoadSetting("Settings/" + fileName);
    if (!loadSuccess)
    {
        QApplication::beep();
        return;
    }

    configChooser->_lastFileName = fileName;

    if (fileName == "default.xml")
        configChooser->ui->pushButton->setChecked(true);
    else if (fileName == "tank.xml")
        configChooser->ui->pushButton_2->setChecked(true);
    else if (fileName == "swap.xml")
        configChooser->ui->pushButton_3->setChecked(true);
    else if (fileName == "hunt.xml")
        configChooser->ui->pushButton_4->setChecked(true);
    else if (fileName == "boss.xml")
        configChooser->ui->pushButton_5->setChecked(true);

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

void MainWindow::on_actionShow_Config_Selector_toggled(bool arg1)
{
    if (arg1)
        configChooser->show();
    else
        configChooser->hide();
}

void MainWindow::onTibiaClientFocusChange(const HWND& focusedHWnd)
{
    bool hasFocus = focusedHWnd == Globals::getHWnd() || focusedHWnd == (HWND)this->winId() || focusedHWnd == (HWND)configChooser->winId();
    if (configChooser->isHidden() && hasFocus && ui->actionShow_Config_Selector->isChecked())
        configChooser->show();
    else if (!configChooser->isHidden() && !hasFocus)
        configChooser->hide();
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

    configChooser->_lastFileName = fileName;

    if (fileName.isEmpty())
        return;
    else
        LoadSetting(fileName, true);
}

void MainWindow::on_actionOther_2_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Script"), "",
                                                    tr("Xml File (*.xml);;All Files (*)"));

    configChooser->_lastFileName = fileName;

    if (fileName.isEmpty())
        return;
    else
        SaveSetting(fileName, true);
}





void MainWindow::on_actionInitial_Config_triggered()
{
    ConfigHelper* configHelper = new ConfigHelper(this);
    configHelper->show();
}

