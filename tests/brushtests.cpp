#include "brushtests.h"


//!
//! \brief PlaneTests::testInitPlane Creates "(-16 -16 0) (16 -16 0) (16 16  0)"
//!
void PlaneTests::testInitPlane() {
    QVector3D botLeft(-16, -16, 0);
    QVector3D topLeft(16, -16, 0);
    QVector3D topRight(16, 16, 0);
    Plane p(botLeft,topLeft,topRight);
    QCOMPARE(p.getBotLeft(),botLeft);
    QCOMPARE(p.getTopLeft(),topLeft);
    QCOMPARE(p.getTopRight(),topRight);
}
