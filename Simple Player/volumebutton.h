#ifndef VOLUMEBUTTON_H
#define VOLUMEBUTTON_H

#include <QToolButton>
#include <QtWidgets>

QT_FORWARD_DECLARE_CLASS(QMenu)
QT_FORWARD_DECLARE_CLASS(QLabel)
QT_FORWARD_DECLARE_CLASS(QSlider)

namespace Ui {
class Widget;
}

class VolumeButton : public QToolButton
{
    Q_OBJECT
    Q_PROPERTY(int volume READ volume WRITE setVolume NOTIFY volumeChanged)

public:
    explicit VolumeButton(QWidget *parent = nullptr, QHBoxLayout *horizontalControlBar = nullptr);

    int volume() const;

public slots:
    void increaseVolume();
    void descreaseVolume();
    void setVolume(int volume);
    void stylize();

    void setNum();

signals:
    void volumeChanged(int volume);

private:
    QMenu *menu = nullptr;
    QLabel *label = nullptr;
    QSlider *slider = nullptr;
};
#endif // VOLUMEBUTTON_H
