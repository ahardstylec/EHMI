#-------------------------------------------------
#
# Project created by QtCreator 2014-11-06T11:35:02
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = fb-server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    fbserver.cpp \
    fbreader.cpp

HEADERS += \
    ../fb-shared/framebuffer.h \
    fbserver.h \
    fbreader.h

QMAKE_CFLAGS += -O2 -mtune=native -flto
