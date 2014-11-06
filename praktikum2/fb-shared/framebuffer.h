#include <QByteArray>

struct FrameData {
    qint32 xres, yres, bpp;
    uchar * frame;
};
