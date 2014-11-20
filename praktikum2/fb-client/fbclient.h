#ifndef FBCLIENT_H
#define FBCLIENT_H

#include <QTcpSocket>
#include <QtNetwork>
#include <QString>
#include <QObject>
#include "painter.h"
#include <QByteArray>

class FBClient : public QObject
{
    Q_OBJECT
public:
    explicit FBClient(QObject * parent = 0);
//    ~FBCLient();
    Painter * painter;
    void start();
private:
    void drawFrame();
    QTcpSocket serverConnection;
    QHostAddress *hostLineEdit;
    qint16 *portLineEdit;
    FrameData remote_fbdata;
    QByteArray frame;
private slots:
    void readFrame();
    void connectSuccess();
    void disconnect();
    void connectToServer();
    void connectError();
};

#endif // FBCLIENT_H
