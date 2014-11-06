#include "painter.h"
#include <QFile>
#include <cerrno>
#include <cstdio>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stropts.h>
#include <linux/fb.h>
#include <cstring>

Painter::Painter() : framebuffer_handler("/dev/fb0")
{
    init();
}

Painter::~Painter(){
    munmap(fb_data.frame, screen_size);
    framebuffer_handler.close();
}

void Painter::init(){
    framebuffer_handler.open(QIODevice::ReadWrite);

    ioctl(framebuffer_handler.handle(), FBIOGET_FSCREENINFO, &fixed_info);

    printf("line length: %u\n", fixed_info.line_length);
    printf("type: %u\n", fixed_info.type);

    ioctl(framebuffer_handler.handle(), FBIOGET_VSCREENINFO, & var_info);
    screen_size = var_info.xres * var_info.yres * var_info.bits_per_pixel / 8;

    fb_data.bpp = var_info.bits_per_pixel;
    fb_data.xres = var_info.xoffset;
    fb_data.xres = var_info.xoffset;
    fb_data.frame =  framebuffer_handler.map(0, fixed_info.smem_len);

    if (MAP_FAILED == fb) {
        throw strerror(errno);
    }

}

void Painter::Draw(FrameData * frame){
    Qdebug() << "draw start";

}

