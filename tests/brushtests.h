#ifndef PLANETESTS_H
#define PLANETESTS_H

#include <QObject>
#include <QtTest>
#include "brush.h"

class PlaneTests : public QObject
{
    Q_OBJECT
    private slots:
        void testInitPlane();
};


#endif // PLANETESTS_H
