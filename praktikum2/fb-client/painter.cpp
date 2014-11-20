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
#include <Magick++.h>


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
    fb_data.xres = var_info.xoffset;
    fb_data.xres = var_info.xoffset;


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
     Pixel * pixel_framebuffer = reinterpret_cast<Pixel *>(framebuffer);
     Pixel * remote_framebuffer = reinterpret_cast<Pixel *>(frame->data());
//     Magick::Image image;
//     qDebug() << "read image start";
//     image.read(frame_data->xres, frame_data->yres, "BGRA", Magick::CharPixel, frame->data());
//     qDebug() << "read image end start";
//     Magick::Geometry new_size(fb_data.xres, fb_data.yres);
//     new_size.aspect(true);
//     image.sample(new_size);
//     Magick::Pixels view(image);
//     Magick::PixelPacket * pixelpacket = view.get(0,0, image.columns(), image.rows());

     qDebug() << "draw fb " << fb_data.xres << "x" << frame_data->yres;
     for (int i = 0; i < fb_data.xres; i++) {
         long int pos = i * fb_data.xres;
         for (int j = 0; j < fb_data.yres; j++) {
             struct Pixel pixel;
             *pixel.blue = (uchar)(0xff);// pixelpacket->blue;
             *pixel.green = (uchar)(0xff); //pixelpacket->green;
             *pixel.red = (uchar)(0xff); //pixelpacket->red;
             *pixel.alpha = (uchar)(0xff); //pixelpacket->opacity;
             pixel_framebuffer[pos] = pixel;//remote_framebuffer[pos];
             pos ++;
//             *pixelpacket++;
         }
     }
     qDebug() << "draw end";
}

