#include <QCoreApplication>
#include "../fb-shared/framebuffer.h"
#include "fbserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    FBServer server;
    server.start();

    return a.exec();
}
