#-------------------------------------------------
#
# Project created by QtCreator 2018-03-08T14:24:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SchoolSport
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    loginwindow.cpp \
    adminwindow.cpp \
    normalwindow.cpp \
    dataprocess.cpp \
    entrywindow.cpp \
    algorithm/fuck.cpp \
    adminwindow.cpp \
    dataprocess.cpp \
    entrywindow.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    normalwindow.cpp \
    algorithm/attender.cpp \
    algorithm/calSportThing.cpp \
    algorithm/fuck.cpp \
    algorithm/SportArithmetic.cpp \
    algorithm/sportThing.cpp \
    algorithm/TEXTMain.cpp \
    querywindow.cpp

HEADERS += \
        mainwindow.h \
    loginwindow.h \
    adminwindow.h \
    normalwindow.h \
    dataprocess.h \
    entrywindow.h \
    algorithm/fuck.h \
    adminwindow.h \
    dataprocess.h \
    entrywindow.h \
    loginwindow.h \
    mainwindow.h \
    normalwindow.h \
    algorithm/attender.h \
    algorithm/calSportThing.h \
    algorithm/fuck.h \
    algorithm/SportArithmetic.h \
    algorithm/sportThing.h \
    algorithm/Top.h \
    querywindow.h

FORMS += \
        mainwindow.ui \
    loginwindow.ui \
    adminwindow.ui \
    normalwindow.ui \
    entrywindow.ui \
    querywindow.ui
