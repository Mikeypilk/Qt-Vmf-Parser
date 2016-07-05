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

    XY_scene.setSceneRect(0,0,MAX_UNITS,MAX_UNITS);
    ui->graphicsView->setScene(&XY_scene);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    ui->graphicsView->setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing, true);
    connect(ui->graphicsView, SIGNAL(scaleChanged(qreal)),&XY_scene,SLOT(setScale(qreal)));
    connect(this, SIGNAL(changeGrid(bool)),&XY_scene,SLOT(setGrid(bool)));
    connect(this, SIGNAL(instantiateBlock()),&XY_scene, SLOT(makeNewBlock()));
    connect(this, SIGNAL(newBlockMode()), &XY_scene, SLOT(setNewBlockMode()));
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
    emit(instantiateBlock());
}
//!
//! \brief MainWindow::on_actionNewBlock_triggered
//!
void MainWindow::on_actionNewBlock_triggered()
{
    emit(newBlockMode());
}
