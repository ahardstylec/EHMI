#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <stropts.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <math.h>

void draw(char * fb, int x_offset, int y_offset, int bpp, int line_length) {
    int x = 50;
    int y = 50;
    int length = 100;
    int width = 20;

    srand(time(0));

    int color[4] = { 
        rand() % (int) pow(2, bpp / 4),
        rand() % (int) pow(2, bpp / 4),
        rand() % (int) pow(2, bpp / 4),
        0
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

}

int main() {
while (1) {
    int framebuffer_handler = open("/dev/fb0", O_RDWR);

    struct fb_fix_screeninfo fixed_info;

    ioctl(framebuffer_handler, FBIOGET_FSCREENINFO, &fixed_info);

    printf("line length: %u\n", fixed_info.line_length);
    printf("type: %u\n", fixed_info.type);

    struct fb_var_screeninfo var_info;

    ioctl(framebuffer_handler, FBIOGET_VSCREENINFO, & var_info);
    int screen_size = var_info.xres * var_info.yres * var_info.bits_per_pixel / 8;

    char * fb = mmap(0, fixed_info.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, framebuffer_handler, 0);

    if (MAP_FAILED == fb) {
        perror(strerror(errno));
        return 1;
    }

    draw(fb, var_info.xoffset, var_info.yoffset, var_info.bits_per_pixel, fixed_info.line_length);

    munmap(fb, screen_size);
    close(framebuffer_handler);

}
    return 0;
}
