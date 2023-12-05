#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../Threads/healer.h"
#include "../Threads/updater.h"
#include "../Threads/partyhunt.h"
#include "configchooser.h"
#include "healer.h"
#include "hudpvp.h"
#include "hudstatuses.h"
#include "partyhunt.h"
#include "pvptools.h"
#include "toolstab.h"
#include <ui_healer.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *ui;

    Healer *healer;
    ConfigChooser *configChooser;
    HUDStatuses *hudStatuses;
    HUDPvP *hudPvP;
    ToolsTab *tools;
    PvpTools *pvpTools;
    PartyHunt *partyHunt;
    void on_Form_StartUp();
    void UpdateUi();

    bool LoadSetting(QString fileName, bool errorMessage = false);
    void SaveSetting(QString fileName, bool errorMessage = false);
public slots:
    void loadSettingSignal(QString fileName);
    void onTibiaClientFocusChange(const HWND& focusedHWnd);
    void changeStatusSignal(const QString &statusName);

private slots:
    void on_actionSelect_Client_triggered();

    void on_actionDefault_triggered();

    void on_actionDefault_2_triggered();

    void on_actionTank_2_triggered();

    void on_actionTank_triggered();

    void on_actionSwap_triggered();

    void on_actionSwap_2_triggered();

    void on_actionHunt_triggered();

    void on_actionHunt_2_triggered();

    void on_actionBoss_triggered();

    void on_actionBoss_2_triggered();

    void on_actionExit_triggered();

    void on_actionPress_Kz_Key_triggered();

    void on_actionOther_triggered();

    void on_actionOther_2_triggered();

    void on_actionInitial_Config_triggered();

    void on_actionLogout_triggered();

    void on_actionStatus_triggered();

    void on_actionPvP_triggered();

    void on_actionConfig_Selector_triggered();

    void on_actionv0_1_10_0_triggered();

private:

    Threads::Updater *updaterThread;

    QCheckBox* generalStatusCheckBox;
    QCheckBox* healerCheckBox;
    QCheckBox* toolsCheckBox;
    QCheckBox* pvpToolsCheckBox;
    QCheckBox* partyHuntCheckBox;

};

#endif // MAINWINDOW_H
