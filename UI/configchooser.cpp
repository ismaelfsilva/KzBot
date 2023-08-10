#include "configchooser.h"
#include "ui_configchooser.h"
#include "QMouseEvent"
#include <iostream>
#include <ostream>

ConfigChooser::ConfigChooser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigChooser)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::SubWindow);
}

ConfigChooser::~ConfigChooser()
{
    delete ui;
}

void ConfigChooser::mousePressEvent( QMouseEvent *e )
{
    if ( e->button() == Qt::LeftButton ) {
        _mousePressed = true;
        _mousePosition = e->pos();
    }
}

void ConfigChooser::mouseMoveEvent( QMouseEvent *e )
{
    if ( _mousePressed ) {
        move( mapToParent( e->pos() - _mousePosition ) );
    }
}

void ConfigChooser::mouseReleaseEvent( QMouseEvent *e )
{
    if ( e->button() == Qt::LeftButton ) {
        _mousePressed = false;
        _mousePosition = QPoint();
    }
}

void ConfigChooser::on_pushButton_toggled(bool checked)
{
    if (!checked)
        return;

    QString buttonFileName = "default.xml";
    if (_lastFileName != buttonFileName)
    {
        _lastFileName = buttonFileName;
        emit loadSetting(buttonFileName);
    }
}


void ConfigChooser::on_pushButton_2_toggled(bool checked)
{
    if (!checked)
        return;

    QString buttonFileName = "tank.xml";
    if (_lastFileName != buttonFileName)
    {
        _lastFileName = buttonFileName;
        emit loadSetting(buttonFileName);
    }
}


void ConfigChooser::on_pushButton_3_toggled(bool checked)
{
    if (!checked)
        return;

    QString buttonFileName = "swap.xml";
    if (_lastFileName != buttonFileName)
    {
        _lastFileName = buttonFileName;
        emit loadSetting(buttonFileName);
    }
}


void ConfigChooser::on_pushButton_4_toggled(bool checked)
{
    if (!checked)
        return;

    QString buttonFileName = "hunt.xml";
    if (_lastFileName != buttonFileName)
    {
        _lastFileName = buttonFileName;
        emit loadSetting(buttonFileName);
    }
}


void ConfigChooser::on_pushButton_5_toggled(bool checked)
{
    if (!checked)
        return;

    QString buttonFileName = "boss.xml";
    if (_lastFileName != buttonFileName)
    {
        _lastFileName = buttonFileName;
        emit loadSetting(buttonFileName);
    }
}

