#include "shuffleeventwatcher.h"
#include<QDebug>

ShuffleEventWatcher::ShuffleEventWatcher(QObject *parent)
    : ButtonHoverWatcher(parent), isOn(false)
{
    imagePath = ":/buttons/shuffle.png";
    hoverImagePath = ":/buttons/shuffle-hover.png";
    pressedImagePath = ":/buttons/shuffle-pressed.png";
    releasedImagePath = ":/buttons/shuffle-released.png";
}

bool ShuffleEventWatcher::eventFilter(QObject * watched, QEvent * event)
{
    QToolButton * button = qobject_cast<QToolButton*>(watched);
    if (!button) {
        return false;
    }

    if (event->type() == QEvent::Enter) {
        // The push button is hovered by mouse
        qDebug()<<"Hovered";

        button->setIcon(QIcon(hoverImagePath));

        return false;
    }

    if (event->type() == QEvent::Leave){
        // The push button is unhovered by mouse
        qDebug()<<"Unhovered";

        if(!isOn)
            button->setIcon(QIcon(imagePath));
        else
           button->setIcon(QIcon(releasedImagePath));

        return false;
    }

    if(event->type() == QEvent::MouseButtonRelease)
    {
        //The push button is released by mouse
        qDebug()<<"Released";

        if(!isOn)
        {
            button->setIcon(QIcon(releasedImagePath));
            qDebug()<<"Setting isOn = true";
            isOn = true;
            button->setToolTip(tr("Turn shuffle off"));
        }
        else
        {
            button->setIcon(QIcon(imagePath));
            qDebug()<<"Setting isOn = false";
            isOn = false;
            button->setToolTip(tr("Turn shuffle on"));
        }

        return false;
    }

    if(event->type() == QEvent::MouseButtonPress){
        qDebug()<<"Pressed";

        //isPressed = true;
        button->setIcon(QIcon(pressedImagePath));

        return false;
    }

    return false;
}

bool ShuffleEventWatcher::statusOn()
{
    return isOn;
}
