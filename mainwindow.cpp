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
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qlabel.h>

#define GRID_INCREMENT 0
#define GRID_DECREMENT 1
#define MAX_UNITS 2097152
//!
//! \brief MainWindow::MainWindow
//! \param parent
//!
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    this->setWindowTitle("World Editor");
    QLabel *label = new QLabel("Status Bar: ");

    ui->statusBar->addWidget(label);

    for(int i = 0; i < 3; i++) {
        ViewPortView *view;
        ViewPortScene *scene;
        switch(i) {
        case 0:
            // Bottom Left
            view = ui->graphicsView_1;
            scene = m_scene_1;
            scene  = new ViewPortScene(&model, Y_AXIS, Z_AXIS);
            break;
        case 1:
            // Bottom Right
            view = ui->graphicsView_2;
            scene = m_scene_2;
            scene  = new ViewPortScene(&model, X_AXIS, Z_AXIS);
            break;
        case 2:
            // Top Right
            view = ui->graphicsView_3;
            scene = m_scene_2;
            scene  = new ViewPortScene(&model, X_AXIS, Y_AXIS);
            break;
        }
        //scene
        scene->setSceneRect(0,0,MAX_UNITS,MAX_UNITS);

        //view
        view->setScene(scene);
        view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
        view->setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing, true);

        // model signals
        connect(&model, SIGNAL(rowsInserted(QModelIndex,int,int)),
                scene, SLOT(addBrush(QModelIndex,int,int)));
        connect(view, SIGNAL(scaleChanged(qreal)),scene,SLOT(setScale(qreal)));
        connect(this, SIGNAL(changeGrid(bool)),scene,SLOT(setGrid(bool)));
        connect(this, SIGNAL(instantiateBlock()),scene, SLOT(makeNewBlock()));
        connect(this, SIGNAL(newBlockMode()), scene, SLOT(setNewBlockMode()));
        connect(this, SIGNAL(changeViewPortMode(MOUSE_INTERACT_MODE)),
                scene, SLOT(setMouseMode(MOUSE_INTERACT_MODE)));
    }
    // Test shape
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
    Brush brush(planes);
    model.addBrush(brush);
}
//!
//! \brief MainWindow::~MainWindow
//!
MainWindow::~MainWindow()
{
    delete ui;
}
//!
//! \brief MainWindow::on_actionGridincrement_triggered
//!
void MainWindow::on_actionGridincrement_triggered()
{
    emit(changeGrid(GRID_INCREMENT));
}
//!
//! \brief MainWindow::on_actionGridDecrement_triggered
//!
void MainWindow::on_actionGridDecrement_triggered()
{
    emit(changeGrid(GRID_DECREMENT));
}
//!
//! \brief MainWindow::on_actionInstantiateBlock_triggered
//!
void MainWindow::on_actionInstantiateBlock_triggered()
{
}
//!
//! \brief MainWindow::on_actionNewBlock_triggered
//!
void MainWindow::on_actionNewBlock_triggered()
{
    emit(changeViewPortMode(NEW));
}
//!
//! \brief MainWindow::on_actionSelect_triggered
//!
void MainWindow::on_actionSelect_triggered()
{
    emit(changeViewPortMode(SELECT));
}
