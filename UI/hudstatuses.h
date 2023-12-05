#ifndef HUDSTATUSES_H
#define HUDSTATUSES_H

#include <QWidget>

namespace Ui {
class HUDStatuses;
}

class HUDStatuses : public QWidget
{
    Q_OBJECT

public:
    explicit HUDStatuses(QWidget *parent = nullptr);
    ~HUDStatuses();
    Ui::HUDStatuses *ui;

    bool _isVisible = false;

    bool nativeEvent(const QByteArray& eventType, void* message, qintptr* result);


protected:
    virtual void mousePressEvent( QMouseEvent *e );
    virtual void mouseMoveEvent( QMouseEvent *e );
    virtual void mouseReleaseEvent( QMouseEvent *e );

signals:
    void changeStatus(const QString& statusName);

private slots:
    void on_closeHUD_clicked();

private:
    QStringList hotkeyList;
    bool _mousePressed;
    QPoint _mousePosition;
};

#endif // HUDSTATUSES_H
