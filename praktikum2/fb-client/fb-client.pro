#-------------------------------------------------
#
# Project created by QtCreator 2014-11-06T11:33:05
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = fb-client
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    painter.cpp \
    fbclient.cpp

HEADERS += \
    painter.h \
    fbclient.h \
    ../fb-shared/framebuffer.h
