#include "fbreader.h"
#include <QDataStream>
#include <QByteArray>

FBReader::FBReader(QObject *parent) :
    QObject(parent), framebuffer("/dev/fb0")
{
    framebuffer.open(QIODevice::ReadOnly);
    fb = framebuffer.map(0,framebuffer.size());
}

FBReader::~FBReader() {
    framebuffer.unmap(fb);
    framebuffer.close();
}

void FBReader::getFrameData(FrameData & frameData) {
    struct fb_fix_screeninfo fixed_info;
    struct fb_var_screeninfo var_info;

    ioctl(fb, FBIOGET_FSCREENINFO, & fixed_info);
    ioctl(fb, FBIOGET_VSCREENINFO, & var_info);

    frameData.bpp = var_info.bits_per_pixel;
    frameData.xres = var_info.xres;
    frameData.yres = var_info.yres;
}

QBytearray & FBReader::getFramebuffer() {
    frame.fromRawData(fb, framebuffer.size());
    return frame;
}
