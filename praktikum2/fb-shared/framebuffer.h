#pragma once
#include <QByteArray>

struct FrameData {
    quint64 bytes;
    qint64 xres, yres, bpp;
};
