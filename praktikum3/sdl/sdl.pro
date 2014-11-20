TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    painter.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    painter.h

