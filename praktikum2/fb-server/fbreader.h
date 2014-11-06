#ifndef FBREADER_H
#define FBREADER_H

#include <QObject>
#include <QFile>
#include "../fb-shared/framebuffer.h"

class FBReader : public QObject
{
    Q_OBJECT
public:
    explicit FBReader(QObject *parent = 0);

    ~FBReader();

    void getFrameData(FrameData & frameData);
    void getFramebuffer(QByteArray &framebuffer);
signals:

public slots:

private:
    QFile framebuffer;
    uchar * fb;
    QByteArray frame;

};

#endif // FBREADER_H
