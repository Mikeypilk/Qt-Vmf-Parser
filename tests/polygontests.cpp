
#include "polygontests.h"

//!
//! \brief PolygonTests::cleanup
//!
void PolygonTests::cleanup() {
    if(!actual.empty() && !expected.empty())
        if (QTest::currentTestFailed()) {
            qDebug() << "Actual Results:";
            qDebug() << actual;
            qDebug() << "Expected Results:";
            qDebug() << expected;
        }
    expected.clear();
    actual.clear();
}
//!
//! \brief PolygonTests::testSquare
//!
//! @verbatim
//!
//!    *          * (128, 128)
//!
//!
//!
//!
//!    [*]        * (128, 0)
//!
//! @endverbatim
//!
void PolygonTests::testSquare() {


    QVector<QPointF> testPoints;
    testPoints.append(QPointF(128, 128));
    testPoints.append(QPointF(0, 0));
    testPoints.append(QPointF(0, 128));
    testPoints.append(QPointF(128, 0));

    expected.append(QPointF(0,0));
    expected.append(QPointF(128, 0));
    expected.append(QPointF(128, 128));
    expected.append(QPointF(0,128));

    actual = Polygoniser::poligonise(testPoints);
    QCOMPARE(expected, actual);
}
//!
//! \brief PolygonTests::testPentagon
//!
//! //! @verbatim
//!
//!          *   (64, 192)
//!
//!
//!
//!    *          * (128, 128)
//!
//!
//!
//!
//!    [*]        * (128, 0)
//!
//! @endverbatim
//!
void PolygonTests::testPentagon() {
    QVector<QPointF> testPoints;
    testPoints.append(QPointF(128, 128));
    testPoints.append(QPointF(0, 0));
    testPoints.append(QPointF(0, 128));
    testPoints.append(QPointF(128, 0));
    testPoints.append(QPointF(64, 192));

    expected.append(QPointF(0,0));
    expected.append(QPointF(128, 0));
    expected.append(QPointF(128, 128));
    expected.append(QPointF(64, 192));
    expected.append(QPointF(0,128));

    actual = Polygoniser::poligonise(testPoints);
    QCOMPARE(expected, actual);
}
//!
//! \brief PolygonTests::testHexagon
//!
//! //! @verbatim
//!
//!          *   (64, 192)
//!
//!
//!    *          * (128, 128)
//!
//!
//!    *          * (128, 0)
//!
//!
//!         [*]   (64, -64)
//!
//! @endverbatim
//!
void PolygonTests::testHexagon() {
    QVector<QPointF> testPoints;
    testPoints.append(QPointF(128, 128));
    testPoints.append(QPointF(0, 0));
    testPoints.append(QPointF(0, 128));
    testPoints.append(QPointF(128, 0));
    testPoints.append(QPointF(64, 192));
    testPoints.append(QPointF(64, -64));

    expected.append(QPointF(64, -64));
    expected.append(QPointF(128, 0));
    expected.append(QPointF(128, 128));
    expected.append(QPointF(64, 192));
    expected.append(QPointF(0,128));
    expected.append(QPointF(0,0));

    actual = Polygoniser::poligonise(testPoints);
    QCOMPARE(expected, actual);

}
//!
//! \brief PolygonTests::testOctagon
//!
//! @verbatim
//!
//!(-32,64) *       *     (32,64)
//!
//!     *               *   (64, 32)
//!
//!
//!     *               *   (64, -32)
//!
//!         *       *    (32, -64)
//!
//! @endverbatim
void PolygonTests::testOctagon() {
    QVector<QPointF> testPoints;
    testPoints.append(QPointF(-32, 64));
    testPoints.append(QPointF(-32, -64));
    testPoints.append(QPointF(32, 64));
    testPoints.append(QPointF(32, -64));
    testPoints.append(QPointF(64, -32));
    testPoints.append(QPointF(64, 32));
    testPoints.append(QPointF(-64, 32));
    testPoints.append(QPointF(-64, -32));

    expected.append(QPointF(-32, -64));
    expected.append(QPointF(32, -64));
    expected.append(QPointF(64, -32));
    expected.append(QPointF(64, 32));
    expected.append(QPointF(32, 64));
    expected.append(QPointF(-32, 64));
    expected.append(QPointF(-64, 32));
    expected.append(QPointF(-64, -32));

    actual = Polygoniser::poligonise(testPoints);
    QCOMPARE(expected, actual);
}
//!
//! \brief PolygonTests::testCuboid
//! https://developer.valvesoftware.com/wiki/File:Brush_planes.gif
//!     ____________
//!    |\____________\
//!    \|____________|
//!
void PolygonTests::testCuboid() {

    QList<Plane*> planes;
    Plane *plane;
    planes.prepend(plane = new Plane(QVector3D(-128, 32, 128),QVector3D(128, 32, 128),QVector3D(128, 0, 128)));
    planes.prepend(plane = new Plane(QVector3D(-128, 0, 0),QVector3D(128, 0, 0),QVector3D(128, 32, 0)));
    planes.prepend(plane = new Plane(QVector3D(-128, 32, 128),QVector3D(-128, 0, 128),QVector3D(-128, 0, 0)));
    planes.prepend(plane = new Plane(QVector3D(128, 32, 0),QVector3D(128, 0, 0),QVector3D(128, 0, 128)));
    planes.prepend(plane = new Plane(QVector3D(128, 32, 128),QVector3D(-128, 32, 128),QVector3D(-128, 32, 0)));
    planes.prepend(plane = new Plane(QVector3D(128, 0, 0),QVector3D(-128, 0, 0),QVector3D(-128, 0, 128)));
    Brush *brush = new Brush(planes);

    QList<QPolygonF> polys = Polygoniser::poligonise(brush, X_AXIS, Y_AXIS);

    QVector<QPointF> Shape1; Shape1 <<  QPointF(-128,0)  << QPointF(128,0);
    QVector<QPointF> Shape2; Shape2 <<  QPointF(-128, 32)  << QPointF(128,32);
    QVector<QPointF> Shape3; Shape3 <<  QPointF(128,0)   << QPointF(128,32);
    QVector<QPointF> Shape4; Shape4 <<  QPointF(-128,0)  << QPointF(-128,32);
    QVector<QPointF> Shape5; Shape5 <<  QPointF(-128,0)  << QPointF(128,0) << QPointF(128,32) << QPointF(-128,32);
    QVector<QPointF> Shape6; Shape6 <<  QPointF(-128,0)  << QPointF(128,0) << QPointF(128,32) << QPointF(-128,32);

    QVERIFY(polys.contains(QPolygonF(Shape1)));
    QVERIFY(polys.contains(QPolygonF(Shape2)));
    QVERIFY(polys.contains(QPolygonF(Shape3)));
    QVERIFY(polys.contains(QPolygonF(Shape4)));
    QVERIFY(polys.contains(QPolygonF(Shape5)));
    QVERIFY(polys.contains(QPolygonF(Shape6)));

}
//!
//! \brief PolygonTests::testOctagonalPrism
//!
void PolygonTests::testOctagonalPrism() {

    QList<Plane*> planes;
    Plane *plane;
    planes.prepend(plane = new Plane(QVector3D(-64,-32,64),QVector3D(-64,32,64),QVector3D(-32,64,64)));
    planes.prepend(plane = new Plane(QVector3D(-64,32,0),QVector3D(-64,-32,0),QVector3D(-32,-64,0)));
    planes.prepend(plane = new Plane(QVector3D(-64,-32,0),QVector3D(-64,32,0),QVector3D(-64,32,64)));
    planes.prepend(plane = new Plane(QVector3D(64,32,0),QVector3D(64,-32,0),QVector3D(64,-32,64)));
    planes.prepend(plane = new Plane(QVector3D(-32,64,0),QVector3D(32,64,0),QVector3D(32,64,64)));
    planes.prepend(plane = new Plane(QVector3D(32,-64,0),QVector3D(-32,-64,0),QVector3D(-32,-64,64)));
    planes.prepend(plane = new Plane(QVector3D(32,64,0),QVector3D(64,32,0),QVector3D(64,32,64)));
    planes.prepend(plane = new Plane(QVector3D(64,-32,0),QVector3D(32,-64,0),QVector3D(32,-64,64)));
    planes.prepend(plane = new Plane(QVector3D(-32,-64,0),QVector3D(-64,-32,0),QVector3D(-64,-32,64)));
    planes.prepend(plane = new Plane(QVector3D(-64,32,0),QVector3D(-32,64,0),QVector3D(-32,64,64)));
    Brush *brush = new Brush(planes);

    QList<QPolygonF> polys = Polygoniser::poligonise(brush, X_AXIS, Y_AXIS);

    QVector<QPointF> Shape1; Shape1   <<    QPointF(32,-64)  << QPointF(64,-32);
    QVector<QPointF> Shape2; Shape2   <<    QPointF(-32,-64) << QPointF(-64,-32);
    QVector<QPointF> Shape3; Shape3   <<    QPointF(-64,32)  << QPointF(-32,64);
    QVector<QPointF> Shape4; Shape4   <<    QPointF(64,32)   << QPointF(32,64);
    QVector<QPointF> Shape5; Shape5   <<    QPointF(-64,-32) << QPointF(-64,32);
    QVector<QPointF> Shape6; Shape6   <<    QPointF(64,-32)  << QPointF(64,32);
    QVector<QPointF> Shape7; Shape7   <<    QPointF(-32,64)  << QPointF(32,64);
    QVector<QPointF> Shape8; Shape8   <<    QPointF(-32,-64) << QPointF(32,-64);
    QVector<QPointF> Shape9; Shape9   <<    QPointF(-32,-64) << QPointF(32,-64) << QPointF(64,-32) << QPointF(64,32) << QPointF(32,64) << QPointF(-32,64) << QPointF(-64,32) << QPointF(-64,-32);
    QVector<QPointF> Shape10; Shape10 <<    QPointF(-32,-64) << QPointF(32,-64) << QPointF(64,-32) << QPointF(64,32) << QPointF(32,64) << QPointF(-32,64) << QPointF(-64,32) << QPointF(-64,-32);

    QVERIFY(polys.contains(QPolygonF(Shape1)));
    QVERIFY(polys.contains(QPolygonF(Shape2)));
    QVERIFY(polys.contains(QPolygonF(Shape3)));
    QVERIFY(polys.contains(QPolygonF(Shape4)));
    QVERIFY(polys.contains(QPolygonF(Shape5)));
    QVERIFY(polys.contains(QPolygonF(Shape6)));
    QVERIFY(polys.contains(QPolygonF(Shape7)));
    QVERIFY(polys.contains(QPolygonF(Shape8)));
    QVERIFY(polys.contains(QPolygonF(Shape9)));
    QVERIFY(polys.contains(QPolygonF(Shape10)));

}
