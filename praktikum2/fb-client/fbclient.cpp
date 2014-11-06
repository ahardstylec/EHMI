#include "fbclient.h"
#include "../fb-shared/framebuffer.h"
#include <QString>
#include <QDebug>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

FBClient::FBClient(Painter * painter)
{
    hostLineEdit = new QLineEdit("141.100.74.162");
    portLineEdit = new QLineEdit(8081);
    portLineEdit->setValidator(new QIntValidator(1, 65535, this));
    self.painter  = painter;
    qtsocket = new QTcpSocket(this);

    //connect to Server
    qtsocket->abort();
    qtsocket->connectToHost(hostLineEdit->text(),
                             portLineEdit->text().toInt());

    // bind socket to qt
    connect(*qtsocket, SIGNAL(readyRead()), this, SLOT(readFrame()));

    framebuffer_handler = open("/dev/fb0", O_RDWR);

    ioctl(framebuffer_handler, FBIOGET_FSCREENINFO, &fixed_info);

    printf("line length: %u\n", fixed_info.line_length);
    printf("type: %u\n", fixed_info.type);


    ioctl(framebuffer_handler, FBIOGET_VSCREENINFO, & var_info);
    screen_size = var_info.xres * var_info.yres * var_info.bits_per_pixel / 8;

    fb = reinterpret_cast<char *>(mmap(0, fixed_info.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, framebuffer_handler, 0));

    if (MAP_FAILED == fb) {
        throw strerror(errno);
    }

}

void FBClient::readFrame(){
    QDebug() << "start readFrame";
    quint16 blockSize;
    if (blockSize == 0) {
        if (qtsocket->bytesAvailable() < (int)sizeof(quint16))
            return;

        in >> blockSize;
    }

    if (qtsocket->bytesAvailable() < blockSize)
        return;

    qtsocket->readData((FrameData) frame, blockSize);

    QDebug() << "readed Frame: ";
    QDebug() << "read: " << blockSize << "Bytes";
    QDebug() << "xres: " << frame.xres;
    QDebug() << "yres: " << frame.yres;
    QDebug() << "bpp: "  << frame.bpp;
    painter->draw(frame);
    return;
}
