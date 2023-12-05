#include "hudpvp.h"
#include "qevent.h"
#include "qsettings.h"
#include "ui_hudpvp.h"
#include "../Objects/game.h"
#include <thread>

HUDPvP::HUDPvP(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HUDPvP)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::SubWindow);

    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TranslucentBackground);

    setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->moveHUD->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    QSettings mySettings("KzSoft", "KzBot - Tibia");
    mySettings.sync();
    this->move(mySettings.value("PvPHudPos").toPoint());

    m_threadStatus = true;
    m_updaterThread = std::thread(&HUDPvP::UI_Updater_Thread, this);
}

HUDPvP::~HUDPvP()
{
    m_threadStatus = false;
    delete ui;
}

void HUDPvP::mousePressEvent( QMouseEvent *e )
{
    if ( e->button() == Qt::LeftButton ) {
        _mousePressed = true;
        _mousePosition = e->pos();
    }
}

void HUDPvP::mouseMoveEvent( QMouseEvent *e )
{
    if ( _mousePressed ) {
        move( mapToParent( e->pos() - _mousePosition ) );

        QSettings mySettings("KzSoft", "KzBot - Tibia");
        mySettings.setValue("PvPHudPos", this->pos());
        mySettings.sync();
    }
}

void HUDPvP::mouseReleaseEvent( QMouseEvent *e )
{
    if ( e->button() == Qt::LeftButton ) {
        _mousePressed = false;
        _mousePosition = QPoint();
    }
}

void HUDPvP::on_closeHUD_clicked()
{
    this->_isVisible = false;
    this->hide();
}

void HUDPvP::UI_Updater_Thread()
{
    while (m_threadStatus)
    {
        Sleep(500);
        if (!Globals::isSet || !this->isVisible() || this->isHidden() || !this->_isVisible)
            continue;

        // General
        uint32_t targetByCount = 0;
        for (auto lastTargetTime : Game::getPlayerTargetedBy())
        {
            if ((int)(Game::getGameTime() - lastTargetTime.second) < (int)5000)
                targetByCount++;
        }
        ui->targetedByValue->setText(QString::number(targetByCount));

        // Friends
        ui->friendsSeenValue->setText(QString::number(Objects::Game::getPlayerAlliesSeen().size()));
        ui->friendsCountValue->setText(QString::number(Objects::Game::getPlayerAlliesAroundCount()));
        ui->friendsEdCountValue->setText(QString::number(Objects::Game::getPlayerAlliesAround()[Vocation::Druid].size()));
        ui->friendsMsCountValue->setText(QString::number(Objects::Game::getPlayerAlliesAround()[Vocation::Sorcerer].size()));
        ui->friendsEkCountValue->setText(QString::number(Objects::Game::getPlayerAlliesAround()[Vocation::Knight].size()));
        ui->friendsRpCountValue->setText(QString::number(Objects::Game::getPlayerAlliesAround()[Vocation::Paladin].size()));

        /*
        CachedCreature* lowestLevelMageFriend = nullptr;
        std::vector<CachedCreature> alliesDruidList = Objects::Game::getPlayerAlliesAround()[Vocation::Druid];
        std::vector<CachedCreature> alliesSorcererList = Objects::Game::getPlayerAlliesAround()[Vocation::Sorcerer];
        for (CachedCreature creature : alliesDruidList)
        {
            if (lowestLevelMageFriend == nullptr || creature.Health < lowestLevelMageFriend->Health)
                lowestLevelMageFriend = &creature;
        }
        for (CachedCreature creature : alliesSorcererList)
        {
            if (lowestLevelMageFriend == nullptr || creature.Health < lowestLevelMageFriend->Health)
                lowestLevelMageFriend = &creature;
        }
        if (lowestLevelMageFriend != nullptr)
            ui->friendsLowestMageValue->setText(QString::fromStdString(lowestLevelMageFriend->Name));
*/
        // Enemies
        ui->enemiesSeenValue->setText(QString::number(Objects::Game::getPlayerEnemiesSeen().size()));
        ui->enemiesCountValue->setText(QString::number(Objects::Game::getPlayerEnemiesAroundCount()));
        ui->enemiesEdCountValue->setText(QString::number(Objects::Game::getPlayerEnemiesAround()[Vocation::Druid].size()));
        ui->enemiesMsCountValue->setText(QString::number(Objects::Game::getPlayerEnemiesAround()[Vocation::Sorcerer].size()));
        ui->enemiesEkCountValue->setText(QString::number(Objects::Game::getPlayerEnemiesAround()[Vocation::Knight].size()));
        ui->enemiesRpCountValue->setText(QString::number(Objects::Game::getPlayerEnemiesAround()[Vocation::Paladin].size()));

        // Low Level & Enemies Name Updater
        CachedCreature* lowestLevelMageEnemy = nullptr;
        CachedCreature* lowestLevelEnemy = nullptr;
        std::unordered_map<std::string, bool> enemiesNames;

        std::map<Vocation, std::vector<CachedCreature>> enemiesAround = Objects::Game::getPlayerEnemiesAround();

        for (auto &vocationList : enemiesAround)
        {
            for (CachedCreature &creature : vocationList.second)
            {
                enemiesNames[creature.Name] = true;
/*
                if (lowestLevelEnemy == nullptr || creature.Health < lowestLevelEnemy->Health)
                    lowestLevelEnemy = &creature;

                if ((vocationList.first == Vocation::Druid || vocationList.first == Vocation::Sorcerer) && (lowestLevelMageEnemy == nullptr || creature.Health < lowestLevelMageEnemy->Health))
                    lowestLevelMageEnemy = &creature;
*/
            }
        }

        if (lowestLevelEnemy != nullptr)
            ui->enemiesLowestLevelValue->setText(QString::fromStdString(lowestLevelEnemy->Name));
        if (lowestLevelMageEnemy != nullptr)
            ui->enemiesLowestMageValue->setText(QString::fromStdString(lowestLevelMageEnemy->Name));

        // Combo UE
        static uint64_t lastEnemyComboUE = 0;
        if (Game::getGameTime() - lastEnemyComboUE > 10000)
        {
            uint32_t UECount = 0;
            for (auto UE : Game::getUltimateExplosions())
            {
                if (enemiesNames[UE.first] && Game::getGameTime() - UE.second < 5000 && (lastEnemyComboUE == 0 || UE.second - lastEnemyComboUE > 10000))
                    UECount++;
            }
            if (UECount >= Globals::getScriptConfig()->getUECountToConsiderCombo())
                lastEnemyComboUE = Game::getGameTime();
        }
        if (lastEnemyComboUE > 0)
            ui->lastComboUEValue->setText(QString::number((Game::getGameTime() - lastEnemyComboUE) / 1000) + "s");
    }
}
