#include <sys/mman.h>
#include <stropts.h>
#include <cstdio>
#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <vector>
#include <array>
#include <unistd.h>
#include "painter.h"

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

   const unsigned int data_width = 32 / 8 / 4;
   struct Pixel {
       char blue[data_width], green[data_width], red[data_width], alpha[data_width];

   };
    
   Pixel * screenshot = reinterpret_cast<Pixel *> (fbTmp);
   Pixel * framebuffer = reinterpret_cast<Pixel *> (fb);

   unsigned int height = var_info.yres;
   unsigned int width = var_info.xres;

   unsigned int startPoint = width* (height/4) - width + (width / 4);
   printf("start point @ %d\n", startPoint);
   fflush(stdout);


   for (unsigned int lineStart = startPoint; lineStart < 3* (height*width-width) / 4; lineStart += width) {
       for (unsigned int offset = 0; offset < width/2; offset++) {
           struct Pixel pixel;
           (*pixel.red) = 0xff;
           (*pixel.alpha) = 0x0;
           unsigned int srcLineStart = 2 * (lineStart - startPoint);
           unsigned int srcOffset = offset * 2;
           framebuffer[lineStart + offset] =  screenshot[srcLineStart + srcOffset];
       }
   }
   
   //sleep(3);
}

Painter::~Painter() {
    munmap(fb, screen_size);
    close(framebuffer_handler);
    delete fbTmp;
}
