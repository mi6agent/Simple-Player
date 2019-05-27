#ifndef PREVIOUSNEXTEVENTWATCHER_H
#define PREVIOUSNEXTEVENTWATCHER_H

#include"buttonhoverwatcher.h"

class PreviousNextEventWatcher : public ButtonHoverWatcher
{
public:
    explicit PreviousNextEventWatcher(QObject * parent, QString, QString, QString);
    bool eventFilter(QObject * watched, QEvent * event);

private:
    QString imagePath;
    QString hoverImagePath;
    QString pressedImagePath;
};

#endif // PREVIOUSNEXTEVENTWATCHER_H
