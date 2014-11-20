TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CFLAGS += -Weverything -mtune=native -march=native -fstack-protector-all -std=c11

SOURCES += main.c \
    simpleHMI.c \
    shmi_button.c \
    shmi_shader.c

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    simpleHMI.h \
    shmi_button.h \
    shmi_shader.h

LIBS += -lglfw -lGLEW -lGL

OTHER_FILES += \
    button_vertex.glfw
