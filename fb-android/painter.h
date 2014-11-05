#pragma once

#include <linux/fb.h>
#include <stdlib.h>

class Painter {
    public:
        Painter();
        ~Painter();
        void draw();
    private:
        char * fb;
        struct fb_fix_screeninfo fixed_info;
        struct fb_var_screeninfo var_info;
        size_t screen_size;
        int framebuffer_handler;

        int xres, yres, bpp;

};

