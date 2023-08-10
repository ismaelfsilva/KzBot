#include <string>
#include <iostream>
#include <windows.h>
#include <wtsapi32.h>
#include <minwindef.h>
#include <sstream>
#include <filesystem>

#include <windows.data.json.h>
#include <fstream>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QVariantMap>
#include <QByteArray>

#include "clientmanager.h"
#include "ui_clientmanager.h"
#include "../Util/kzhelper.h"
#include "../Settings/globals.h"
#include "../Addresses/Versions/versions.h"
#include "../Objects/client.h"

#include <QMessageBox>
#include "confighelper.h"

#pragma comment(lib, "Wtsapi32.lib")


ClientManager::ClientManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientManager)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window);

    QTableWidget *tableWidget = ui->tableWidget;
    tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Interactive);
    tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Interactive);
    tableWidget->verticalHeader()->setVisible(false);

    RefreshClients();

    if (ui->tableWidget->rowCount() == 1)
        ui->tableWidget->selectRow(0);

    this->setFocus();

}

ClientManager::~ClientManager()
{
    delete ui;
}

void ClientManager::CheckFirstClient()
{
    if (!Globals::isSet && ui->tableWidget->rowCount() == 1)
    {
        ui->tableWidget->selectRow(0);
        ui->pushButton_2->click();
    }
}

void ClientManager::RefreshClients()
{
    QTableWidget *tableWidget = ui->tableWidget;
    tableWidget->setRowCount(0);

    std::vector<HWND> processes = Util::KzHelper::getWindowsByTitle("Tibia - ", true);

    for (const HWND &hwnd : processes)
    {
        int rowCount = tableWidget->rowCount();
        tableWidget->insertRow(rowCount);

        DWORD idInt;
        GetWindowThreadProcessId(hwnd, &idInt);

        std::string idString = std::to_string(idInt);
        std::string processName = Util::KzHelper::getWindowTitle(hwnd);
        std::filesystem::path path = Util::KzHelper::getWindowPath(hwnd).parent_path().parent_path();

        std::string filePath = path.string();
        filePath.append("\\package.json");

        QFile file;
        file.setFileName(QString::fromLatin1(filePath));
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QByteArray val = file.readAll();
        file.close();
        QJsonDocument doc = QJsonDocument::fromJson(val);
        QJsonObject jObject = doc.object();
        QVariantMap mainMap = jObject.toVariantMap();


        QTableWidgetItem *idItem = new QTableWidgetItem(QString::fromStdString(idString));
        QTableWidgetItem *nameItem = new QTableWidgetItem(QString::fromStdString(processName.substr(8)));
        QTableWidgetItem *versionItem = new QTableWidgetItem(mainMap["version"].toString());

        idItem->setTextAlignment(Qt::AlignCenter);
        nameItem->setTextAlignment(Qt::AlignCenter);
        versionItem->setTextAlignment(Qt::AlignCenter);

        tableWidget->setItem(rowCount, 0, idItem);
        tableWidget->setItem(rowCount, 1, nameItem);
        tableWidget->setItem(rowCount, 2, versionItem);
    }

}

void ClientManager::on_pushButton_clicked()
{
    ClientManager::RefreshClients();
}


void ClientManager::on_pushButton_3_clicked()
{
    this->close();
}


void ClientManager::on_pushButton_2_clicked()
{
    QTableWidget *tableWidget = ui->tableWidget;

    QList<QTableWidgetItem *> selectedItems = tableWidget->selectedItems();

    if (selectedItems.length() != 3)
        return;

    if (!Addresses::Versions::isSupportedVersion(selectedItems[2]->text().toStdString()))
        return;

    DWORD pId = selectedItems[0]->text().toInt();
    HWND hWnd = Util::KzHelper::getWindowById(pId);


    Globals::setHWnd(hWnd);
    Globals::setProcessId(pId);
    Globals::setHandle(OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId));
    Globals::setBaseAddress(Util::KzHelper::GetProcessBaseAddress(pId));
    Addresses::Versions::setVersion(selectedItems[2]->text().toStdString());
    Objects::Client::updateEquipmentPoint();
    Objects::Client::updateGameScreenRect();

    Objects::KeyBinding* keyBinding = Objects::Client::getKeyBindingByKey(VK_F13);
    if (keyBinding == nullptr)
    {
        ConfigHelper* configHelper = new ConfigHelper();
        configHelper->show();
        configHelper->setFocus();
    }

    //Objects::Client::updateHotkeys();
    Globals::isSet = true;

    this->close();
}


void ClientManager::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{
    ClientManager::on_pushButton_2_clicked();
}

