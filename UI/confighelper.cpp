#include "confighelper.h"
#include "ui_confighelper.h"

#include "../Settings/globals.h"
#include "../Util/kzhelper.h"
#include <Qt>
#include <QClipboard>

ConfigHelper::ConfigHelper(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConfigHelper)
{
    ui->setupUi(this);
    

    ui->frame->setVisible(false);
    ui->frame_2->setVisible(false);
    ui->frame_3->setVisible(false);
    ui->frame_4->setVisible(false);
    ui->frame_5->setVisible(false);
    ui->frame_6->setVisible(false);
    ui->frame_7->setVisible(false);
    ui->frame_9->setVisible(false);

    this->setMaximumSize(800, 600);
    this->setMinimumSize(800, 600);
    this->setFixedSize(800, 600);
}

ConfigHelper::~ConfigHelper()
{
    delete ui;
}

void ConfigHelper::on_radioButton_toggled(bool checked)
{
    ui->initFrame->setVisible(checked);

    ui->pushButton->setEnabled(!checked);
}


void ConfigHelper::on_radioButton_2_toggled(bool checked)
{

    ui->frame->setVisible(checked);
    ui->frame_2->setVisible(checked);
    ui->frame_3->setVisible(checked);
}


void ConfigHelper::on_radioButton_3_toggled(bool checked)
{
    ui->frame_7->setVisible(checked);
    ui->frame_4->setVisible(checked);
    ui->frame_5->setVisible(checked);
    ui->frame_6->setVisible(checked);
}


void ConfigHelper::on_radioButton_4_toggled(bool checked)
{
    ui->frame_9->setVisible(checked);

    ui->pushButton_2->setEnabled(!checked);
}

void ConfigHelper::on_pushButton_clicked()
{
    if (ui->radioButton->isChecked())
        return;
    else if (ui->radioButton_2->isChecked())
        ui->radioButton->setChecked(true);
    else if (ui->radioButton_3->isChecked())
        ui->radioButton_2->setChecked(true);
    else if (ui->radioButton_4->isChecked())
        ui->radioButton_3->setChecked(true);
}


void ConfigHelper::on_pushButton_2_clicked()
{
    if (ui->radioButton_4->isChecked())
        return;
    else if (ui->radioButton_3->isChecked())
        ui->radioButton_4->setChecked(true);
    else if (ui->radioButton_2->isChecked())
        ui->radioButton_3->setChecked(true);
    else if (ui->radioButton->isChecked())
        ui->radioButton_2->setChecked(true);
}


void ConfigHelper::on_pushButton_3_clicked()
{
    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText("                                                  ", QClipboard::Clipboard);
}


void ConfigHelper::on_pushButton_4_clicked()
{
    if (Globals::isSet)
        Util::KzHelper::SendKey(VK_F13);
}

