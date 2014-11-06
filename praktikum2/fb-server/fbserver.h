#ifndef FBSERVER_H
#define FBSERVER_H

#include <QObject>
#include <QTcpServer>

class FBServer : public QObject {
    Q_OBJECT
public:
    FBServer();
    virtual ~FBServer();
    void start();
private:
    QTcpServer server;
private slots:
    void sendFrame();
};

#endif // FBSERVER_H
