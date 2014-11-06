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
    munmap(framebuffer, screen_size);
    framebuffer_handler.close();
}

void Painter::init(){
    framebuffer_handler.open(QIODevice::ReadWrite);

    ioctl(framebuffer_handler.handle(), FBIOGET_FSCREENINFO, &fixed_info);

    printf("line length: %u\n", fixed_info.line_length);
    printf("type: %u\n", fixed_info.type);

    ioctl(framebuffer_handler.handle(), FBIOGET_VSCREENINFO, & var_info);


    fb_data.bpp = var_info.bits_per_pixel;
    fb_data.xres = var_info.xoffset;
    fb_data.xres = var_info.xoffset;
    screen_size = this->get_screen_size(&fb_data);
    framebuffer =  framebuffer_handler.map(0, fixed_info.smem_len);

    if (MAP_FAILED == framebuffer) {
        throw strerror(errno);
    }

}

quint16 Painter::get_screen_size(FrameData * frame_data){
    return frame_data->xres * frame_data->yres * frame_data->bpp / 8;
}

void Painter::draw(QByteArray * frame){
    qDebug() << "draw start";
}

