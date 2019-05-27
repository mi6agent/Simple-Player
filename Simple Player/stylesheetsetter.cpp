#include "stylesheetsetter.h"

void StyleSheetSetter::setMainWidgetStylesheet(QWidget *mainWidget)
{
    mainWidget->setStyleSheet("QToolTip\
                 {\
                  border: 1px solid black;\
                  padding: 1px;\
                  border-radius: 3px;\
                  opacity: 100;\
                  color: #fffafb\
                 }\
                  \
                 QWidget\
                 {\
                    color: #b1b1b1;\
                    background-color: #323232;\
                 }\
                  \
                 QWidget:item:hover\
                 {\
                     background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #ca0619);\
                     color: #000000;\
                 }\
                 \
                 QWidget:item:selected\
                 {\
                     background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\
                 }\
                  \
                 QWidget:disabled\
                 {\
                     color: #404040;\
                     background-color: #323232;\
                 }\
                 \
                 QAbstractItemView\
                 {\
                     background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #4d4d4d, stop: 0.1 #646464, stop: 1 #5d5d5d);\
                 }\
                 \
                 QWidget:focus\
                 {\
                     /*border: 2px solid QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);*/\
                 }\
                 \
                 QScrollBar:horizontal {\
                      border: 1px solid #222222;\
                      background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0.0 #121212, stop: 0.2 #282828, stop: 1 #484848);\
                      height: 7px;\
                      margin: 0px 16px 0 16px;\
                 }\
                 \
                 QScrollBar::handle:horizontal\
                 {\
                       background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #ffa02f, stop: 0.5 #d7801a, stop: 1 #ffa02f);\
                       min-height: 20px;\
                       border-radius: 2px;\
                 }\
                 \
                 QScrollBar::add-line:horizontal {\
                       border: 1px solid #1b1b19;\
                       border-radius: 2px;\
                       background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #ffa02f, stop: 1 #d7801a);\
                       width: 14px;\
                       subcontrol-position: right;\
                       subcontrol-origin: margin;\
                 }\
                 \
                 QScrollBar::sub-line:horizontal {\
                       border: 1px solid #1b1b19;\
                       border-radius: 2px;\
                       background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #ffa02f, stop: 1 #d7801a);\
                       width: 14px;\
                      subcontrol-position: left;\
                      subcontrol-origin: margin;\
                 }\
                 \
                 QScrollBar::right-arrow:horizontal, QScrollBar::left-arrow:horizontal\
                 {\
                       border: 1px solid black;\
                       width: 1px;\
                       height: 1px;\
                       background: white;\
                 }\
                 \
                 QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal\
                 {\
                       background: none;\
                 }\
                 \
                 QScrollBar:vertical\
                 {\
                       background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0.0 #121212, stop: 0.2 #282828, stop: 1 #484848);\
                       width: 7px;\
                       margin: 16px 0 16px 0;\
                       border: 1px solid #222222;\
                 }\
                 \
                 QScrollBar::handle:vertical\
                 {\
                       background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 0.5 #d7801a, stop: 1 #ffa02f);\
                       min-height: 20px;\
                       border-radius: 2px;\
                 }\
                 \
                 QScrollBar::add-line:vertical\
                 {\
                       border: 1px solid #1b1b19;\
                       border-radius: 2px;\
                       background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\
                       height: 14px;\
                       subcontrol-position: bottom;\
                       subcontrol-origin: margin;\
                 }\
                 \
                 QScrollBar::sub-line:vertical\
                 {\
                       border: 1px solid #1b1b19;\
                       border-radius: 2px;\
                       background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #d7801a, stop: 1 #ffa02f);\
                       height: 14px;\
                       subcontrol-position: top;\
                       subcontrol-origin: margin;\
                 }\
                 \
                 QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical\
                 {\
                       border: 1px solid black;\
                       width: 1px;\
                       height: 1px;\
                       background: white;\
                 }\
                 \
                 QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical\
                 {\
                       background: none;\
                 }\
                 \
                 QHeaderView::section\
                 {\
                     background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #616161, stop: 0.5 #505050, stop: 0.6 #434343, stop:1 #656565);\
                     color: white;\
                     padding-left: 4px;\
                     border: 1px solid #6c6c6c;\
                 }\
                 \
                 QMainWindow::separator\
                 {\
                     background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #161616, stop: 0.5 #151515, stop: 0.6 #212121, stop:1 #343434);\
                     color: white;\
                     padding-left: 4px;\
                     border: 1px solid #4c4c4c;\
                     spacing: 3px; /* spacing between items in the tool bar */\
                 }\
                 \
                 QMainWindow::separator:hover\
                 {\
                     background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #d7801a, stop:0.5 #b56c17 stop:1 #ffa02f);\
                     color: white;\
                     padding-left: 4px;\
                     border: 1px solid #6c6c6c;\
                     spacing: 3px; /* spacing between items in the tool bar */\
                 }\
                 \
                ");
}

void StyleSheetSetter::setPlayListViewStyleSheet(QTableView *playListView)
{
    playListView->setStyleSheet("QTableView{\
                                border: 1px solid #76797C;\
                                   gridline-color: #31363b;\
                                   background-color: #232629;\
                               }\
                               \
                               QWidget::item:alternate {\
                                   background: #666;\
                               }\
                               \
                               QTableView, QHeaderView\
                               {\
                                   border-radius: 0px;\
                               }\
                               ");
}

void StyleSheetSetter::setHorizontalSliderStyleSheet(QSlider *horizontalSlider)
{
    horizontalSlider->setStyleSheet("QSlider {\
                                    background: rgb(170, 170, 170);\
                                    padding: 2px;\
                                    height: 40px;\
                                }\
                                \
                                QSlider::groove:horizontal {\
                                    subcontrol-origin: content;\
                                    background: rgb(76, 76, 76);\
                                    \
                                    /* the groove expands to the size of the slider by default. \
                                    by giving it a height, it has a fixed size */\
                                    height: 20px;\
                                }\
                                \
                                QSlider::handle:horizontal {\
                                    background-color: rgb(50, 50, 50);\
                                    width: 40px;\
                                    border-radius: 20px;\
                                    \
                                    /* handle is placed by default on the contents rect of the groove. \
                                    Expand outside the groove */\
                                    margin: -10px 0;\
                                }\
                                \
                                QSlider::sub-page:horizontal {\
                                    background: #999;\
                                    margin: 5px;\
                                    border-radius: 5px;\
                                }\
                                \
                                QSlider::add-page:horizontal {\
                                    background: #666;\
                                    margin: 5px;\
                                    border-radius: 5px;\
                                }");
}
