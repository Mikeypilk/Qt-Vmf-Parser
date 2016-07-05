#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "viewportscene.h"
#include "viewportview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    ViewPortScene XZ_scene;
    ViewPortScene YZ_scene;
    ViewPortScene XY_scene;

signals:
    void changeGrid(bool);
    void instantiateBlock();
    void newBlockMode();

private slots:
    void on_actionGridincrement_triggered();
    void on_actionGridDecrement_triggered();
    void on_actionInstantiateBlock_triggered();
    void on_actionNewBlock_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
