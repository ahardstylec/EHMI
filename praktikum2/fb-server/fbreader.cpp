#include "fbreader.h"
#include <QDataStream>
#include <QByteArray>
#include <linux/fb.h>
#include <stropts.h>
#include <QDebug>
#include <string.h>

FBReader::FBReader(QObject *parent) :
    QObject(parent), framebuffer("/dev/fb0")
{
    framebuffer.open(QIODevice::ReadOnly);
    ioctl(framebuffer.handle(), FBIOGET_FSCREENINFO, & fixed_info);
    ioctl(framebuffer.handle(), FBIOGET_VSCREENINFO, & var_info);

    qDebug() << "fb smem size: " <<  qint64(fixed_info.smem_len);
    fb = framebuffer.map(0, qint64(fixed_info.smem_len));
}

FBReader::~FBReader() {
    framebuffer.unmap(fb);
    framebuffer.close();

}

void FBReader::getFrameData(FrameData & frameData) {
    frameData.bpp = var_info.bits_per_pixel;
    frameData.xres = var_info.xres;
    frameData.yres = var_info.yres;
}

QByteArray & FBReader::getFramebuffer() {
    frame = QByteArray((const char *) fb, fixed_info.smem_len);
    qDebug() << "frame size: " << frame.size();
    return frame;
}

quint32 FBReader::fbSize() {
    return fixed_info.smem_len;
}
