#include "updater.h"
#include "healer.h"
#include "partyhunt.h"
#include "qapplication.h"
#include "qeventloop.h"
#include "../Objects/battlelist.h"
#include "../Objects/client.h"
#include "../Objects/game.h"
#include "../Util/kzhelper.h"
#include "pvptools.h"
#include "tools.h"

#include <wininet.h>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <openssl/evp.h>
#include <QMessageAuthenticationCode>
#include <QObject>
#include <QNetworkReply>

#include <iostream>

using namespace Threads;

Updater::Updater()
{
    scriptConfig = Globals::getScriptConfig();


}

Updater::~Updater()
{
    Stop();
}

void Updater::Start()
{
    if (m_threadStatus == false)
    {
        m_threadStatus = true;
        m_updaterThread = std::thread(&Threads::Updater::m_threadFunc, this);
        m_actionThread = std::thread(&Threads::Updater::m_actionThreadFunc, this);
    }
}

void Updater::Stop()
{
    m_threadStatus = false;
}

void Threads::Updater::m_threadFunc()
{
    while (m_threadStatus)
    {
        // Authentication
        try
        {
            if (Globals::getUserId() < 0 || Globals::getUsername().isEmpty() || Globals::getPassword().isEmpty() || Globals::getUserSignature().isEmpty() || Globals::getAuthErrorCount() >= 10)
            {
                QApplication::quit();
                return;
            }
            else if (Globals::getAuthTickCount() == 0 || (Globals::getAuthErrorCount() > 0 && Globals::getAuthTickCount() % 600 == 0) || Globals::getAuthTickCount() % 3000 == 0)
            {
                QUrl url("https://tibia.kzsoft.com.br/authenticate.php");

                QByteArray postData;
                postData.append("email=").append(QUrl::toPercentEncoding(Globals::getEmail()));
                postData.append("&token=").append(QUrl::toPercentEncoding(Globals::getUserSignature()));
                postData.append("&product_id=").append(QUrl::toPercentEncoding(QString::number(4)));


                QNetworkAccessManager *manager = new QNetworkAccessManager();
                QNetworkRequest request(url);

                request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

                QNetworkReply *reply = manager->post(request, postData);

                // WAIT RESPONSE
                QEventLoop loop;                
                loop.connect(manager, SIGNAL(finished(QNetworkReply*)), SLOT(quit()));
                loop.exec();


                // CHECK
                if (reply->error() != QNetworkReply::NoError) {
                    throw (1);
                }

                QByteArray response = reply->readAll();
                //std::cout << "Response: " << response.toStdString() << std::endl;

                std::vector<QByteArray> keys = {
                    "7p9Fj6Aq0Wt4vRg3Dn2L",
                    "3zX5dMv7Hb1Jk9Pc8NfR",
                    "2wG4yEh5Sj3Vt6Ub1QxP",
                    "9lK6nTf3Xj8Hc7Zm5VbR",
                    "1bN4vGh2Dm7Kt9Qc3XwS",
                    "8rZ7lBt5Ym3Fk2Nj1HvG",
                    "4wT3rSf2Jl6Bn1Qc9VgH",
                    "5nH2jMf6Xb3Dv1Rg7KtP",
                    "6q0Wt4Yh8Jc7Vb9Nm2Lp",
                    "2fD5gR7nH1kT3jM4bVx"
                };

                // Verificar a assinatura digital do token
                QByteArray privateKey = keys[(Globals::getAuthSuccessCount() + 1) % 10];

                // Converter payload em QByteArray
                QByteArray input = Globals::getUserSignature().toUtf8();
                QByteArray calculatedSignature = QMessageAuthenticationCode::hash(input, privateKey, QCryptographicHash::Sha256).toHex();

                //std::cout << "Signature: " << calculatedSignature.toStdString() << " - " << privateKey.toStdString() << " - " << input.toStdString() << std::endl;

                if (response != calculatedSignature) {
                    throw (3);
                }

                //std::cout << "Autenticação válida." << std::endl;

                Globals::setAuthErrorCount(0);
                Globals::increaseAuthSuccessCount();
            }
        }
        catch (...)
        {
            DWORD lpresult;
            BOOL winresult = InternetGetConnectedState(&lpresult,0);
            bool connected = winresult == 1 ? true : false;

            if (connected)
            {
                //std::cout << "Error na autenticação" << std::endl;
                Globals::increaseAuthErrorCount();
            }
            else
            {
                //std::cout << "Autenticação: Sem Conexão" << std::endl;
            }
        }
        Globals::increaseAuthTickCount();

        // On Focus/Unfocus Bot and Client
        HWND foregroundWindow = GetForegroundWindow();
        if (foregroundWindow != m_lastForegroundWindow)
        {
            m_lastForegroundWindow = foregroundWindow;
            emit hasFocus(foregroundWindow);
        }

        // Pause/Unpause Area
        bool canUseHotkeys = Globals::getAuthTickCount() > m_lastHotkeyTick;
        if (GetAsyncKeyState(VK_PAUSE) & 0x0001 && canUseHotkeys)
        {
            emit changeStatus("general");
            Beep(1000, 500);
            m_lastHotkeyTick = Globals::getAuthTickCount() + 10;
        }
        if (GetAsyncKeyState(VK_ESCAPE) & 0x0001)
        {
            Game::setLastTargetId(0);
        }

        // ScriptConfig Hotkeys
        if (GetAsyncKeyState(0x31) & GetAsyncKeyState(VK_CONTROL) & 0x8000 && canUseHotkeys)
        {
            emit loadSetting("default.xml");
            m_lastHotkeyTick = Globals::getAuthTickCount() + 10;
        }
        if (GetAsyncKeyState(0x32) & GetAsyncKeyState(VK_CONTROL) & 0x8000 && canUseHotkeys)
        {
            emit loadSetting("tank.xml");
            m_lastHotkeyTick = Globals::getAuthTickCount() + 10;
        }
        if (GetAsyncKeyState(0x33) & GetAsyncKeyState(VK_CONTROL) & 0x8000 && canUseHotkeys)
        {
            emit loadSetting("swap.xml");
            m_lastHotkeyTick = Globals::getAuthTickCount() + 10;
        }
        if (GetAsyncKeyState(0x34) & GetAsyncKeyState(VK_CONTROL) & 0x8000 && canUseHotkeys)
        {
            emit loadSetting("hunt.xml");
            m_lastHotkeyTick = Globals::getAuthTickCount() + 10;
        }
        if (GetAsyncKeyState(0x35) & GetAsyncKeyState(VK_CONTROL) & 0x8000 && canUseHotkeys)
        {
            emit loadSetting("boss.xml");
            m_lastHotkeyTick = Globals::getAuthTickCount() + 10;
        }

        // Updater
        if (scriptConfig->getGeneralStatus())
        {
            try
            {
                if (!Globals::isSet)
                    throw("Client not set.");

                if (Objects::Client::getEquipmentPoint() == NULL)
                    Objects::Client::updateEquipmentPoint();

                if (Objects::Client::getGameScreenPlayerPoint() == nullptr)
                    Objects::Client::updateGameScreenRect();

                Objects::Game::Update();
            }
            catch (...)
            {}
        }

        if (scriptConfig->getGeneralStatus())
        {
            if (scriptConfig->getHealerStatus())
            {
                Threads::Healer* healerThread = new Threads::Healer();
                healerThread->Start();
            }
            if (scriptConfig->getToolsStatus())
            {
                Threads::Tools* toolsThread = new Threads::Tools();
                toolsThread->Start();
            }
            if (scriptConfig->getPvPToolslsStatus())
            {
                Threads::PvPTools* pvpToolsThread = new Threads::PvPTools();
                pvpToolsThread->Start();
            }
            if (scriptConfig->getPartyHuntStatus())
            {
                Threads::PartyHunt* partyHuntThread = new Threads::PartyHunt();
                partyHuntThread->Start();
            }
        }

        Sleep(100);
    }

    m_updaterThread.detach();
    m_threadStatus = false;
}

