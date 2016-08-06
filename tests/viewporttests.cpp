#include "viewporttests.h"

void ViewPortTests::testAddBlock() {

    Solids newSolids;
    ViewPortScene scene(&newSolids, X_AXIS, Y_AXIS);
    connect(&newSolids, SIGNAL(rowsInserted(QModelIndex,int,int)),
            &scene, SLOT(addBrush(QModelIndex,int,int)));

    int before = scene.items().count();
    Plane *plane;
    QList<Plane*> planes;
    planes.prepend(plane = new Plane(QVector3D(-128, 32, 128),QVector3D(128, 32, 128),QVector3D(128, 0, 128)));
    planes.prepend(plane = new Plane(QVector3D(-128, 0, 0),QVector3D(128, 0, 0),QVector3D(128, 32, 0)));
    planes.prepend(plane = new Plane(QVector3D(-128, 32, 128),QVector3D(-128, 0, 128),QVector3D(-128, 0, 0)));
    planes.prepend(plane = new Plane(QVector3D(128, 32, 0),QVector3D(128, 0, 0),QVector3D(128, 0, 128)));
    planes.prepend(plane = new Plane(QVector3D(128, 32, 128),QVector3D(-128, 32, 128),QVector3D(-128, 32, 0)));
    planes.prepend(plane = new Plane(QVector3D(128, 0, 0),QVector3D(-128, 0, 0),QVector3D(-128, 0, 128)));
    Brush brush(planes);
    newSolids.addSolid(brush);
    int after = scene.items().count();
    QVERIFY(after - before == 6);

}

