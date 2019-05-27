#-------------------------------------------------
#
# Project created by QtCreator 2016-06-29T11:25:56
#
#-------------------------------------------------

QT       += core gui multimedia winextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimplePlayer
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    volumebutton.cpp \
    buttonhoverwatcher.cpp \
    playpauseeventwatcher.cpp \
    stopeventwatcher.cpp \
    previousnexteventwatcher.cpp \
    shuffleeventwatcher.cpp \
    repeateventwatcher.cpp \
    stylesheetsetter.cpp

HEADERS  += widget.h \
    volumebutton.h \
    buttonhoverwatcher.h \
    playpauseeventwatcher.h \
    stopeventwatcher.h \
    previousnexteventwatcher.h \
    shuffleeventwatcher.h \
    repeateventwatcher.h \
    stylesheetsetter.h

FORMS    += widget.ui

RESOURCES += buttons.qrc

win32:RC_ICONS += app_icon.ico

#target.path = H:\Workspaces\Qt Projects\Simple Player
#INSTALLS += target
