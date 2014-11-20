#include "fbclient.h"
#include "../fb-shared/framebuffer.h"
#include <QString>
#include <QtNetwork>
#include <QDebug>
#include <QObject>
#include <iostream>

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
    serverConnection.connectToHost("141.100.74.138", 8081);
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

    qDebug() <<  "Server is sending FrameData " << blockSize;

    remote_fbdata << in;
    qDebug() << "readed Frame: ";
    qDebug() << "xres: " << remote_fbdata.xres;
    qDebug() << "yres: " << remote_fbdata.yres;
    qDebug() << "bpp: "  << remote_fbdata.bpp;

    quint32 blocksize_new= 0;
    if (serverConnection.bytesAvailable() < (int)sizeof(quint32))
        return;
    in >> blocksize_new;


    qDebug() <<  "Server is sending Frame with" << blocksize_new << "bytes";
    quint32 bytes_read= 0;
    QByteArray read_tmp_array;
    int i =0;
    while(bytes_read < blocksize_new){
       serverConnection.waitForReadyRead();
       read_tmp_array  = serverConnection.readAll();
       frame+read_tmp_array;
       bytes_read+=read_tmp_array.size();
       if(i%10 == 0){
        std::cout << "\rrecieved data bytes read: " << bytes_read/1024 << " KB \t\t\t";
       }
       i++;
    }

    std::cout << std::endl;

    painter->draw(&frame, &remote_fbdata);
    serverConnection.disconnectFromHost();
    return;
}
