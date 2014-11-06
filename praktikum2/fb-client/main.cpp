#include <QtCore/QCoreApplication>
#include "fbclient.h"
#include "painter.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Painter painter;
    FBClient client(&painter);
    
    return a.exec();
}
