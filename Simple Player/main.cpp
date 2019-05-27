#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("MusiX");
    w.setAttribute(Qt::WA_AlwaysShowToolTips, true);
    w.show();

    return a.exec();
}
