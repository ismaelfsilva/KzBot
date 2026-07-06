#include "pvptools.h"
#include "mainwindow.h"
#include "qsettings.h"
#include "ui_hudstatuses.h"
#include "ui_pvptools.h"
#include "../Settings/globals.h"
#include "../Objects/game.h"
#include "../Util/kzhelper.h"

PvpTools::PvpTools(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PvpTools)
{
    ui->setupUi(this);

    Globals::getScriptConfig()->m_pvpOnComboUEActionA = new ComboRule("ComboUEA");
    Globals::getScriptConfig()->m_pvpOnComboUEActionB = new ComboRule("ComboUEB");

    Globals::getScriptConfig()->m_pvpOnComboAvatarActionA = new ComboRule("ComboAvatarA");
    Globals::getScriptConfig()->m_pvpOnComboAvatarActionB = new ComboRule("ComboAvatarB");

    Globals::getScriptConfig()->ComboRules.emplace_back(new ComboRule());
    Globals::getScriptConfig()->ComboRules.emplace_back(new ComboRule());
    Globals::getScriptConfig()->ComboRules.emplace_back(new ComboRule());


    ui->clearTileKey->setMaximumSequenceLength(1);
    ui->protSqmKey->setMaximumSequenceLength(1);
    ui->comboKey->setMaximumSequenceLength(1);

    ui->clearTileKey->setClearButtonEnabled(true);
    ui->protSqmKey->setClearButtonEnabled(true);
    ui->comboKey->setClearButtonEnabled(true);

    if(QLineEdit *lineEdit = ui->clearTileKey->findChild<QLineEdit*>("qt_keysequenceedit_lineedit")){
        lineEdit->setPlaceholderText("Key");
        lineEdit->setAlignment(Qt::AlignCenter);
    }

    if(QLineEdit *lineEdit = ui->protSqmKey->findChild<QLineEdit*>("qt_keysequenceedit_lineedit")){
        lineEdit->setPlaceholderText("Key");
        lineEdit->setAlignment(Qt::AlignCenter);
    }

    if(QLineEdit *lineEdit = ui->comboKey->findChild<QLineEdit*>("qt_keysequenceedit_lineedit")){
        lineEdit->setPlaceholderText("Key");
        lineEdit->setAlignment(Qt::AlignCenter);
    }

    QSettings mySettings("KzSoft", "KzBot - Tibia");
    mySettings.sync();
    ui->clearTileKey->setKeySequence(QKeySequence::fromString(mySettings.value("clearTileKey").toString()));
    ui->clearTileKey->editingFinished();

    ui->protSqmKey->setKeySequence(QKeySequence::fromString(mySettings.value("protSqmKey").toString()));
    ui->protSqmKey->editingFinished();


}

PvpTools::~PvpTools()
{
    delete ui;
}


bool PvpTools::nativeEvent(const QByteArray& eventType, void* message, qintptr* result)
{
    Q_UNUSED(eventType);
    Q_UNUSED(result);
    MSG* msg = static_cast<MSG*>(message);
    if (msg->message == WM_HOTKEY)
    {
        if (!Globals::isSet) // Client not set
            return false;

        if (GetForegroundWindow() != Globals::getHWnd() || !Globals::getScriptConfig()->getGeneralStatus() || !Globals::getScriptConfig()->getPvPToolslsStatus())
            return false;

        switch (msg->wParam)
        {
        case 101: // Flor
        {
            if (ui->protSqmStatus->isChecked())
            {
                POINT p;
                GetCursorPos(&p);
                ScreenToClient(GetForegroundWindow(), &p);
                Util::KzHelper::DragDrop(&Globals::getScriptConfig()->flowerSourcePoint, &p);
            }
            break;
        }
        case 102: // Clear
        {
            if (ui->clearTileStatus->isChecked())
            {
                POINT p;
                GetCursorPos(&p);
                ScreenToClient(GetForegroundWindow(), &p);
                Util::KzHelper::DragDrop(&p, &Globals::getScriptConfig()->clearTileDestPoint);
            }
            break;
        }
        case 103:
        {
            if (Objects::Game::getTargetId() <= 0)
                break;

            for (auto* rule : Globals::getScriptConfig()->m_pvpSingleTargetComboRules)
            {
                if (rule->spell == nullptr || Game::isSpellOnCooldown(rule->spell) || (rule->itemId == 0 && !rule->spell->vocations[Game::getPlayerVocation()]) || (rule->spell->range > 0 && rule->spell->range < Game::getTargetedCreature().Position.getDistance(Game::getPlayerPosition())))
                    continue;

                Input* input = new Input();

                input->gameTime = Game::getGameTime();
                input->canRepeat = true;

                if (rule->itemId > 0)
                {
                    input->itemId = rule->itemId;
                    input->itemUseType = ItemUseType::UseOnTarget;
                }
                else if (!rule->spellInput.empty())
                {
                    input->text = rule->spellInput;
                }

                Globals::addInput(input);


                break;
            }
        }
        default:
            break;
        }

    }

    return false;
    //return QMainWindow::nativeEvent(eventType, message, result);
}

