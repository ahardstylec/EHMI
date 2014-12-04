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
//    munmap(framebuffer, fixed_info.smem_len);

    framebuffer_handler.unmap(framebuffer);
    framebuffer_handler.close();
}

void Painter::init(){
//    qDebug() << "init painter";
    framebuffer_handler.open(QIODevice::ReadWrite);

    ioctl(framebuffer_handler.handle(), FBIOGET_FSCREENINFO, & fixed_info);
    ioctl(framebuffer_handler.handle(), FBIOGET_VSCREENINFO, & var_info);

    framebuffer = framebuffer_handler.map(0, fixed_info.smem_len);
    framebuffer_array.resize(fixed_info.smem_len);
    fb_data.bpp = var_info.bits_per_pixel;
    fb_data.xres = var_info.xres;
    fb_data.yres = var_info.yres;

    qDebug() << "xres: " << fb_data.xres;
    qDebug() << "yres: " << fb_data.yres;
    qDebug() << "bpp: "  << fb_data.bpp;

    if (MAP_FAILED == framebuffer) {
        throw strerror(errno);
    }

}
const unsigned int data_width = 32/8/4;
struct Pixel {
   uchar blue[data_width], green[data_width], red[data_width], alpha[data_width];
};

void Painter::draw(QByteArray * frame, FrameData * frame_data){
     qDebug() << "draw start";
     qDebug() << "recieved frame size" << frame->size();
     system("clear");
     typedef Pixel pixelarray[fb_data.yres][fb_data.xres];
     typedef Pixel remote_pixelarray[frame_data->yres][frame_data->xres];
     pixelarray & pixel_framebuffer = *reinterpret_cast<pixelarray *>(framebuffer);
     remote_pixelarray & remote_framebuffer = *reinterpret_cast<remote_pixelarray *>(frame->data());

     for (int row = 0; row < fb_data.yres; row++) {
         for (int column = 0; column < fb_data.xres; column++) {
             pixel_framebuffer[row][column] = remote_framebuffer[row][column];
         }
     }

     qDebug() << "draw end";
}

