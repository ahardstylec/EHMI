#include <QtCore/QCoreApplication>
#include "fbclient.h"
#include "painter.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    painter = Painter();
    client = FBClient(&painter);
    
    return a.exec();
}
