#include "stopeventwatcher.h"
#include<QDebug>

StopEventWatcher::StopEventWatcher(QObject *parent) : ButtonHoverWatcher(parent)
{
    stopImagePath = ":/buttons/stop-button.png";
    stopHoverImagePath = ":/buttons/stop-button-hover.png";
    stopPressedImagePath = ":/buttons/stop-button-pressed.png";
}

bool StopEventWatcher::eventFilter(QObject * watched, QEvent * event)
{
    QToolButton * button = qobject_cast<QToolButton*>(watched);
    if (!button) {
        return false;
    }

    if (event->type() == QEvent::Enter) {
        // The push button is hovered by mouse
        qDebug()<<"Hovered";

        button->setIcon(QIcon(stopHoverImagePath));

        return false;
    }

    if (event->type() == QEvent::Leave || event->type() == QEvent::MouseButtonRelease){
        // The push button is not hovered by mouse or mouse is released
        qDebug()<<"Unhovered | Released";

        button->setIcon(QIcon(stopImagePath));

        return false;
    }

    if(event->type() == QEvent::MouseButtonPress){
        qDebug()<<"Pressed";

        button->setIcon(QIcon(stopPressedImagePath));

        return false;
    }

    return false;
}
