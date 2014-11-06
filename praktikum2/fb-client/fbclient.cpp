#include "fbclient.h"
#include "../fb-shared/framebuffer.h"
#include <QString>
#include <QtNetwork>
#include <QDebug>

FBClient::FBClient(Painter * painter)
{
    this.painter  = painter;

//    host = new QHostAddress("141.100.74.162");
//    port = new qint16(8081);
    qtsocket = new QTcpSocket(this);

    //connect to Server
    qtsocket->abort();
    qtsocket->connectToHost("141.100.74.162", 8081);

    // bind socket to qt
    connect(qtsocket, SIGNAL(readyRead()), this, SLOT(readFrame()));
}

void FBClient::readFrame(){
    qDebug() << "start readFrame";
    int blockSize = sizeof(FormData);
    char * tmp;
//    if (blockSize == 0) {
//        if (qtsocket->bytesAvailable() < (int)sizeof(quint16))
//            return;

//       qtsocket->read(tmp, (int)sizeof(quint16));
//       blockSize = *(quint16) tmp;
//    }
    // read FrameData from server
    if (qtsocket->bytesAvailable() < blockSize)
        return;
    qtsocket->read((FrameData) remote_fbdata);
    quint16 frame_size = painter->get_screen_size(remote_fbdata);

    qtsocket->read(frame, frame_size);

    qDebug() << "readed Frame: ";
    qDebug() << "read: " << blockSize << "Bytes";
    qDebug() << "xres: " << remote_fbdata.xres;
    qDebug() << "yres: " << remote_fbdata.yres;
    qDebug() << "bpp: "  << remote_fbdata.bpp;
    painter->draw(&frame);
    return;
}
