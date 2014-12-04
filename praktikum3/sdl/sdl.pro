TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lSDL2

SOURCES += main.cpp \
    painter.cpp \
    button.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    painter.h \
    button.h

