#pragma once

#include <linux/fb.h>

class Painter {
    public:
        Painter();
        ~Painter();
        void draw();
        void make_screenshot();
    private:
        char * fb;
        struct fb_fix_screeninfo fixed_info;
        struct fb_var_screeninfo var_info;
        unsigned int screen_size;
        int framebuffer_handler;
        char * fbTmp;

        void init();
};

