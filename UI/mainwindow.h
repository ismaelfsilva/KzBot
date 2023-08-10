#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../Threads/healer.h"
#include "../Threads/updater.h"
#include "../Threads/partyhunt.h"
#include "configchooser.h"
#include "healer.h"
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

    Healer *healer;
    ConfigChooser *configChooser;
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

    void on_actionShow_Config_Selector_toggled(bool arg1);

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

private:
    Ui::MainWindow *ui;

    Threads::Updater *updaterThread;

    QCheckBox* generalStatusCheckBox;
    QCheckBox* healerCheckBox;
    QCheckBox* toolsCheckBox;
    QCheckBox* pvpToolsCheckBox;
    QCheckBox* partyHuntCheckBox;

};

#endif // MAINWINDOW_H
