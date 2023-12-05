#include "hudstatuses.h"
#include "mainwindow.h"
#include "qevent.h"
#include "ui_hudstatuses.h"
#include <QKeySequenceEdit>
#include <QMessageBox>
#include <QSettings>
#include <iostream>
#include <ostream>
#include <ui_mainwindow.h>
#include "../Util/kzhelper.h"


HUDStatuses::HUDStatuses(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HUDStatuses)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::SubWindow);

    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TranslucentBackground);
    //setAttribute(Qt::WA_PaintOnScreen);

    setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->moveHUD->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    QString checkButtonStyleSheet = "QPushButton {border: 0px; background-color: rgba(255, 0, 0, 200);} QPushButton:checked {background-color: rgba(0, 255, 0, 200)}";

    QSettings mySettings("KzSoft", "KzBot - Tibia");
    mySettings.sync();
    this->move(mySettings.value("StatusHudPos").toPoint());


    for (auto control : this->children())
    {
        if (control->objectName().endsWith("Status"))
        {
            ((QPushButton*)control)->setStyleSheet(checkButtonStyleSheet);
            connect((QPushButton*)control, &QPushButton::clicked, this, [control, this](int arg1) {
                emit changeStatus(control->objectName());
            });
            connect((QPushButton*)control, &QPushButton::toggled, this, [control](int arg1) {
                if (arg1)
                    control->setProperty("text", "On");
                else
                    control->setProperty("text", "Off");
            });
        }
        else if (control->objectName().endsWith("Key"))
        {
            ((QKeySequenceEdit*) control)->setMaximumSequenceLength(1);
            ((QKeySequenceEdit*) control)->setClearButtonEnabled(true);
            if(QLineEdit *lineEdit = control->findChild<QLineEdit*>("qt_keysequenceedit_lineedit")){
                lineEdit->setPlaceholderText("Key");
                lineEdit->setAlignment(Qt::AlignCenter);
                lineEdit->setStyleSheet("text-align: center; border: 0px;background-color: rgba(100, 100, 200, 200);");
            }



            uint hotkeyId = hotkeyList.size();
            QString statusName = control->objectName().replace("Key", "Status");
            hotkeyList.push_back(statusName);



            connect((QKeySequenceEdit*)control, &QKeySequenceEdit::editingFinished, this, [this, control, hotkeyId, statusName]() {
                QKeySequence keySequence = ((QKeySequenceEdit*)control)->keySequence();
                UnregisterHotKey(HWND(winId()), hotkeyId);

                QSettings mySettings("KzSoft", "KzBot - Tibia");
                mySettings.setValue(statusName, keySequence.toString());
                mySettings.sync();

                if(QLineEdit *lineEdit = control->findChild<QLineEdit*>("qt_keysequenceedit_lineedit")){
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
                    if (!RegisterHotKey(HWND(winId()), hotkeyId, modifiers, Util::KzHelper::qtKeyToVK(keySequence[0].key(), ext)))
                    {
                        ((QKeySequenceEdit*)control)->clear();
                        if(QLineEdit *lineEdit = control->findChild<QLineEdit*>("qt_keysequenceedit_lineedit")){
                            lineEdit->setPlaceholderText("Key");
                        }
                    }
                }
            });


            mySettings.sync();
            ((QKeySequenceEdit*) control)->setKeySequence(QKeySequence::fromString(mySettings.value(statusName).toString()));
            ((QKeySequenceEdit*) control)->editingFinished();
        }
    }
}

HUDStatuses::~HUDStatuses()
{
    delete ui;
}

bool HUDStatuses::nativeEvent(const QByteArray& eventType, void* message, qintptr* result)
{
    Q_UNUSED(eventType);
    Q_UNUSED(result);
    MSG* msg = static_cast<MSG*>(message);
    if (msg->message == WM_HOTKEY)
    {
        emit changeStatus(hotkeyList[msg->wParam]);
    }

    return false;
    //return QMainWindow::nativeEvent(eventType, message, result);
}

void HUDStatuses::mousePressEvent( QMouseEvent *e )
{
    if ( e->button() == Qt::LeftButton ) {
        _mousePressed = true;
        _mousePosition = e->pos();
    }
}

void HUDStatuses::mouseMoveEvent( QMouseEvent *e )
{
    if ( _mousePressed ) {
        move( mapToParent( e->pos() - _mousePosition ) );

        QSettings mySettings("KzSoft", "KzBot - Tibia");
        mySettings.setValue("StatusHudPos", this->pos());
        mySettings.sync();
    }
}

void HUDStatuses::mouseReleaseEvent( QMouseEvent *e )
{
    if ( e->button() == Qt::LeftButton ) {
        _mousePressed = false;
        _mousePosition = QPoint();
    }
}

void HUDStatuses::on_closeHUD_clicked()
{
    this->_isVisible = false;
    this->hide();
}

