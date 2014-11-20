#include <QtCore/QCoreApplication>
#include "fbclient.h"
#include "painter.h"
#include <QDebug>
#include <Magick++.h>

int main(int argc, char *argv[])
{
    Magick::InitializeMagick(*argv);
    QCoreApplication a(argc, argv);
    qDebug() << "started fbclient";
    Painter painter;
    FBClient client;
    client.painter = &painter;
    client.start();
    
    return a.exec();
}
