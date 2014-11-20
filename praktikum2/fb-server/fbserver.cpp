#include "fbserver.h"
#include <QObject>
#include <QTcpSocket>
#include <QNetworkInterface>
#include "fbreader.h"
#include "../fb-shared/framebuffer.h"

FBServer::FBServer(QObject * parent) : QTcpServer(parent) , server()
{
    connect(& server, SIGNAL (newConnection()), this, SLOT (sendFrame()));
}

FBServer::~FBServer() {
    qDebug("closing server");
    server.close();
}

void FBServer::start() {
    qDebug() << "starting server";
    bool success = server.listen(QHostAddress::AnyIPv4, 8081);
    if (!success) {
        qDebug("Error starting Server");
        qDebug() << this->errorString();
    }
}

void FBServer::sendFrame() {
    qDebug("sending");
    FrameData frame;
    reader.getFrameData(frame);

    QByteArray framebuffer = reader.getFramebuffer();
   // qDebug() << framebuffer;
    qDebug() << "size: " << framebuffer.size();


    qDebug() << "frame data size: " << sizeof(FrameData);
    QByteArray block;

    QDataStream out(&block, QIODevice::WriteOnly);


    out.setVersion(QDataStream::Qt_4_8);
    out << qint16(0);

    frame >> out;

    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));

    QTcpSocket * clientConnection = server.nextPendingConnection();
    qDebug() << "writable: " << clientConnection->isWritable();
    connect(clientConnection, SIGNAL(disconnected()), clientConnection, SLOT(deleteLater()));

    //clientConnection->write(reinterpret_cast<char *>(& frame));
    int bytesWritten = clientConnection->write(block);

    //clientConnection->flush();
    qDebug() << bytesWritten << " bytes written";


    QByteArray fbBlock;

    QDataStream fbOut(&fbBlock, QIODevice::WriteOnly);
    fbOut.setVersion(QDataStream::Qt_4_8);
    fbOut << quint32(0);

    fbOut << framebuffer;

    fbOut.device()->seek(0);
    fbOut << quint32(fbBlock.size() - sizeof(quint32));

    bytesWritten = clientConnection->write(fbBlock);
    //clientConnection->flush();
    qDebug() << bytesWritten << " bytes written";
     qDebug() << "fb size: " << framebuffer.size();

    clientConnection->disconnectFromHost();

}
