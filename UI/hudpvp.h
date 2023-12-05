#ifndef HUDPVP_H
#define HUDPVP_H

#include <QWidget>
#include <thread>

namespace Ui {
class HUDPvP;
}

class HUDPvP : public QWidget
{
    Q_OBJECT

public:
    explicit HUDPvP(QWidget *parent = nullptr);
    ~HUDPvP();
    Ui::HUDPvP *ui;

    bool _isVisible = false;

    void UI_Updater_Thread();
protected:
    virtual void mousePressEvent( QMouseEvent *e );
    virtual void mouseMoveEvent( QMouseEvent *e );
    virtual void mouseReleaseEvent( QMouseEvent *e );

private slots:
    void on_closeHUD_clicked();

private:
    bool m_threadStatus;
    std::thread m_updaterThread;


    bool _mousePressed;
    QPoint _mousePosition;
};

#endif // HUDPVP_H
