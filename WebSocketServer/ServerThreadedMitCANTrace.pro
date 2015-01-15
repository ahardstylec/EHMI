QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ServerThreadedMitCANTrace
TEMPLATE = app

SOURCES += \
    main.cpp \
    Log.cpp \
    ServerThreaded.cpp \
    SocketThread.cpp \
    QWsSocket.cpp \
    QWsServer.cpp \
    CanTraceParser.cpp

HEADERS += \
    Log.h \
    QWsServer.h \
    QWsSocket.h \
    ServerThreaded.h \
    SocketThread.h \
    CanTraceParser.h

OTHER_FILES += \
    data/Trace.txt



# if you are using Shadow build, you need to get the output folder
CONFIG(release, debug|release): DESTDIR = $$OUT_PWD/release
CONFIG(debug, debug|release): DESTDIR = $$OUT_PWD/debug

copydata.commands = $(COPY_DIR) $$PWD/data $(DESTDIR)
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

# if you are using normal build (non-shadow) that would have worked as well.
# CONFIG(release, debug|release): DESTDIR = release
# CONFIG(debug, debug|release): DESTDIR = debug

OtherFiles.path = $$DESTDIR
OtherFiles.files += $$files(*.txt)

INSTALLS += OtherFiles
