#include "playpauseeventwatcher.h"
#include<QDebug>

PlayPauseEventWatcher::PlayPauseEventWatcher(QObject *parent) : ButtonHoverWatcher(parent), isPlaying(false)
{
    playImagePath = ":/buttons/play-button.png";
    playHoverImagePath = ":/buttons/play-button-hover.png";
    playPressedImagePath = ":/buttons/play-button-pressed.png";

    pauseImagePath = ":/buttons/pause-button.png";
    pauseHoverImagePath = ":/buttons/pause-button-hover.png";
    pausePressedImagePath = ":/buttons/pause-button-pressed.png";
}

bool PlayPauseEventWatcher::eventFilter(QObject * watched, QEvent * event)
{
    QToolButton * button = qobject_cast<QToolButton*>(watched);
    if (!button) {
        return false;
    }

    if (event->type() == QEvent::Enter) {
        // The push button is hovered by mouse
        qDebug()<<"Hovered";

        if(isPlaying)
            button->setIcon(QIcon(pauseHoverImagePath));
        else
            button->setIcon(QIcon(playHoverImagePath));

        return false;
    }

    if (event->type() == QEvent::MouseButtonRelease){
        // The push button is not hovered by mouse
        qDebug()<<"Released";

        if(isPlaying)
        {
            button->setIcon(QIcon(playImagePath));
            isPlaying = false;
        }
        else
        {
            button->setIcon(QIcon(pauseImagePath));
            isPlaying = true;
        }

        return false;
    }

    if(event->type() == QEvent::Leave)
    {
        qDebug()<<"Unhovered";

        if(isPlaying)
            button->setIcon(QIcon(pauseImagePath));
        else
            button->setIcon(QIcon(playImagePath));

        return false;
    }

    if(event->type() == QEvent::MouseButtonPress){
        qDebug()<<"Pressed";

        if(isPlaying)
            button->setIcon(QIcon(pausePressedImagePath));
        else
            button->setIcon(QIcon(playPressedImagePath));

        return false;
    }

    return false;
}

void PlayPauseEventWatcher::setIsPlaying(bool state)
{
    isPlaying = state;
}

bool PlayPauseEventWatcher::getIsPlaying()
{
    return isPlaying;
}
