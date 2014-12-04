#-------------------------------------------------
#
# Project created by QtCreator 2014-12-04T12:28:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = praktikum4
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        CanTraceParser.cpp

HEADERS  += mainwindow.h \
            CanTraceParser.h

FORMS    += mainwindow.ui

OTHER_FILES += data/CanTraceFile.txt

copydata.commands = $(COPY_DIR) $$PWD/data $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata
