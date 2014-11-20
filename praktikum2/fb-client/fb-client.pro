######################################################################
# Automatically generated by qmake (3.0) Do. Nov. 13 09:00:23 2014
######################################################################


QT       += core network

QT       -= gui

QMAKE_CXXFLAGS += -g -fopenmp -DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=16 -fopenmp -DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=16 -fopenmp -DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=16 -I/usr/include/ImageMagick-6

LIBS += -lMagick++-6.Q16HDRI -lMagickWand-6.Q16HDRI -lMagickCore-6.Q16HDRI

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
