#include "brushtests.h"

///////////////////////////////////////////////////////////////////////////////
/// PLANE TESTS
/// ///////////////////////////////////////////////////////////////////////////
//!
//! \brief PlaneTests::testInitPlane test init"
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

//!
//! \brief PlaneTests::testGetSet tests get and set are implemented properly
//!
void PlaneTests::testGetSet() {

    QVector3D botLeft(-32, -32, 0);
    QVector3D topLeft(32, -32, 0);
    QVector3D topRight(32, 32, 0);
    Plane p(botLeft,topLeft,topRight);

    QVector3D botLeft2(-16, -16, 0);
    QVector3D topLeft2(16, -16, 0);
    QVector3D topRight2(16, 16, 0);

    p.setBotLeft(botLeft2);
    p.setTopLeft(topLeft2);
    p.setTopRight(topRight2);

    QCOMPARE(p.getBotLeft(),botLeft2);
    QCOMPARE(p.getTopLeft(),topLeft2);
    QCOMPARE(p.getTopRight(),topRight2);

}
//!
//! \brief PlaneTests::testInvalid tests for values that are the same
//!
void PlaneTests::testInvalid() {

    QVector3D uninit3d;

    // Invalid values 1
    QVector3D botLeft2(16, -16, 0);
    QVector3D topLeft2(16, -16, 0);
    QVector3D topRight2(16, -16, 0);
    Plane x(botLeft2,topLeft2,topRight2);
    QCOMPARE(x.getBotLeft(), uninit3d);
    QCOMPARE(x.getTopLeft(), uninit3d);
    QCOMPARE(x.getTopRight(), uninit3d);

    // Invalid values 2
    QVector3D botLeft3(16, -16, 0);
    QVector3D topLeft3(16, -16, 0);
    QVector3D topRight3(16, 16, 0);
    Plane y(botLeft3,topLeft3,topRight3);
    QCOMPARE(y.getBotLeft(), uninit3d);
    QCOMPARE(y.getTopLeft(), uninit3d);
    QCOMPARE(y.getTopRight(), uninit3d);

    // Invalid values 3
    QVector3D botLeft4(16, -16, 0);
    QVector3D topLeft4(32, -16, 0);
    QVector3D topRight4(32, -16, 0);
    Plane z(botLeft4,topLeft4,topRight4);
    QCOMPARE(z.getBotLeft(), uninit3d);
    QCOMPARE(z.getTopLeft(), uninit3d);
    QCOMPARE(z.getTopRight(), uninit3d);
}
///////////////////////////////////////////////////////////////////////////////
/// BRUSH TESTS
/// ///////////////////////////////////////////////////////////////////////////
//!
//! \brief BrushTests::testInitBrush test init
//!
void BrushTests::testInitBrush() {
    //    https://developer.valvesoftware.com/wiki/VMF#Planes
    QList<Plane*> planes;
    Plane *plane;
    planes.prepend(plane = new Plane(QVector3D(-128, 32, 128),QVector3D(128, 32, 128),QVector3D(128, 0, 128)));
    planes.prepend(plane = new Plane(QVector3D(-128, 0, 0),QVector3D(128, 0, 0),QVector3D(128, 32, 0)));
    planes.prepend(plane = new Plane(QVector3D(-128, 32, 128),QVector3D(-128, 0, 128),QVector3D(-128, 0, 0)));
    planes.prepend(plane = new Plane(QVector3D(128, 32, 0),QVector3D(128, 0, 0),QVector3D(128, 0, 128)));
    planes.prepend(plane = new Plane(QVector3D(128, 32, 128),QVector3D(-128, 32, 128),QVector3D(-128, 32, 0)));
    planes.prepend(plane = new Plane(QVector3D(128, 0, 0),QVector3D(-128, 0, 0),QVector3D(-128, 0, 128)));
    Brush brush(planes);
    QCOMPARE(brush.getNumOfSides(), 6);
}
//!
//! \brief BrushTests::testInvalid tests more than one plane on same plane
//!
void BrushTests::testInvalid() {
    QList<Plane*> planes2;
    Plane *plane2;
    planes2.prepend(plane2 = new Plane(QVector3D(-32, -32, 0),QVector3D(32, -32, 0),QVector3D(32, 32, 0)));
    planes2.prepend(plane2 = new Plane(QVector3D(32, -32, 0),QVector3D(32, 32,  0),QVector3D(-32, 32, 0)));
    planes2.prepend(plane2 = new Plane(QVector3D(32, 32,  0),QVector3D(-32, 32, 0),QVector3D(-32, -32, 0)));
    planes2.prepend(plane2 = new Plane(QVector3D(-32, 32, 0),QVector3D(-32, -32, 0),QVector3D(32 ,-32,  0)));
    Brush brush2(planes2);
    QCOMPARE(brush2.getNumOfSides(), 0);
}
//!
//! \brief BrushTests::testCorners tests that the corners for the bounding box are calculated
//!
void BrushTests::testCorners() {
    //    https://developer.valvesoftware.com/wiki/VMF#Planes
    QList<Plane*> planes;
    Plane *plane;
    planes.prepend(plane = new Plane(QVector3D(-128, 32, 128),QVector3D(128, 32, 128),QVector3D(128, 0, 128)));
    planes.prepend(plane = new Plane(QVector3D(-128, 0, 0),QVector3D(128, 0, 0),QVector3D(128, 32, 0)));
    planes.prepend(plane = new Plane(QVector3D(-128, 32, 128),QVector3D(-128, 0, 128),QVector3D(-128, 0, 0)));
    planes.prepend(plane = new Plane(QVector3D(128, 32, 0),QVector3D(128, 0, 0),QVector3D(128, 0, 128)));
    planes.prepend(plane = new Plane(QVector3D(128, 32, 128),QVector3D(-128, 32, 128),QVector3D(-128, 32, 0)));
    planes.prepend(plane = new Plane(QVector3D(128, 0, 0),QVector3D(-128, 0, 0),QVector3D(-128, 0, 128)));
    Brush brush(planes);

    //! X against Y axis
    QCOMPARE(brush.getTopLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(-128,32));
    QCOMPARE(brush.getTopRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(128,32));
    QCOMPARE(brush.getBottomLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(-128,0));
    QCOMPARE(brush.getBottomRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(128,0));

    //! Y against Z axis
    QCOMPARE(brush.getTopLeft(Brush::Y_AXIS, Brush::Z_AXIS).toPoint(), QPoint(0,128));
    QCOMPARE(brush.getTopRight(Brush::Y_AXIS, Brush::Z_AXIS).toPoint(), QPoint(32,128));
    QCOMPARE(brush.getBottomLeft(Brush::Y_AXIS, Brush::Z_AXIS).toPoint(), QPoint(0,0));
    QCOMPARE(brush.getBottomRight(Brush::Y_AXIS, Brush::Z_AXIS).toPoint(), QPoint(32,0));

    //! X against Z axis
    QCOMPARE(brush.getTopLeft(Brush::X_AXIS, Brush::Z_AXIS).toPoint(), QPoint(-128,128));
    QCOMPARE(brush.getTopRight(Brush::X_AXIS, Brush::Z_AXIS).toPoint(), QPoint(128,128));
    QCOMPARE(brush.getBottomLeft(Brush::X_AXIS, Brush::Z_AXIS).toPoint(), QPoint(-128,0));
    QCOMPARE(brush.getBottomRight(Brush::X_AXIS, Brush::Z_AXIS).toPoint(), QPoint(128,0));

}
//!
//! \brief BrushTests::testEdges tests that the edges for the bounding box are calculated properly
//!
void BrushTests::testEdges() {
    QList<Plane*> planes;
    Plane *plane;
    planes.prepend(plane = new Plane(QVector3D(-128, 32, 128),QVector3D(128, 32, 128),QVector3D(128, 0, 128)));
    planes.prepend(plane = new Plane(QVector3D(-128, 0, 0),QVector3D(128, 0, 0),QVector3D(128, 32, 0)));
    planes.prepend(plane = new Plane(QVector3D(-128, 32, 128),QVector3D(-128, 0, 128),QVector3D(-128, 0, 0)));
    planes.prepend(plane = new Plane(QVector3D(128, 32, 0),QVector3D(128, 0, 0),QVector3D(128, 0, 128)));
    planes.prepend(plane = new Plane(QVector3D(128, 32, 128),QVector3D(-128, 32, 128),QVector3D(-128, 32, 0)));
    planes.prepend(plane = new Plane(QVector3D(128, 0, 0),QVector3D(-128, 0, 0),QVector3D(-128, 0, 128)));
    Brush brush(planes);

    QCOMPARE(brush.getBottom(Brush::X_AXIS, Brush::Y_AXIS).toPointF(), QPointF(0,0));
}
//!
//! \brief BrushTests::testTransform tests transforming the block with the corners
//!
void BrushTests::testTransformCorners() {
    QList<Plane*> planes;
    Plane *plane;
    planes.prepend(plane = new Plane(QVector3D(-128, 32, 128),QVector3D(128, 32, 128),QVector3D(128, 0, 128)));
    planes.prepend(plane = new Plane(QVector3D(-128, 0, 0),QVector3D(128, 0, 0),QVector3D(128, 32, 0)));
    planes.prepend(plane = new Plane(QVector3D(-128, 32, 128),QVector3D(-128, 0, 128),QVector3D(-128, 0, 0)));
    planes.prepend(plane = new Plane(QVector3D(128, 32, 0),QVector3D(128, 0, 0),QVector3D(128, 0, 128)));
    planes.prepend(plane = new Plane(QVector3D(128, 32, 128),QVector3D(-128, 32, 128),QVector3D(-128, 32, 0)));
    planes.prepend(plane = new Plane(QVector3D(128, 0, 0),QVector3D(-128, 0, 0),QVector3D(-128, 0, 128)));
    Brush brush(planes);

    //! Move the top left corner to -256,64
    brush.transform(Brush::BOUND_BOX__TOP_LEFT, Brush::X_AXIS, Brush::Y_AXIS, QPoint(-256,64));
    QCOMPARE(brush.getTopLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(-256,64));
    QCOMPARE(brush.getTopRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(128,64));
    QCOMPARE(brush.getBottomLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(-256,0));
    QCOMPARE(brush.getBottomRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(128,0));

    //! Move the top right corner to 256,128
    brush.transform(Brush::BOUND_BOX__TOP_RIGHT, Brush::X_AXIS, Brush::Y_AXIS, QPoint(256,128));
    QCOMPARE(brush.getTopLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(-256,128));
    QCOMPARE(brush.getTopRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(256,128));
    QCOMPARE(brush.getBottomLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(-256,0));
    QCOMPARE(brush.getBottomRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(256,0));

    //! Move the bottom left corner to -512, -128
    brush.transform(Brush::BOUND_BOX__BOTTOM_LEFT, Brush::X_AXIS, Brush::Z_AXIS, QPoint(-512,-128));
    QCOMPARE(brush.getTopLeft(Brush::X_AXIS, Brush::Z_AXIS).toPoint(), QPoint(-512,128));
    QCOMPARE(brush.getTopRight(Brush::X_AXIS, Brush::Z_AXIS).toPoint(), QPoint(256,128));
    QCOMPARE(brush.getBottomLeft(Brush::X_AXIS, Brush::Z_AXIS).toPoint(), QPoint(-512,-128));
    QCOMPARE(brush.getBottomRight(Brush::X_AXIS, Brush::Z_AXIS).toPoint(), QPoint(256,-128));
}
//!
//! \brief BrushTests::testTransformEdges tests transforming the block with edges
//!
void BrushTests::testTransformEdges() {
    QList<Plane*> planes;
    Plane *plane;
    planes.prepend(plane = new Plane(QVector3D(-128, 32, 128),QVector3D(128, 32, 128),QVector3D(128, 0, 128)));
    planes.prepend(plane = new Plane(QVector3D(-128, 0, 0),QVector3D(128, 0, 0),QVector3D(128, 32, 0)));
    planes.prepend(plane = new Plane(QVector3D(-128, 32, 128),QVector3D(-128, 0, 128),QVector3D(-128, 0, 0)));
    planes.prepend(plane = new Plane(QVector3D(128, 32, 0),QVector3D(128, 0, 0),QVector3D(128, 0, 128)));
    planes.prepend(plane = new Plane(QVector3D(128, 32, 128),QVector3D(-128, 32, 128),QVector3D(-128, 32, 0)));
    planes.prepend(plane = new Plane(QVector3D(128, 0, 0),QVector3D(-128, 0, 0),QVector3D(-128, 0, 128)));
    Brush brush(planes);

    brush.transform(Brush::BOUND_BOX__BOTTOM, Brush::X_AXIS, Brush::Y_AXIS, QPoint(0,-32));
    QCOMPARE(brush.getTopLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(-128,32));
    QCOMPARE(brush.getTopRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(128,32));
    QCOMPARE(brush.getBottomLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(-128,-32));
    QCOMPARE(brush.getBottomRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(128,-32));

}