void PvpTools::UpdateUi()
{
    ui->checkBox->setChecked(Globals::getScriptConfig()->getPvPHoldTarget());
    ui->checkBox_2->setChecked(Globals::getScriptConfig()->getPvPDashTarget());
    ui->checkBox_3->setChecked(Globals::getScriptConfig()->getPvPParalyzeTarget());

    // Combo
    ui->checkBox_10->setChecked(Globals::getScriptConfig()->getPvPOnComboUE());
    if (Globals::getScriptConfig()->m_pvpOnComboUEActionA->itemId > 0)
        ui->lineEdit_2->setText(QString::number(Globals::getScriptConfig()->m_pvpOnComboUEActionA->itemId));
    else
        ui->lineEdit_2->setText(QString::fromStdString(Globals::getScriptConfig()->m_pvpOnComboUEActionA->spellInput));
    if (Globals::getScriptConfig()->m_pvpOnComboUEActionB->itemId > 0)
        ui->lineEdit_3->setText(QString::number(Globals::getScriptConfig()->m_pvpOnComboUEActionB->itemId));
    else
        ui->lineEdit_3->setText(QString::fromStdString(Globals::getScriptConfig()->m_pvpOnComboUEActionB->spellInput));

    // Avatar
    ui->checkBox_11->setChecked(Globals::getScriptConfig()->getPvPOnComboAvatar());
    if (Globals::getScriptConfig()->m_pvpOnComboAvatarActionA->itemId > 0)
        ui->lineEdit_4->setText(QString::number(Globals::getScriptConfig()->m_pvpOnComboAvatarActionA->itemId));
    else
        ui->lineEdit_4->setText(QString::fromStdString(Globals::getScriptConfig()->m_pvpOnComboAvatarActionA->spellInput));
    if (Globals::getScriptConfig()->m_pvpOnComboAvatarActionB->itemId > 0)
        ui->lineEdit_5->setText(QString::number(Globals::getScriptConfig()->m_pvpOnComboAvatarActionB->itemId));
    else
        ui->lineEdit_5->setText(QString::fromStdString(Globals::getScriptConfig()->m_pvpOnComboAvatarActionB->spellInput));


    ui->combo1Content->setText(QString::fromStdString(Globals::getScriptConfig()->m_pvpOnComboUEActionA->spellInput));
    ui->combo1Content->setText(QString::fromStdString(Globals::getScriptConfig()->m_pvpOnComboUEActionB->content));

    ui->combo1Leader->setText(QString::fromStdString(Globals::getScriptConfig()->ComboRules[0]->leader));
    ui->combo2Leader->setText(QString::fromStdString(Globals::getScriptConfig()->ComboRules[1]->leader));
    ui->combo3Leader->setText(QString::fromStdString(Globals::getScriptConfig()->ComboRules[2]->leader));

    ui->combo1Content->setText(QString::fromStdString(Globals::getScriptConfig()->ComboRules[0]->content));
    ui->combo2Content->setText(QString::fromStdString(Globals::getScriptConfig()->ComboRules[1]->content));
    ui->combo3Content->setText(QString::fromStdString(Globals::getScriptConfig()->ComboRules[2]->content));

    if (Globals::getScriptConfig()->ComboRules[0]->itemId > 0)
        ui->combo1Input->setText(QString::number(Globals::getScriptConfig()->ComboRules[0]->itemId));
    else
        ui->combo1Input->setText(QString::fromStdString(Globals::getScriptConfig()->ComboRules[0]->spellInput));

    if (Globals::getScriptConfig()->ComboRules[1]->itemId > 0)
        ui->combo2Input->setText(QString::number(Globals::getScriptConfig()->ComboRules[1]->itemId));
    else
        ui->combo2Input->setText(QString::fromStdString(Globals::getScriptConfig()->ComboRules[1]->spellInput));

    if (Globals::getScriptConfig()->ComboRules[2]->itemId > 0)
        ui->combo3Input->setText(QString::number(Globals::getScriptConfig()->ComboRules[2]->itemId));
    else
        ui->combo3Input->setText(QString::fromStdString(Globals::getScriptConfig()->ComboRules[2]->spellInput));
}

