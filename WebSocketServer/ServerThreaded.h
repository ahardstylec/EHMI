// Example Code copied from https://github.com/ant-lafarge/QtWebsocket

#ifndef SERVERTHREADED_H
#define SERVERTHREADED_H

#include <QtCore>
#include <QtNetwork>

#include "QWsServer.h"
#include "QWsSocket.h"
#include "SocketThread.h"

class ServerThreaded : public QObject
{
	Q_OBJECT

public:
	ServerThreaded();
	~ServerThreaded();

public slots:
	void processNewConnection();
	void displayMessage( QString message );

    void SendBroadcastMessage( QString _Message );
    void SendBroadcastMessage( QByteArray message );

signals:
    void broadcastMessage( QString message );
    void broadcastMessage( QByteArray message );

private:
	QWsServer * server;

};

#endif // SERVERTHREADED_H
