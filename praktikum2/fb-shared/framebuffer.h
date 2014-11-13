#pragma once
#include <QDataStream>

struct FrameData {
    quint64 xres, yres, bpp;

    inline FrameData & operator<< (QDataStream & in) {
        in  >> xres >>  yres >> bpp;
        return * this;
    }

    inline FrameData & operator>>(QDataStream & out) {
        out << xres << yres << bpp;
        return * this;
    }
};