void PvpTools::on_checkBox_stateChanged(int arg1)
{
    Globals::getScriptConfig()->setPvPHoldTarget(arg1);
}


void PvpTools::on_checkBox_2_stateChanged(int arg1)
{
    Globals::getScriptConfig()->setPvPDashTarget(arg1);

    QObject* parentPtr = this->parent();
    while (parentPtr->parent() != nullptr)
        parentPtr = parentPtr->parent();
    ((MainWindow*)parentPtr)->hudStatuses->ui->gotoTargetStatus->setChecked(arg1);
}


void PvpTools::on_checkBox_3_stateChanged(int arg1)
{
    Globals::getScriptConfig()->setPvPParalyzeTarget(arg1);
}

void PvpTools::on_combo1Leader_textChanged(const QString &arg1)
{
    ComboRule* c = Globals::getScriptConfig()->ComboRules[0];
    c->leader = arg1.toStdString();
}


void PvpTools::on_combo2Leader_textChanged(const QString &arg1)
{
    ComboRule* c = Globals::getScriptConfig()->ComboRules[1];
    c->leader = arg1.toStdString();
}


void PvpTools::on_combo3Leader_textChanged(const QString &arg1)
{
    ComboRule* c = Globals::getScriptConfig()->ComboRules[2];
    c->leader = arg1.toStdString();
}



void PvpTools::on_combo1Content_textChanged(const QString &arg1)
{
    ComboRule* c = Globals::getScriptConfig()->ComboRules[0];
    c->content = arg1.toStdString();
}


void PvpTools::on_combo2Content_textChanged(const QString &arg1)
{
    ComboRule* c = Globals::getScriptConfig()->ComboRules[1];
    c->content = arg1.toStdString();
}


void PvpTools::on_combo3Content_textChanged(const QString &arg1)
{
    ComboRule* c = Globals::getScriptConfig()->ComboRules[2];
    c->content = arg1.toStdString();
}


void PvpTools::on_combo1Input_textChanged(const QString &arg1)
{
    ComboRule* c = Globals::getScriptConfig()->ComboRules[0];

    c->itemId = 0;
    c->spellInput = "";
    c->spell = nullptr;

    if (arg1.toInt() > 0)
    {
        Spell* s = Globals::getSpell(arg1.toInt());
        if (s != nullptr)
            c->spell = s;

        c->itemId = arg1.toInt();
    }
    else
    {
        Spell* s = Globals::getSpell(arg1.toStdString());
        if (s != nullptr)
            c->spell = s;

        c->spellInput = arg1.toStdString();
    }
}


