#include "repeateventwatcher.h"
#include<QDebug>
#include<QMediaPlaylist>

RepeatEventWatcher::RepeatEventWatcher(QObject *parent) : ButtonHoverWatcher(parent)
{
    repeatMode = QMediaPlaylist::Loop;
}

bool RepeatEventWatcher::eventFilter(QObject * watched, QEvent * event)
{
    QToolButton * button = qobject_cast<QToolButton*>(watched);
    if (!button) {
        return false;
    }

    if (event->type() == QEvent::MouseButtonRelease){
        // The push button is not hovered by mouse or mouse is released
        qDebug()<<"Released";

        if(repeatMode == QMediaPlaylist::Sequential)
        {
            qDebug()<<"Inside Sequential condition";
            button->setIcon(QIcon(":/buttons/repeat-loop-released.png"));
            button->setToolTip(tr("Repeat all"));
            repeatMode = QMediaPlaylist::Loop;
        }
        else if(repeatMode == QMediaPlaylist::Loop)
        {
            qDebug()<<"Inside loop condition";
            button->setIcon(QIcon(":/buttons/repeat-one-released.png"));
            button->setToolTip(tr("Repeat one"));
            repeatMode = QMediaPlaylist::CurrentItemInLoop;
        }
        else
        {
            qDebug()<<"Inside CurrentItemInLoop condition";
            button->setIcon(QIcon(":/buttons/repeat-no.png"));
            button->setToolTip(tr("No repeat"));
            repeatMode = QMediaPlaylist::Sequential;
        }

        return false;
    }

    if(event->type() == QEvent::MouseButtonPress){
        qDebug()<<"Pressed";

            button->setIcon(QIcon(":/buttons/repeat-no-pressed.png"));

        return false;
    }

    return false;
}

int RepeatEventWatcher::getRepeatMode()
{
    return repeatMode;
}
