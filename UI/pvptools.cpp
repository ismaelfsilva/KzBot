#include "pvptools.h"
#include "mainwindow.h"
#include "ui_hudstatuses.h"
#include "ui_pvptools.h"
#include "../Settings/globals.h"
#include "../Objects/game.h"

PvpTools::PvpTools(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PvpTools)
{
    ui->setupUi(this);

    Globals::getScriptConfig()->m_pvpOnComboUEActionA = new ComboRule("ComboUEA");
    Globals::getScriptConfig()->m_pvpOnComboUEActionB = new ComboRule("ComboUEB");

    Globals::getScriptConfig()->m_pvpOnComboAvatarActionA = new ComboRule("ComboAvatarA");
    Globals::getScriptConfig()->m_pvpOnComboAvatarActionB = new ComboRule("ComboAvatarB");

    Globals::getScriptConfig()->ComboRules.push_back(new ComboRule());
    Globals::getScriptConfig()->ComboRules.push_back(new ComboRule());
    Globals::getScriptConfig()->ComboRules.push_back(new ComboRule());
}

PvpTools::~PvpTools()
{
    delete ui;
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