void PvpTools::on_combo2Input_textChanged(const QString &arg1)
{
    ComboRule* c = Globals::getScriptConfig()->ComboRules[1];

    c->itemId = 0;
    c->spellInput = "";
    c->spell = nullptr;

    if (arg1.toInt() > 0)
    {
        Spell* s = Globals::getSpell(arg1.toInt());
        if (s != nullptr)
            c->spell = s;

        c->itemId = arg1.toInt();
    }
    else
    {
        Spell* s = Globals::getSpell(arg1.toStdString());
        if (s != nullptr)
            c->spell = s;

        c->spellInput = arg1.toStdString();
    }
}


void PvpTools::on_combo3Input_textChanged(const QString &arg1)
{
    ComboRule* c = Globals::getScriptConfig()->ComboRules[2];

    c->itemId = 0;
    c->spellInput = "";
    c->spell = nullptr;

    if (arg1.toInt() > 0)
    {
        Spell* s = Globals::getSpell(arg1.toInt());
        if (s != nullptr)
            c->spell = s;

        c->itemId = arg1.toInt();
    }
    else
    {
        Spell* s = Globals::getSpell(arg1.toStdString());
        if (s != nullptr)
            c->spell = s;

        c->spellInput = arg1.toStdString();
    }
}



void PvpTools::on_checkBox_10_stateChanged(int arg1)
{
    Globals::getScriptConfig()->setPvPOnComboUE(arg1);
    if (arg1)
        Objects::Game::m_lastSeenChatMessage = 0;

    QObject* parentPtr = this->parent();
    while (parentPtr->parent() != nullptr)
        parentPtr = parentPtr->parent();
    ((MainWindow*)parentPtr)->hudStatuses->ui->comboUEStatus->setChecked(arg1);
}


void PvpTools::on_lineEdit_2_textChanged(const QString &arg1)
{
    ComboRule* rule = Globals::getScriptConfig()->m_pvpOnComboUEActionA;

    rule->itemId = 0;
    rule->spellInput = "";
    rule->spell = nullptr;

    if (arg1.toInt() > 0)
    {
        Spell* s = Globals::getSpell(arg1.toInt());
        if (s != nullptr)
            rule->spell = s;

        rule->itemId = arg1.toInt();
    }
    else
    {
        Spell* s = Globals::getSpell(arg1.toStdString());
        if (s != nullptr)
            rule->spell = s;

        rule->spellInput = arg1.toStdString();
    }
}


void PvpTools::on_lineEdit_3_textChanged(const QString &arg1)
{
    ComboRule* rule = Globals::getScriptConfig()->m_pvpOnComboUEActionB;

    rule->itemId = 0;
    rule->spellInput = "";
    rule->spell = nullptr;

    if (arg1.toInt() > 0)
    {
        Spell* s = Globals::getSpell(arg1.toInt());
        if (s != nullptr)
            rule->spell = s;

        rule->itemId = arg1.toInt();
    }
    else
    {
        Spell* s = Globals::getSpell(arg1.toStdString());
        if (s != nullptr)
            rule->spell = s;

        rule->spellInput = arg1.toStdString();
    }
}

void PvpTools::on_checkBox_11_stateChanged(int arg1)
{
    Globals::getScriptConfig()->setPvPOnComboAvatar(arg1);
    if (arg1)
        Objects::Game::m_lastSeenChatMessage = 0;
}


void PvpTools::on_lineEdit_4_textChanged(const QString &arg1)
{
    ComboRule* rule = Globals::getScriptConfig()->m_pvpOnComboAvatarActionA;

    rule->itemId = 0;
    rule->spellInput = "";
    rule->spell = nullptr;

    if (arg1.toInt() > 0)
    {
        Spell* s = Globals::getSpell(arg1.toInt());
        if (s != nullptr)
            rule->spell = s;

        rule->itemId = arg1.toInt();
    }
    else
    {
        Spell* s = Globals::getSpell(arg1.toStdString());
        if (s != nullptr)
            rule->spell = s;

        rule->spellInput = arg1.toStdString();
    }
}


