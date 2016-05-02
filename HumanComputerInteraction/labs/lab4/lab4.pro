#-------------------------------------------------
#
# Project created by QtCreator 2015-07-07T08:02:27
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab4
TEMPLATE = app


SOURCES += main.cpp\
    resquepasswdwindow.cpp \
    simplecrypt.cpp \
    database.cpp \
    mainwindow.cpp \
    users.cpp \
    tablewindow.cpp \
    changepasswordwindow.cpp \
    addnewuserwindow.cpp

HEADERS  += \
    resquepasswdwindow.h \
    simplecrypt.h \
    database.h \
    mainwindow.h \
    users.h \
    tablewindow.h \
    changepasswordwindow.h \
    addnewuserwindow.h

FORMS    += mainwindow.ui \
    resquepasswdwindow.ui \
    tablewindow.ui \
    changepasswordwindow.ui \
    addnewuserwindow.ui

RESOURCES += \
    resource.qrc
