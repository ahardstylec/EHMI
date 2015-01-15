// Example Code copied from https://github.com/ant-lafarge/QtWebsocket

#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H

#include <QThread>

#include "QWsSocket.h"

class SocketThread : public QThread
{
	Q_OBJECT

public:
	SocketThread( QWsSocket * wsSocket );
	~SocketThread();

	QWsSocket * socket;
	void run();

private slots:
	void processMessage( QString message );
	void sendMessage( QString message );
    void sendMessage( QByteArray message );
	void processPong( quint64 elapsedTime );
	void socketDisconnected();

signals:
	void messageReceived( QString frame );

private:
	
};

#endif // SOCKETTHREAD_H