void Threads::Updater::m_actionThreadFunc()
{
    while (m_threadStatus)
    {
        try
        {
            if (Globals::getInputs().size() == 0)
            {
                Sleep(10);
                continue;
            }

            Objects::KeyBinding* botKey = nullptr;
            std::string botKeyText = "";
            bool sentInput = false;
            bool lastInputTypeWasText = true;

            for(auto it = Globals::getInputs().begin(); it != Globals::getInputs().end(); it = Globals::getInputs().begin()){
                try
                {
                    Input* input = *it;
                    if (!input->canRepeat && Game::getGameTime() != input->gameTime)
                    {
                        it = std::remove(Globals::getInputs().begin(), Globals::getInputs().end(), input);
                        Globals::getInputs().erase(it, Globals::getInputs().end());
                        continue;
                    }

                    botKey = Objects::Client::getKeyBindingByKey(VK_F13);
                    if (botKey == nullptr)
                        break;

                    botKeyText = botKey->getText();
                    if (botKeyText.size() < 50)
                        break;

                    bool editedHotkey = false;

                    if (input->requiresRealTarget)
                        Objects::Client::Target(Game::getDataPointer(), input->position);
                    else if (input->targetId)
                        Objects::Battlelist::setTargetId(Game::getDataPointer(), input->targetId);

                    if (input->text.length() > 0)
                    {
                        if (!lastInputTypeWasText)
                            botKey->setId(0);

                        std::string outputText = "#s " + input->text;
                        outputText.append(50 - outputText.length(), ' ');

                        botKey->setText(outputText);
                        botKey->setSendAutomatically(true);
                        lastInputTypeWasText = true;
                        sentInput = true;
                        editedHotkey = true;

                        for (int i = 0; i < 50; i++)
                        {
                            if (botKey->getText() == outputText)
                                continue;

                            Sleep(1);
                        }
                    }
                    else if (input->itemId > 0)
                    {
                        if (lastInputTypeWasText)
                        {
                            botKey->setText("");
                            //botKey->setSendAutomatically(false);
                        }

                        botKey->setUseType(input->itemUseType);
                        botKey->setId(input->itemId);
                        sentInput = true;
                        editedHotkey = true;

                        for (int i = 0; i < 50; i++)
                        {
                            if (botKey->getId() == input->itemId)
                                continue;

                            Sleep(1);
                        }
                    }

                    if (editedHotkey)
                    {
                        Util::KzHelper::SendKey(VK_F13);
                        Sleep(1);

                        if (input->usesCrosshair)
                        {
                            Util::KzHelper::LeftClick(Client::getSqmPoint(Game::getDataPointer(), input->position));
                            Sleep(1);
                        }
                    }

                    it = std::remove(Globals::getInputs().begin(), Globals::getInputs().end(), input);
                    Globals::getInputs().erase(it, Globals::getInputs().end());
                    //it = Globals::getInputs().begin();
                }
                catch (...)
                {}
            }
            if (sentInput && botKey != nullptr && botKey->getText().size() >= 50)
            {
                botKey->setText("                                                  ");
                //botKey->setSendAutomatically(false);
                if (!lastInputTypeWasText)
                    botKey->setId(0);
            }
        }
        catch (...)
        {

        }

    }

    m_actionThread.detach();
}
