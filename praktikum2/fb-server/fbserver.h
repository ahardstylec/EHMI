#ifndef FBSERVER_H
#define FBSERVER_H
#include "fbreader.h"

#include <QObject>
#include <QTcpServer>

class FBServer : public QTcpServer {
    Q_OBJECT
public:
    explicit FBServer(QObject * parent);
    virtual ~FBServer();
    void start();
private:
    QTcpServer server;
     FBReader reader;
private slots:
    void sendFrame();
};

#endif // FBSERVER_H
