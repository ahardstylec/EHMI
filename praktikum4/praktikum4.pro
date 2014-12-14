#-------------------------------------------------
#
# Project created by QtCreator 2014-12-04T12:28:06
#
#-------------------------------------------------

QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = praktikum4
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        CanTraceParser.cpp \
    qsvgview.cpp \
    temperaturebar.cpp \
    steeringwheel.cpp \
    blinker.cpp \
    gaspedal.cpp

HEADERS  += mainwindow.h \
            CanTraceParser.h \
    qsvgview.h \
    temperaturebar.h \
    global.h \
    steeringwheel.h \
    blinker.h \
    gaspedal.h

FORMS    += mainwindow.ui

OTHER_FILES += data/CanTraceFile.txt

copydata.commands = $(COPY_DIR) $$PWD/data $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata


QMAKE_CXXFLAGS += -std=c++11
