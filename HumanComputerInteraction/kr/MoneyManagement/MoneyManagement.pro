#-------------------------------------------------
#
# Project created by QtCreator 2015-08-02T15:39:53
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MoneyManagement
TEMPLATE = app


SOURCES += main.cpp\
        signinwindow.cpp \
    rescuepassworddialog.cpp \
    beforerescuepassworddialog.cpp \
    signupdialog.cpp \
    managementwindow.cpp \
    statisticwindow.cpp \
    moneyutils.cpp \
    simplecrypt.cpp \
    users.cpp \
    user.cpp \
    changepassworddialog.cpp \
    database.cpp \
    categoriesdialog.cpp \
    goalsdialog.cpp \
    goal.cpp \
    income.cpp \
    consumption.cpp \
    operation.cpp \
    piggybank.cpp \
    goals.cpp \
    templatesdialog.cpp \
    piechartwidget.cpp

HEADERS  += signinwindow.h \
    rescuepassworddialog.h \
    beforerescuepassworddialog.h \
    signupdialog.h \
    managementwindow.h \
    statisticwindow.h \
    moneyutils.h \
    simplecrypt.h \
    users.h \
    user.h \
    changepassworddialog.h \
    database.h \
    categoriesdialog.h \
    goalsdialog.h \
    goal.h \
    income.h \
    consumption.h \
    operation.h \
    piggybank.h \
    goals.h \
    templatesdialog.h \
    piechartwidget.h

FORMS    += signinwindow.ui \
    rescuepassworddialog.ui \
    beforerescuepassworddialog.ui \
    signupdialog.ui \
    managementwindow.ui \
    statisticwindow.ui \
    changepassworddialog.ui \
    categoriesdialog.ui \
    goalsdialog.ui \
    templatesdialog.ui

RESOURCES += \
    resources.qrc
