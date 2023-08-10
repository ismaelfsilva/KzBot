#ifndef CONFIGCHOOSER_H
#define CONFIGCHOOSER_H

#include <QWidget>

namespace Ui {
class ConfigChooser;
}

class ConfigChooser : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigChooser(QWidget *parent = nullptr);
    ~ConfigChooser();
    Ui::ConfigChooser *ui;
    QString _lastFileName;

signals:
    void loadSetting(const QString& fileName);

protected:
    virtual void mousePressEvent( QMouseEvent *e );
    virtual void mouseMoveEvent( QMouseEvent *e );
    virtual void mouseReleaseEvent( QMouseEvent *e );

private slots:
    void on_pushButton_toggled(bool checked);

    void on_pushButton_2_toggled(bool checked);

    void on_pushButton_3_toggled(bool checked);

    void on_pushButton_4_toggled(bool checked);

    void on_pushButton_5_toggled(bool checked);

private:

    bool _mousePressed;
    QPoint _mousePosition;
};

#endif // CONFIGCHOOSER_H
