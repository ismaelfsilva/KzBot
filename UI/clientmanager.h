#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include "qtablewidget.h"
#include <QWidget>

namespace Ui {
class ClientManager;
}

class ClientManager : public QWidget
{
    Q_OBJECT

public:
    explicit ClientManager(QWidget *parent = nullptr);
    ~ClientManager();

    void RefreshClients();

    void CheckFirstClient();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);

private:
    Ui::ClientManager *ui;
};

#endif // CLIENTMANAGER_H
