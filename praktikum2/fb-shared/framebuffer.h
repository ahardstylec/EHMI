#pragma once
#include <QByteArray>

struct FrameData {
    quint32 bytes;
    qint64 xres, yres, bpp;
};
