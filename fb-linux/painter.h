#pragma once

#include <linux/fb.h>

class Painter {
    public:
        Painter();
        ~Painter();
        void init();
        void draw();
    private:
        char * fb;
        struct fb_fix_screeninfo fixed_info;
        struct fb_var_screeninfo var_info;
        size_t screen_size;
};