void PvpTools::on_lineEdit_5_textChanged(const QString &arg1)
{
    ComboRule* rule = Globals::getScriptConfig()->m_pvpOnComboAvatarActionB;

    rule->itemId = 0;
    rule->spellInput = "";
    rule->spell = nullptr;

    if (arg1.toInt() > 0)
    {
        Spell* s = Globals::getSpell(arg1.toInt());
        if (s != nullptr)
            rule->spell = s;

        rule->itemId = arg1.toInt();
    }
    else
    {
        Spell* s = Globals::getSpell(arg1.toStdString());
        if (s != nullptr)
            rule->spell = s;

        rule->spellInput = arg1.toStdString();
    }
}


void PvpTools::on_clearTileDest_clicked()
{
    SetForegroundWindow(Globals::getHWnd());
    Sleep(200);
    while (GetForegroundWindow() == Globals::getHWnd())
    {
        if (GetAsyncKeyState(VK_LBUTTON) & 1)
        {
            GetCursorPos(&Globals::getScriptConfig()->clearTileDestPoint);
            ScreenToClient(GetForegroundWindow(), &Globals::getScriptConfig()->clearTileDestPoint);

            ui->clearTileDest->setText("Destination {x: " + QString::number(Globals::getScriptConfig()->clearTileDestPoint.x) + " y: " + QString::number(Globals::getScriptConfig()->clearTileDestPoint.y) + "}");
            break;
        }
    }

    QObject* parentPtr = this->parent();
    while (parentPtr->parent() != nullptr)
        parentPtr = parentPtr->parent();
    SetForegroundWindow((HWND)((MainWindow*)parentPtr)->winId());
}


void PvpTools::on_protSqmFlowerSource_clicked()
{
    SetForegroundWindow(Globals::getHWnd());
    Sleep(200);
    while (GetForegroundWindow() == Globals::getHWnd())
    {
        if (GetAsyncKeyState(VK_LBUTTON) & 1)
        {
            GetCursorPos(&Globals::getScriptConfig()->flowerSourcePoint);
            ScreenToClient(GetForegroundWindow(), &Globals::getScriptConfig()->flowerSourcePoint);
            
            ui->protSqmFlowerSource->setText("Source {x: " + QString::number(Globals::getScriptConfig()->flowerSourcePoint.x) + " y: " + QString::number(Globals::getScriptConfig()->flowerSourcePoint.y) + "}");
            break;
        }
    }

    QObject* parentPtr = this->parent();
    while (parentPtr->parent() != nullptr)
        parentPtr = parentPtr->parent();
    SetForegroundWindow((HWND)((MainWindow*)parentPtr)->winId());
    ((MainWindow*)parentPtr)->activateWindow();
}


void PvpTools::on_protSqmKey_editingFinished()
{
    QKeySequence keySequence = ui->protSqmKey->keySequence();
    UnregisterHotKey(HWND(winId()), 101);

    QSettings mySettings("KzSoft", "KzBot - Tibia");
    mySettings.setValue("protSqmKey", keySequence.toString());
    mySettings.sync();

    if(QLineEdit *lineEdit = ui->protSqmKey->findChild<QLineEdit*>("qt_keysequenceedit_lineedit")){
        lineEdit->setPlaceholderText("Key");
    }

    if (!keySequence.isEmpty())
    {
        uint32_t modifiers = 0;
        if (keySequence[0].keyboardModifiers() & Qt::ShiftModifier)
            modifiers |= MOD_SHIFT;
        if (keySequence[0].keyboardModifiers() & Qt::ControlModifier)
            modifiers |= MOD_CONTROL;
        if (keySequence[0].keyboardModifiers() & Qt::AltModifier)
            modifiers |= MOD_ALT;

        bool ext;
        if (!RegisterHotKey(HWND(winId()), 101, modifiers, Util::KzHelper::qtKeyToVK(keySequence[0].key(), ext)))
        {
            ui->protSqmKey->clear();
            if(QLineEdit *lineEdit = ui->protSqmKey->findChild<QLineEdit*>("qt_keysequenceedit_lineedit")){
                lineEdit->setPlaceholderText("Key");
            }
        }
    }
}


