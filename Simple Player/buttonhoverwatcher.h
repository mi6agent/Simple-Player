#ifndef BUTTONHOVERWATCHER_H
#define BUTTONHOVERWATCHER_H

#include <QObject>
#include <QToolButton>
#include <QEvent>

class ButtonHoverWatcher : public QObject
{
    Q_OBJECT
public:
    explicit ButtonHoverWatcher(QObject * parent);
    bool eventFilter(QObject * watched, QEvent * event) Q_DECL_OVERRIDE = 0;

//private:
//    QString ImagePath;
//    QString hoverImagePath;
//    QString pressedImagePath;
};

#endif // BUTTONHOVERWATCHER_H
