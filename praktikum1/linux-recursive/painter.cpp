#include <sys/mman.h>
#include <stropts.h>
#include <cstdio>
#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <vector>
#include <array>
#include <unistd.h>
#include <vector>
#include "painter.h"
#include <Magick++.h>
// #include "core/core.hpp"
// #include "imgproc/imgproc.hpp"
// #include "highgui/highgui.hpp"


using namespace std;

Painter::Painter() {
    init();
}

void Painter::init() {
    framebuffer_handler = open("/dev/fb0", O_RDWR);


    ioctl(framebuffer_handler, FBIOGET_FSCREENINFO, &fixed_info);
    printf("line length: %u\n", fixed_info.line_length);
    printf("type: %u\n", fixed_info.type);

    ioctl(framebuffer_handler, FBIOGET_VSCREENINFO, & var_info);
    screen_size = var_info.xres * var_info.yres * var_info.bits_per_pixel / 8;
    printf("resolution: %dx%d\n", var_info.xres, var_info.yres);
    printf("bpp: %d\n", var_info.bits_per_pixel);

    fb = reinterpret_cast<char *>(mmap(0, fixed_info.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, framebuffer_handler, 0));

    if (MAP_FAILED == fb) {
        throw strerror(errno);
    }
    fbTmp = new char[fixed_info.smem_len];
}

void Painter::draw() {
    // take screenshot
   memcpy(fbTmp, fb, fixed_info.smem_len);

   char * fbTmp_two = new char[fixed_info.smem_len];

   const unsigned int data_width = 32 / 8 / 4;
   struct Pixel {
       char blue[data_width], green[data_width], red[data_width], alpha[data_width];
   };
    
   unsigned int height = var_info.yres;
   unsigned int width = var_info.xres;

   unsigned int scaled_msize = width*height/2*var_info.bits_per_pixel / 8;

   char * scaledTmp = new char[scaled_msize];

   Pixel * scaled_screenshot = reinterpret_cast<Pixel *> (scaledTmp);
   Pixel * screenshot = reinterpret_cast<Pixel *> (fbTmp);
   Pixel * framebuffer = reinterpret_cast<Pixel *> (fb);
   
   // Magick::Image image;
   // image.read(width, height, "BGRA", Magick::CharPixel, fbTmp);
   // image.sample(Magick::Geometry(width/2, height/2));
   // image.write(0,0, width/2, height/2, "BGRA", Magick::CharPixel, scaled_screenshot);

   unsigned int startPoint = width* (height/4) - width + (width / 4);
   printf("start point @ %d\n", startPoint);
   fflush(stdout);


   unsigned int x_offset = width/4;
   unsigned int y_offset = height/4;

    // Magick::Pixels view(image);
    // Magick::PixelPacket * pixelpacket = view.get(0,0, image.columns(), image.rows());
    // for (int i = 0; i < image.rows(); i++) {
    //     long int pos = x_offset + (y_offset + i) * width;

    //     for (int j = 0; j < image.columns(); j++) {
    //         struct Pixel pixel;
    //         *pixel.blue = pixelpacket->blue;
    //         *pixel.green = pixelpacket->green;
    //         *pixel.red = pixelpacket->red;
    //         *pixel.alpha = pixelpacket->opacity;
    //         framebuffer[pos] = pixel; // screenshot[image.columns()+i*j];
    //         pos ++;
    //         *pixelpacket++;
    //     }
    // }
   unsigned int y= 0;
   for (unsigned int lineStart = startPoint; lineStart < 3* (height*width-width) / 4; lineStart += width) {

       for (unsigned int offset = 0; offset < width/2; offset++) {
          unsigned int srcLineStart = 2*(lineStart- startPoint);
          unsigned int srcOffset = offset*2;
          framebuffer[lineStart + offset] =  screenshot[srcLineStart + srcOffset];
        }
        y++;
   }
   //sleep(3);
}

void Painter::make_screenshot(){
  Magick::Image image;
  image.read(1280, 800, "BGRA", Magick::CharPixel, fb);
  image.write("screenshot.jpg");
}

Painter::~Painter() {
    munmap(fb, screen_size);
    close(framebuffer_handler);
    delete fbTmp;
}
