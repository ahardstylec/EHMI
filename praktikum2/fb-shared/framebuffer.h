#pragma once
#include <QDataStream>

class FrameData {
public:
    inline FrameData() : xres(0), yres(0), bpp(0){

    }
    inline FrameData(quint64 xres, quint64 yres, quint64 bpp) : xres(xres), yres(yres), bpp(bpp) {}

    quint64 xres, yres, bpp;

    inline FrameData & operator<< (QDataStream & in) {
        in  >> xres >>  yres >> bpp;
        return * this;
    }

    inline FrameData & operator>>(QDataStream & out) {
        out << xres << yres << bpp;
        return * this;
    }

    inline friend QDataStream & operator<<(QDataStream & out, const FrameData * fd) {
        out << fd->xres << fd->yres << fd->bpp;
        return out;
    }

    inline friend QDataStream & operator>>(QDataStream & in, FrameData * fd) {
        in >> fd->xres >> fd->yres >> fd->bpp;
        return in;
    }
};
