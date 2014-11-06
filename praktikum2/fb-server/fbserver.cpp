#include "fbserver.h"
#include <QObject>
#include <QTcpSocket>
#include <QNetworkInterface>
#include "fbreader.h"
#include "../fb-shared/framebuffer.h"

FBServer::FBServer()
{
    connect(& server, SIGNAL (newConnection()), this, SLOT (sendFrame()));
}

FBServer::~FBServer() {
    server.close();
}

void FBServer::start() {
    server.listen(QHostAddress::Any, 8081);


}

void FBServer::sendFrame() {
    FBReader reader;
    FrameData frame;
    reader.getFrameData(frame);

    QTcpSocket * clientConnection = server.nextPendingConnection();
    connect(clientConnection, SIGNAL(disconnected()), clientConnection, SLOT(deleteLater()));

    clientConnection->write(frame);

}
