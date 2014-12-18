#ifndef BLINKERRIGHT_H
#define BLINKERRIGHT_H

#include <QObject>
#include <QTimer>
#include "global.h"
#include <QTime>

class Blinker : public QSvgViewItem
{
    Q_OBJECT
public:
    Blinker(int side);
    ~Blinker();
    int side;
    bool isBlinking;
    QTimer timer;

signals:
    bool setLight(bool);

public slots:
    void update(int value);
    void toggleBlinker();
    void blinkerWatchDog();

};

#endif // BLINKERRIGHT_H
