#ifndef PAINTER_H
#define PAINTER_H

#include <QFile>
#include "linux/fb.h"
#include "../fb-shared/framebuffer.h"

class Painter
{
public:
    Painter();
private:
    struct FrameData fb_data;
    QFile framebuffer_handler;
    struct fb_fix_screeninfo fixed_info;
    struct fb_var_screeninfo var_info;
    size_t screen_size;
    void init();
};

#endif // PAINTER_H
