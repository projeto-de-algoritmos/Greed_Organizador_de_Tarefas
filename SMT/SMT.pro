TEMPLATE = app
TARGET = SMT
INCLUDEPATH += .

QT = core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++17

SOURCES += \
        main.cpp \
        window.cpp

HEADERS += \
        window.h \
    job.h
