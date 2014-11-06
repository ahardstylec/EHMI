#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QtNetwork>
#include "../fb-shared/framebuffer.h"
#include "painter.h"

class FBClient : public QObject
{
public:
    FBClient(painter *);

private:
    void drawFrame();
    QTcpSocket * qtsocket;
    QLineEdit *hostLineEdit;
    QLineEdit *portLineEdit;
    struct FrameData frame;
    Painter * painter;
private slots:
    void readFrame();
};

#endif // CLIENT_H
