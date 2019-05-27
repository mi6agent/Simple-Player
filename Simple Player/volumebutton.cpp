#include "volumebutton.h"
#include<QtWin>

VolumeButton::VolumeButton(QWidget *parent, QHBoxLayout *horizontalControlBar) :
    QToolButton(parent)
{
    setFixedSize(40, 40);
    setIconSize(QSize(40, 40));
    horizontalControlBar->addWidget(this);
    this->setStyleSheet("background-color: rgba(255, 255, 255, 0);");

    qDebug().noquote()<<width()<<" "<<height();
    //move(11, 110);
    //setGeometry(11, 53, 50, 50);

    //QPixmap pix(":/buttons/full_volume.png");
    //setIcon(QIcon(pix));
    qDebug().noquote()<<iconSize().width()<<" "<<iconSize().height();

    //setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    setPopupMode(QToolButton::InstantPopup);

    QWidget *popup = new QWidget(this);

    slider = new QSlider(Qt::Horizontal, popup);
    slider->setRange(0, 100);
    connect(slider, &QAbstractSlider::valueChanged, this, &VolumeButton::volumeChanged);

    label = new QLabel(popup);
    label->setAlignment(Qt::AlignCenter);
    //label->setNum();
    //label->setMinimumWidth(label->sizeHint().width());
    label->setStyleSheet("QLabel { background-color : white; color : blue; }");

    typedef void(QLabel::*IntSlot)(int);
    connect(slider, &QAbstractSlider::valueChanged, label, static_cast<IntSlot>(&QLabel::setNum));
    connect(slider, &QAbstractSlider::valueChanged, this, setNum);

    QBoxLayout *popupLayout = new QHBoxLayout(popup);
    popupLayout->setMargin(2);
    popupLayout->addWidget(slider);
    popupLayout->addWidget(label);

    QWidgetAction *action = new QWidgetAction(this);
    action->setDefaultWidget(popup);

    menu = new QMenu(this);
    menu->addAction(action);
    setMenu(menu);

    stylize();
}

void VolumeButton::increaseVolume()
{
    slider->triggerAction(QSlider::SliderPageStepAdd);
}

void VolumeButton::descreaseVolume()
{
    slider->triggerAction(QSlider::SliderPageStepSub);
}

int VolumeButton::volume() const
{
    return slider->value();
}

void VolumeButton::setVolume(int volume)
{
    slider->setValue(volume);
}

void VolumeButton::stylize()
{
    if (QtWin::isCompositionEnabled()) {
        QtWin::enableBlurBehindWindow(menu);
        QString css("QMenu { border: 1px solid %1; border-radius: 2px; background: transparent; }");
        menu->setStyleSheet(css.arg(QtWin::realColorizationColor().name()));
    } else {
        QtWin::disableBlurBehindWindow(menu);
        QString css("QMenu { border: 1px solid black; background: %1; }");
        menu->setStyleSheet(css.arg(QtWin::realColorizationColor().name()));
    }
}

void VolumeButton::setNum()
{
    if(!slider->value())
        setIcon(QIcon(":/buttons/volume-0.png"));
    else if(slider->value() && slider->value() < 33)
        setIcon(QIcon(":/buttons/volume-1.png"));
    else if(slider->value() > 32 && slider->value() < 66)
        setIcon(QIcon(":/buttons/volume-2.png"));
    else
        setIcon(QIcon(":/buttons/volume-3.png"));
}
