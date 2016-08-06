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
#include "solids.h"
#include "maptests.h"
#include "QSignalSpy"

//!
//! \brief MapTests::init
//!
void MapTests::init() {

}

//!
//! \brief MapTests::testInsertBrush
//!
void MapTests::testInsertBrush() {

    Solids newSolids;
    QSignalSpy spy(&newSolids, SIGNAL(rowsInserted(QModelIndex,int,int)));

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

    QCOMPARE(spy.count(), 1); // make sure the signal was emitted exactly one time
}

//!
//! \brief MapTests::testReturnBrush
//!
void MapTests::testReturnBrush() {

    Solids newSolids;
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

    QVariant output = newSolids.index(0,0).data(Solids::BrushRole);
    Brush s2 = output.value<Brush>();
    QCOMPARE(s2.getCenter(X_AXIS, Y_AXIS), QVector2D(0,16));

}

void MapTests::testReadVMF() {
    Map map;
    map.readVMF(":/vmfs/testBox.vmf");




}
