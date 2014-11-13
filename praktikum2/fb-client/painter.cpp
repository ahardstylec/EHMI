#include "painter.h"
#include <QFile>
#include <QDebug>
#include <cerrno>
#include <cstdio>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stropts.h>
#include <linux/fb.h>
#include <cstring>
#include <QByteArray>

Painter::Painter() : framebuffer_handler("/dev/fb0")
{
    init();
}

Painter::~Painter(){
    munmap(framebuffer, fb_data.bytes);
    framebuffer_handler.close();
}

void Painter::init(){
//    qDebug() << "init painter";
    framebuffer_handler.open(QIODevice::ReadWrite);

    ioctl(framebuffer_handler.handle(), FBIOGET_FSCREENINFO, & fixed_info);
    ioctl(framebuffer_handler.handle(), FBIOGET_VSCREENINFO, & var_info);

    framebuffer =  framebuffer_handler.map(0, fixed_info.smem_len);

    fb_data.bpp = var_info.bits_per_pixel;
    fb_data.xres = var_info.xoffset;
    fb_data.xres = var_info.xoffset;
    fb_data.bytes = fixed_info.smem_len;

    if (MAP_FAILED == framebuffer) {
        throw strerror(errno);
    }

}

void Painter::draw(QByteArray * frame){
    qDebug() << "draw start";
}

