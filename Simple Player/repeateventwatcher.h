#ifndef REPEATEVENTWATCHER_H
#define REPEATEVENTWATCHER_H

#include"buttonhoverwatcher.h"

class RepeatEventWatcher : public ButtonHoverWatcher
{
public:
    explicit RepeatEventWatcher(QObject * parent);
    bool eventFilter(QObject * watched, QEvent * event);

    int getRepeatMode();

private:
    int repeatMode;
};

#endif // REPEATEVENTWATCHER_H
