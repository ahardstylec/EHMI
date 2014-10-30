#include <sys/mman.h>
#include <stropts.h>
#include <cstdio>
#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <ctime>
#include <random>
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

    fb = reinterpret_cast<char *>(mmap(0, fixed_info.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, framebuffer_handler, 0));

    if (MAP_FAILED == fb) {
        throw strerror(errno);
    }
}

void Painter::draw() {
    int x = 50;
    int y = 50;
    int length = 100;
    int width = 20;

    int bpp = var_info.bits_per_pixel;
    int x_offset = var_info.xoffset;
    int y_offset = var_info.yoffset;
    int line_length = fixed_info.line_length;

    std::default_random_engine generator;
    //    srand(time(0));

    std::uniform_int_distribution<int> distribution(0, pow(2, bpp / 4));
    int color[4] = { 
        distribution(generator),
        distribution(generator),
        distribution(generator),
        0
            /*
               rand() % (int) pow(2, bpp / 4),
               rand() % (int) pow(2, bpp / 4),
               rand() % (int) pow(2, bpp / 4),
               0
               */
    };

    for (int i = 0; i < width; i++) {
        long int pos = (x + x_offset) * (bpp/8) + (y + y_offset + i) * line_length;

        for (int j = 1; j < length; j++) {
            int increment = bpp / 8 / 4;
            char * pixel_pos = fb + pos;
            * pixel_pos = color[0]; // blue
            * (pixel_pos + (increment * 1)) = color[1]; // green
            * (pixel_pos + (increment * 2)) = color[2]; // red
            * (pixel_pos + (increment * 3)) = color[3]; // alpha

            pos += (int) (bpp / 8);
        }
    }

    sleep(3);
}

Painter::~Painter() {
    munmap(fb, screen_size);
    close(framebuffer_handler);
}
