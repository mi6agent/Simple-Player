#include "previousnexteventwatcher.h"
#include<QDebug>

PreviousNextEventWatcher::PreviousNextEventWatcher(QObject *parent,
                                                   QString imagePath, QString hoverImagePath, QString pressedImagePath)
    : ButtonHoverWatcher(parent)
{
    this->imagePath = imagePath;
    this->hoverImagePath = hoverImagePath;
    this->pressedImagePath = pressedImagePath;
}

bool PreviousNextEventWatcher::eventFilter(QObject * watched, QEvent * event)
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

    if (event->type() == QEvent::Leave || event->type() == QEvent::MouseButtonRelease){
        // The push button is not hovered by mouse or Mouse is released
        qDebug()<<"Unhovered | Released";

        button->setIcon(QIcon(imagePath));

        return false;
    }

    if(event->type() == QEvent::MouseButtonPress){
        qDebug()<<"Pressed";

        button->setIcon(QIcon(pressedImagePath));

        return false;
    }

    return false;
}
