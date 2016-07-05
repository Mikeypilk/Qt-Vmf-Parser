#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "brush.h"

#define GRID_INCREMENT 0
#define GRID_DECREMENT 1
#define MAX_UNITS 2097152

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionGridincrement_triggered()
{
    emit(changeGrid(GRID_INCREMENT));
}

void MainWindow::on_actionGridDecrement_triggered()
{
    emit(changeGrid(GRID_DECREMENT));
}

void MainWindow::on_actionInstantiateBlock_triggered()
{
    emit(instantiateBlock());
}

void MainWindow::on_actionNewBlock_triggered()
{
    emit(newBlockMode());
}
