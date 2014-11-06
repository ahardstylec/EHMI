#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QtNetwork>
#include <QString>
#include <Q_INT32>
//#include "../fb-shared/framebuffer.h"
#include "painter.h"
#include <QByteArray>

class FBClient : public QObject
{
public:
    FBClient(Painter *);

private:
    void drawFrame();
    QTcpSocket * qtsocket;
    QHostAddress *hostLineEdit;
    qint16 *portLineEdit;
    FrameData remote_fbdata;
    QByteArray frame;
    Painter * painter;
private slots:
    void readFrame();
};

#endif // CLIENT_H
