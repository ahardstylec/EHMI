#ifndef PAINTER_H
#define PAINTER_H

#include <QFile>
#include "linux/fb.h"
#include "../fb-shared/framebuffer.h"
#include <QByteArray>

class Painter
{
public:
    Painter();
    ~Painter();
    void draw(QByteArray *);
private:
    FrameData fb_data;
    uchar  * framebuffer;
    QByteArray framebuffer_array;
    QFile framebuffer_handler;
    struct fb_fix_screeninfo fixed_info;
    struct fb_var_screeninfo var_info;
    void init();
};

#endif // PAINTER_H
