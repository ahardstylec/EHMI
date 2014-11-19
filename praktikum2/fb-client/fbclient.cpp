#include "fbclient.h"
#include "../fb-shared/framebuffer.h"
#include <QString>
#include <QtNetwork>
#include <QDebug>
#include <QObject>

FBClient::FBClient(QObject * parent) : QObject(parent)
{
    connect(&serverConnection, SIGNAL(connected()), this, SLOT(connectSuccess()));
    connect(&serverConnection, SIGNAL(readyRead()), this, SLOT(readFrame()));
    connect(&serverConnection, SIGNAL(disconnected()), this, SLOT(disconnect()));
    connect(&serverConnection, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(connectError()));
}

void FBClient::start(){
    this->connectToServer();
}


void FBClient::connectSuccess(){
    qDebug() << "connected to Server";
}


void FBClient::connectError(){
    qDebug() << "connect to Server failed: " << serverConnection.errorString();
    QTimer::singleShot(5000, this, SLOT(connectToServer()));
}

void FBClient::connectToServer(){
    //connect to Server
    qDebug() << "connecting to Server";
    serverConnection.abort();
    serverConnection.connectToHost("141.100.40.220", 8081);
}

void FBClient::disconnect(){
    qDebug() << "disconnected from Server";
}

void FBClient::readFrame(){
    qDebug() << "start readFrame";
    qint64 frame_data_size =sizeof(FrameData);
    qint16 blockSize;
    QByteArray tmp;
//    char* tmp;
    QDataStream in(&serverConnection);
    in.setVersion(QDataStream::Qt_4_8);

    if (serverConnection.bytesAvailable() < (int)sizeof(qint16))
        return;

    in >> blockSize;

    if (serverConnection.bytesAvailable() < blockSize){
        qDebug() << "less bytes send as expected, expect: " << frame_data_size << " bytes available: "<< serverConnection.bytesAvailable()<< "bytes";
        return;
    }

    qDebug() <<  "Server is sending FrameData";

    remote_fbdata << in;

    qDebug() << "readed Frame: ";
    qDebug() << "xres: " << remote_fbdata->xres;
    qDebug() << "yres: " << remote_fbdata->yres;
    qDebug() << "bpp: "  << remote_fbdata->bpp;


    blockSize= 0;

    if (serverConnection.bytesAvailable() < (int)sizeof(qint16))
        return;
    in >> blockSize;

    if (serverConnection.bytesAvailable() < blockSize){
        qDebug() << "less bytes send as expected, expect: " << frame_data_size << " bytes available: "<< serverConnection.bytesAvailable()<< "bytes";
        return;
    }
    qDebug() <<  "Server is sending Frame";

    in >> frame;

    painter->draw(frame);
    return;
}
