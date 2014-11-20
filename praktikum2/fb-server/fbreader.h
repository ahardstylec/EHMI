#ifndef FBREADER_H
#define FBREADER_H

#include <QObject>
#include <QFile>
#include <linux/fb.h>
#include "../fb-shared/framebuffer.h"

class FBReader : public QObject
{
    Q_OBJECT
public:
    explicit FBReader(QObject *parent = 0);

    ~FBReader();

    void getFrameData(FrameData & frameData);
    QByteArray & getFramebuffer();

    quint32 fbSize();

signals:

public slots:

private:
    QFile framebuffer;
    uchar * fb;
    QByteArray frame;
    char * fbRawData;


    struct fb_fix_screeninfo fixed_info;
    struct fb_var_screeninfo var_info;

};

#endif // FBREADER_H
