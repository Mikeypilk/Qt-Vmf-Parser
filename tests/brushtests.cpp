/*
This file is part of World Editor.

World Editor is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

World Editor is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with World Editor.  If not, see <http://www.gnu.org/licenses/>.
*/

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
void BrushTests::init() {
    actual.clear();
    expected.clear();
    planes.clear();
    Plane *plane;
    planes.prepend(plane = new Plane(QVector3D(-128, 32, 128),QVector3D(128, 32, 128),QVector3D(128, 0, 128)));
    planes.prepend(plane = new Plane(QVector3D(-128, 0, 0),QVector3D(128, 0, 0),QVector3D(128, 32, 0)));
    planes.prepend(plane = new Plane(QVector3D(-128, 32, 128),QVector3D(-128, 0, 128),QVector3D(-128, 0, 0)));
    planes.prepend(plane = new Plane(QVector3D(128, 32, 0),QVector3D(128, 0, 0),QVector3D(128, 0, 128)));
    planes.prepend(plane = new Plane(QVector3D(128, 32, 128),QVector3D(-128, 32, 128),QVector3D(-128, 32, 0)));
    planes.prepend(plane = new Plane(QVector3D(128, 0, 0),QVector3D(-128, 0, 0),QVector3D(-128, 0, 128)));
    brush = new Brush(planes);
}
void BrushTests::cleanup() {
    if (QTest::currentTestFailed()) {
        qDebug() << "Actual Results:";
        qDebug() << actual;
        qDebug() << "Expected Results:";
        qDebug() << expected;
    }
}
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
    Brush *brush = new Brush(planes);

    //! X against Y axis
    QCOMPARE(brush->getTopLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(-128,32));
    QCOMPARE(brush->getTopRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(128,32));
    QCOMPARE(brush->getBottomLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(-128,0));
    QCOMPARE(brush->getBottomRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(128,0));

    //! Y against Z axis
    QCOMPARE(brush->getTopLeft(Brush::Y_AXIS, Brush::Z_AXIS).toPoint(), QPoint(0,128));
    QCOMPARE(brush->getTopRight(Brush::Y_AXIS, Brush::Z_AXIS).toPoint(), QPoint(32,128));
    QCOMPARE(brush->getBottomLeft(Brush::Y_AXIS, Brush::Z_AXIS).toPoint(), QPoint(0,0));
    QCOMPARE(brush->getBottomRight(Brush::Y_AXIS, Brush::Z_AXIS).toPoint(), QPoint(32,0));

    //! X against Z axis
    QCOMPARE(brush->getTopLeft(Brush::X_AXIS, Brush::Z_AXIS).toPoint(), QPoint(-128,128));
    QCOMPARE(brush->getTopRight(Brush::X_AXIS, Brush::Z_AXIS).toPoint(), QPoint(128,128));
    QCOMPARE(brush->getBottomLeft(Brush::X_AXIS, Brush::Z_AXIS).toPoint(), QPoint(-128,0));
    QCOMPARE(brush->getBottomRight(Brush::X_AXIS, Brush::Z_AXIS).toPoint(), QPoint(128,0));

    planes.clear();
    planes.prepend(plane = new Plane(QVector3D(64, 32, 256),QVector3D(256, 32, 256),QVector3D(256, 0, 256)));
    planes.prepend(plane = new Plane(QVector3D(64, 0, 0),QVector3D(256, 0, 0),QVector3D(256, 32, 0)));
    planes.prepend(plane = new Plane(QVector3D(64, 32, 256),QVector3D(64, 0, 256),QVector3D(64, 0, 0)));
    planes.prepend(plane = new Plane(QVector3D(256, 32, 0),QVector3D(256, 0, 0),QVector3D(256, 0, 256)));
    planes.prepend(plane = new Plane(QVector3D(256, 32, 256),QVector3D(64, 32, 256),QVector3D(64, 32, 0)));
    planes.prepend(plane = new Plane(QVector3D(256, 0, 0),QVector3D(64, 0, 0),QVector3D(64, 0, 256)));
    brush = new Brush(planes);
    //! X against Y axis
    QCOMPARE(brush->getTopLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(64,32));
    QCOMPARE(brush->getTopRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(256,32));
    QCOMPARE(brush->getBottomLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(64,0));
    QCOMPARE(brush->getBottomRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(256,0));

    // TODO: Write more tests
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

    // TODO: Write more tests
}
//!
//! \brief BrushTests::testTranslate
//!
void BrushTests::testTranslate() {
    QList<Plane*> planes;
    Plane *plane;
    planes.prepend(plane = new Plane(QVector3D(-128, 32, 128),QVector3D(128, 32, 128),QVector3D(128, 0, 128)));
    planes.prepend(plane = new Plane(QVector3D(-128, 0, 0),QVector3D(128, 0, 0),QVector3D(128, 32, 0)));
    planes.prepend(plane = new Plane(QVector3D(-128, 32, 128),QVector3D(-128, 0, 128),QVector3D(-128, 0, 0)));
    planes.prepend(plane = new Plane(QVector3D(128, 32, 0),QVector3D(128, 0, 0),QVector3D(128, 0, 128)));
    planes.prepend(plane = new Plane(QVector3D(128, 32, 128),QVector3D(-128, 32, 128),QVector3D(-128, 32, 0)));
    planes.prepend(plane = new Plane(QVector3D(128, 0, 0),QVector3D(-128, 0, 0),QVector3D(-128, 0, 128)));
    Brush brush(planes);

    brush.translate(Brush::X_AXIS, Brush::Y_AXIS, QVector2D(128, 0));
    QCOMPARE(brush.getTopLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(0,32));
    QCOMPARE(brush.getTopRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(256,32));
    QCOMPARE(brush.getBottomLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(0,0));
    QCOMPARE(brush.getBottomRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(256,0));

    brush.translate(Brush::X_AXIS, Brush::Y_AXIS, QVector2D(-128, 32));
    QCOMPARE(brush.getTopLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(-128,64));
    QCOMPARE(brush.getTopRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(128,64));
    QCOMPARE(brush.getBottomLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(-128,32));
    QCOMPARE(brush.getBottomRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(128,32));

    brush.translate(Brush::X_AXIS, Brush::Y_AXIS, QVector2D(0, -48));
    QCOMPARE(brush.getTopLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(-128,16));
    QCOMPARE(brush.getTopRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(128,16));
    QCOMPARE(brush.getBottomLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(-128,-16));
    QCOMPARE(brush.getBottomRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(128,-16));

    // TODO: Write more tests
}
//!
//! \brief BrushTests::testRotate
//!
void BrushTests::testRotateFullCircleXY() {
    QList<Plane*> planes;
    Plane *plane;
    planes.prepend(plane = new Plane(QVector3D(-128, 32, 128),QVector3D(128, 32, 128),QVector3D(128, 0, 128)));
    planes.prepend(plane = new Plane(QVector3D(-128, 0, 0),QVector3D(128, 0, 0),QVector3D(128, 32, 0)));
    planes.prepend(plane = new Plane(QVector3D(-128, 32, 128),QVector3D(-128, 0, 128),QVector3D(-128, 0, 0)));
    planes.prepend(plane = new Plane(QVector3D(128, 32, 0),QVector3D(128, 0, 0),QVector3D(128, 0, 128)));
    planes.prepend(plane = new Plane(QVector3D(128, 32, 128),QVector3D(-128, 32, 128),QVector3D(-128, 32, 0)));
    planes.prepend(plane = new Plane(QVector3D(128, 0, 0),QVector3D(-128, 0, 0),QVector3D(-128, 0, 128)));
    Brush *brush = new Brush(planes);

    //! Rotate XY AXIS
    brush->rotate(Brush::X_AXIS, Brush::Y_AXIS, 90);
    QCOMPARE(brush->getTopLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(-16,144));
    QCOMPARE(brush->getTopRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(16,144));
    QCOMPARE(brush->getBottomLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(-16,-112));
    QCOMPARE(brush->getBottomRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(16,-112));

    brush->rotate(Brush::X_AXIS, Brush::Y_AXIS, 90);
    QCOMPARE(brush->getTopLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(-128,32));
    QCOMPARE(brush->getTopRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(128,32));
    QCOMPARE(brush->getBottomLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(-128,0));
    QCOMPARE(brush->getBottomRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(128,0));

    brush->rotate(Brush::X_AXIS, Brush::Y_AXIS, 90);
    QCOMPARE(brush->getTopLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(-16,144));
    QCOMPARE(brush->getTopRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(16,144));
    QCOMPARE(brush->getBottomLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(-16,-112));
    QCOMPARE(brush->getBottomRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(16,-112));

    brush->rotate(Brush::X_AXIS, Brush::Y_AXIS, 90);
    QCOMPARE(brush->getTopLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(-128,32));
    QCOMPARE(brush->getTopRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(128,32));
    QCOMPARE(brush->getBottomLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(-128,0));
    QCOMPARE(brush->getBottomRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(128,0));
    QCOMPARE(brush->getTopLeft(Brush::Y_AXIS, Brush::Z_AXIS).toPoint(), QPoint(0,128));
    QCOMPARE(brush->getTopRight(Brush::Y_AXIS, Brush::Z_AXIS).toPoint(), QPoint(32,128));
    QCOMPARE(brush->getBottomLeft(Brush::Y_AXIS, Brush::Z_AXIS).toPoint(), QPoint(0,0));
    QCOMPARE(brush->getBottomRight(Brush::Y_AXIS, Brush::Z_AXIS).toPoint(), QPoint(32,0));
    QCOMPARE(brush->getTopLeft(Brush::X_AXIS, Brush::Z_AXIS).toPoint(), QPoint(-128,128));
    QCOMPARE(brush->getTopRight(Brush::X_AXIS, Brush::Z_AXIS).toPoint(), QPoint(128,128));
    QCOMPARE(brush->getBottomLeft(Brush::X_AXIS, Brush::Z_AXIS).toPoint(), QPoint(-128,0));
    QCOMPARE(brush->getBottomRight(Brush::X_AXIS, Brush::Z_AXIS).toPoint(), QPoint(128,0));
}
void BrushTests::testRotateYZ() {
    brush->rotate(Brush::Y_AXIS, Brush::Z_AXIS, 90);
    QCOMPARE(brush->getTopLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(-128,80));
    QCOMPARE(brush->getTopRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(128,80));
    QCOMPARE(brush->getBottomLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(-128,-48));
    QCOMPARE(brush->getBottomRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(128,-48));
    brush->rotate(Brush::X_AXIS, Brush::Z_AXIS, 90);
    QCOMPARE(brush->getTopLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(-16,80));
    QCOMPARE(brush->getTopRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(16,80));
    QCOMPARE(brush->getBottomLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(-16,-48));
    QCOMPARE(brush->getBottomRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint(), QPoint(16,-48));
}
//!
//! \brief BrushTests::testTransform_topLeft
//!
void BrushTests::testTransform_topLeft() {
    expected.append(QPoint(-384,96));
    expected.append(QPoint(128,96));
    expected.append(QPoint(-384,0));
    expected.append(QPoint(128,0));
    brush->transform(Brush::BOUND_BOX__TOP_LEFT, Brush::X_AXIS, Brush::Y_AXIS, QVector2D(-256,64));
    actual.append(brush->getTopLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    actual.append(brush->getTopRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    actual.append(brush->getBottomLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    actual.append(brush->getBottomRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    QCOMPARE(expected,actual);
}
//!
//! \brief BrushTests::testTransform_topLeft_2
//!
void BrushTests::testTransform_topLeft_2() {
    expected.append(QPoint(-256,16));
    expected.append(QPoint(128,16));
    expected.append(QPoint(-256,0));
    expected.append(QPoint(128,0));
    brush->transform(Brush::BOUND_BOX__TOP_LEFT, Brush::X_AXIS, Brush::Y_AXIS, QVector2D(-128,-16));
    actual.append(brush->getTopLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    actual.append(brush->getTopRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    actual.append(brush->getBottomLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    actual.append(brush->getBottomRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    QCOMPARE(expected,actual);
}
//!
//! \brief BrushTests::testTransform_topLeft_3
//!
void BrushTests::testTransform_topLeft_3() {
    expected.append(QPoint(0,16));
    expected.append(QPoint(128,16));
    expected.append(QPoint(0,0));
    expected.append(QPoint(128,0));
    brush->transform(Brush::BOUND_BOX__TOP_LEFT, Brush::X_AXIS, Brush::Y_AXIS, QVector2D(128,-16));
    actual.append(brush->getTopLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    actual.append(brush->getTopRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    actual.append(brush->getBottomLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    actual.append(brush->getBottomRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    QCOMPARE(expected,actual);
}
//!
//! \brief BrushTests::testTransform_topLeft_4
//!
void BrushTests::testTransform_topLeft_4() {
    expected.append(QPoint(-64,48));
    expected.append(QPoint(128,48));
    expected.append(QPoint(-64,0));
    expected.append(QPoint(128,0));
    brush->transform(Brush::BOUND_BOX__TOP_LEFT, Brush::X_AXIS, Brush::Y_AXIS, QVector2D(64,16));
    actual.append(brush->getTopLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    actual.append(brush->getTopRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    actual.append(brush->getBottomLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    actual.append(brush->getBottomRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    QCOMPARE(expected,actual);
}
//!
//! \brief BrushTests::testTransform_topRight
//!
void BrushTests::testTransform_topRight() {
    expected.append(QPoint(-128,48));
    expected.append(QPoint(256,48));
    expected.append(QPoint(-128,0));
    expected.append(QPoint(256,0));
    brush->transform(Brush::BOUND_BOX__TOP_RIGHT, Brush::X_AXIS, Brush::Y_AXIS, QVector2D(128,16));
    actual.append(brush->getTopLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    actual.append(brush->getTopRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    actual.append(brush->getBottomLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    actual.append(brush->getBottomRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    QCOMPARE(expected,actual);
}
//!
//! \brief BrushTests::testTransform_topRight_2
//!
void BrushTests::testTransform_topRight_2() {
    expected.append(QPoint(-128,48));
    expected.append(QPoint(64,48));
    expected.append(QPoint(-128,0));
    expected.append(QPoint(64,0));
    brush->transform(Brush::BOUND_BOX__TOP_RIGHT, Brush::X_AXIS, Brush::Y_AXIS, QVector2D(-64,16));
    actual.append(brush->getTopLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    actual.append(brush->getTopRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    actual.append(brush->getBottomLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    actual.append(brush->getBottomRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    QCOMPARE(expected,actual);
}
//!
//! \brief BrushTests::testTransform_topRight_3
//!
void BrushTests::testTransform_topRight_3() {
    expected.append(QPoint(-128,16));
    expected.append(QPoint(64,16));
    expected.append(QPoint(-128,0));
    expected.append(QPoint(64,0));
    brush->transform(Brush::BOUND_BOX__TOP_RIGHT, Brush::X_AXIS, Brush::Y_AXIS, QVector2D(-64,-16));
    actual.append(brush->getTopLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    actual.append(brush->getTopRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    actual.append(brush->getBottomLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    actual.append(brush->getBottomRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    QCOMPARE(expected,actual);
}
//!
//! \brief BrushTests::testTransform_topRight_4
//!
void BrushTests::testTransform_topRight_4() {
    expected.append(QPoint(-128,16));
    expected.append(QPoint(192,16));
    expected.append(QPoint(-128,0));
    expected.append(QPoint(192,0));
    brush->transform(Brush::BOUND_BOX__TOP_RIGHT, Brush::X_AXIS, Brush::Y_AXIS, QVector2D(64,-16));
    actual.append(brush->getTopLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    actual.append(brush->getTopRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    actual.append(brush->getBottomLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    actual.append(brush->getBottomRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    QCOMPARE(expected,actual);
}
//!
//! \brief BrushTests::testTransform_botLeft
//!
void BrushTests::testTransform_botLeft() {
    expected.append(QPoint(-64,32));
    expected.append(QPoint(128,32));
    expected.append(QPoint(-64,-16));
    expected.append(QPoint(128,-16));
    brush->transform(Brush::BOUND_BOX__BOTTOM_LEFT, Brush::X_AXIS, Brush::Y_AXIS, QVector2D(64,-16));
    actual.append(brush->getTopLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    actual.append(brush->getTopRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    actual.append(brush->getBottomLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    actual.append(brush->getBottomRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    QCOMPARE(expected,actual);
}
//!
//! \brief BrushTests::testTransform_botRight
//!
void BrushTests::testTransform_botRight() {
    expected.append(QPoint(-128,32));
    expected.append(QPoint(192,32));
    expected.append(QPoint(-128,-16));
    expected.append(QPoint(192,-16));
    brush->transform(Brush::BOUND_BOX__BOTTOM_RIGHT, Brush::X_AXIS, Brush::Y_AXIS, QVector2D(64,-16));
    actual.append(brush->getTopLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    actual.append(brush->getTopRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    actual.append(brush->getBottomLeft(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    actual.append(brush->getBottomRight(Brush::X_AXIS, Brush::Y_AXIS).toPoint());
    QCOMPARE(expected,actual);
}
//!
//! \brief BrushTests::testMatchVertexes
//!
void BrushTests::testMatchVertexes() {
    brush->matchingVertexes(Brush::X_AXIS,Brush::Y_AXIS,QVector2D(-128,32));
    QCOMPARE(brush->m_xMatch.size(), 9);
    QCOMPARE(brush->m_yMatch.size(), 8);
    brush->matchingVertexes(Brush::X_AXIS,Brush::Z_AXIS,QVector2D(-128,128));
    QCOMPARE(brush->m_xMatch.size(), 9);
    QCOMPARE(brush->m_zMatch.size(), 9);
    QCOMPARE(brush->m_yMatch.size(), 0);
    brush->matchingVertexes(Brush::X_AXIS,Brush::Z_AXIS,QVector2D(-512,1024));
    QCOMPARE(brush->m_xMatch.size(), 0);
    QCOMPARE(brush->m_zMatch.size(), 0);
    QCOMPARE(brush->m_yMatch.size(), 0);
}
//!
//! \brief BrushTests::testTranslateVertexes
//!
void BrushTests::testTranslateVertexes() {
   // Top left corner
   brush->matchingVertexes(Brush::X_AXIS,Brush::Y_AXIS,QVector2D(-128,32));
   QCOMPARE(brush->m_xMatch.size(), 9);
   QCOMPARE(brush->m_yMatch.size(), 8);
   brush->translateMyVertexes(Brush::X_AXIS, Brush::Y_AXIS, QVector2D(128, 0));
   brush->matchingVertexes(Brush::X_AXIS, Brush::Y_AXIS, QVector2D(-128, 32));
   QCOMPARE(brush->m_xMatch.size(), 4);
   QCOMPARE(brush->m_yMatch.size(), 8);
   brush->matchingVertexes(Brush::X_AXIS, Brush::Y_AXIS, QVector2D(0, 32));
   QCOMPARE(brush->m_xMatch.size(), 5);
   QCOMPARE(brush->m_yMatch.size(), 8);
}

void BrushTests::testInitBrushOctagonal() {

  planes.clear();
  Plane *plane;
  planes.prepend(plane = new Plane(QVector3D(32, -32, 64),QVector3D(-32, -32, 64),QVector3D(-32, 32, 64)));
  planes.prepend(plane = new Plane(QVector3D(-32, -32, 0),QVector3D(32, -32, 0),QVector3D(32, 32, 0)));
  planes.prepend(plane = new Plane(QVector3D(48, -48, 16),QVector3D(32, -64, 32),QVector3D(48, -48, 48)));
  planes.prepend(plane = new Plane(QVector3D(-48, -48, 48),QVector3D(-32, -64, 32),QVector3D(-48, -48, 16)));
  planes.prepend(plane = new Plane(QVector3D(-48, 48, 16),QVector3D(-32, 64, 32),QVector3D(-48, 48, 48)));
  planes.prepend(plane = new Plane(QVector3D(64, 32, 32),QVector3D(48, 48, 48),QVector3D(32, 64, 32)));
  planes.prepend(plane = new Plane(QVector3D(-32, 32, 0),QVector3D(32, 32, 0),QVector3D(48, 48, 16)));
  planes.prepend(plane = new Plane(QVector3D(-32, -32, 0),QVector3D(-32, -32, 0),QVector3D(-48, -48, 16)));
  planes.prepend(plane = new Plane(QVector3D(32, 32, 0),QVector3D(32, -32, 0),QVector3D(48, -48, 16)));
  planes.prepend(plane = new Plane(QVector3D(-32, -32, 0),QVector3D(-32, 32, 0),QVector3D(-48, 48, 16)));
  planes.prepend(plane = new Plane(QVector3D(-32, -64, 32),QVector3D(-48, -48, 48),QVector3D(-32, -32, 64)));
  planes.prepend(plane = new Plane(QVector3D(32, 64, 32),QVector3D(48, 48, 48),QVector3D(32, 32, 64)));
  planes.prepend(plane = new Plane(QVector3D(-64, 32, 32),QVector3D(-48, 48, 48),QVector3D(-32, 32, 64)));
  planes.prepend(plane = new Plane(QVector3D(64, 32, 32),QVector3D(64, -32, 32),QVector3D(48, -48, 48)));
  brush = new Brush(planes);




}
