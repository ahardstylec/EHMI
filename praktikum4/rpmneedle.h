#ifndef RPMNEEDLE_H
#define RPMNEEDLE_H

#include <QObject>
#include <QVector3D>
#include "qsvgviewitem.h"

class RpmNeedle : public QSvgViewItem
{
    Q_OBJECT
public:
    RpmNeedle(QString filename, qreal xPosOffset, qreal yPosOffset);
    ~RpmNeedle();

    QVector3D rotationPoint;

public slots:
    virtual void update(qreal value)=0;
};

#endif // RPMNEEDLE_H