void PvpTools::on_clearTileKey_editingFinished()
{
    QKeySequence keySequence = ui->clearTileKey->keySequence();
    UnregisterHotKey(HWND(winId()), 102);

    QSettings mySettings("KzSoft", "KzBot - Tibia");
    mySettings.setValue("clearTileKey", keySequence.toString());
    mySettings.sync();

    if(QLineEdit *lineEdit = ui->clearTileKey->findChild<QLineEdit*>("qt_keysequenceedit_lineedit")){
        lineEdit->setPlaceholderText("Key");
    }

    if (!keySequence.isEmpty())
    {
        uint32_t modifiers = 0;
        if (keySequence[0].keyboardModifiers() & Qt::ShiftModifier)
            modifiers |= MOD_SHIFT;
        if (keySequence[0].keyboardModifiers() & Qt::ControlModifier)
            modifiers |= MOD_CONTROL;
        if (keySequence[0].keyboardModifiers() & Qt::AltModifier)
            modifiers |= MOD_ALT;

        bool ext;
        if (!RegisterHotKey(HWND(winId()), 102, modifiers, Util::KzHelper::qtKeyToVK(keySequence[0].key(), ext)))
        {
            ui->clearTileKey->clear();
            if(QLineEdit *lineEdit = ui->clearTileKey->findChild<QLineEdit*>("qt_keysequenceedit_lineedit")){
                lineEdit->setPlaceholderText("Key");
            }
        }
    }
}


void PvpTools::on_comboInput_textChanged(const QString &arg1)
{
    Globals::getScriptConfig()->m_pvpSingleTargetComboRules.clear();
    // Get Spells / Items
    for (auto input : ui->comboInput->text().trimmed().split(";"))
    {
        input = input.trimmed();
        ComboRule* rule = new ComboRule();

        rule->itemId = 0;
        rule->spellInput = "";
        rule->spell = nullptr;

        if (input.toInt() > 0)
        {
            Spell* s = Globals::getSpell(input.toInt());
            if (s != nullptr)
                rule->spell = s;

            rule->itemId = input.toInt();
            std::cout << rule->itemId << std::endl;
        }
        else
        {
            Spell* s = Globals::getSpell(input.toStdString());
            if (s != nullptr)
                rule->spell = s;

            rule->spellInput = input.toStdString();
        }

        Globals::getScriptConfig()->m_pvpSingleTargetComboRules.emplace_back(rule);
    }
}


void PvpTools::on_comboKey_editingFinished()
{
    // Register Hotkey
    QKeySequence keySequence = ui->comboKey->keySequence();
    UnregisterHotKey(HWND(winId()), 103);

    QSettings mySettings("KzSoft", "KzBot - Tibia");
    mySettings.setValue("singleTargetComboKey", keySequence.toString());
    mySettings.sync();

    if(QLineEdit *lineEdit = ui->clearTileKey->findChild<QLineEdit*>("qt_keysequenceedit_lineedit")){
        lineEdit->setPlaceholderText("Key");
    }

    if (!keySequence.isEmpty())
    {
        uint32_t modifiers = 0;
        if (keySequence[0].keyboardModifiers() & Qt::ShiftModifier)
            modifiers |= MOD_SHIFT;
        if (keySequence[0].keyboardModifiers() & Qt::ControlModifier)
            modifiers |= MOD_CONTROL;
        if (keySequence[0].keyboardModifiers() & Qt::AltModifier)
            modifiers |= MOD_ALT;

        bool ext;
        if (!RegisterHotKey(HWND(winId()), 103, modifiers, Util::KzHelper::qtKeyToVK(keySequence[0].key(), ext)))
        {
            ui->comboKey->clear();
            if(QLineEdit *lineEdit = ui->comboKey->findChild<QLineEdit*>("qt_keysequenceedit_lineedit")){
                lineEdit->setPlaceholderText("Key");
            }
        }
    }
}


void PvpTools::on_comboStatus_stateChanged(int arg1)
{
    Globals::getScriptConfig()->m_pvpSingleTargetComboStatus = arg1;
}

