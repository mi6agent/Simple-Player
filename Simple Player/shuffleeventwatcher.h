#ifndef SHUFFLEEVENTWATCHER_H
#define SHUFFLEEVENTWATCHER_H

#include"buttonhoverwatcher.h"

class ShuffleEventWatcher : public ButtonHoverWatcher
{
public:
    explicit ShuffleEventWatcher(QObject * parent);
    bool eventFilter(QObject * watched, QEvent * event);

    bool statusOn();

private:
    bool isOn;
    //bool isPressed;

    QString imagePath;
    QString hoverImagePath;
    QString pressedImagePath;
    QString releasedImagePath;
};

#endif // SHUFFLEEVENTWATCHER_H
