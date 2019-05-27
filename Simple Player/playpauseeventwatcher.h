#ifndef PLAYPAUSEEVENTWATCHER_H
#define PLAYPAUSEEVENTWATCHER_H

#include"buttonhoverwatcher.h"

class PlayPauseEventWatcher : public ButtonHoverWatcher
{
public:
    explicit PlayPauseEventWatcher(QObject * parent);
    bool eventFilter(QObject * watched, QEvent * event);

    void setIsPlaying(bool);
    bool getIsPlaying();

private:
    QString playImagePath;
    QString playHoverImagePath;
    QString playPressedImagePath;

    QString pauseImagePath;
    QString pauseHoverImagePath;
    QString pausePressedImagePath;

    bool isPlaying;
};

#endif // PLAYPAUSEEVENTWATCHER_H
