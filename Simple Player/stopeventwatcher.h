#ifndef STOPEVENTWATCHER_H
#define STOPEVENTWATCHER_H

#include"buttonhoverwatcher.h"

class StopEventWatcher : public ButtonHoverWatcher
{
public:
    explicit StopEventWatcher(QObject * parent);
    bool eventFilter(QObject * watched, QEvent * event);

private:
    QString stopImagePath;
    QString stopHoverImagePath;
    QString stopPressedImagePath;
};

#endif // STOPEVENTWATCHER_H
