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

    ViewPortScene *m_scene_1;
    ViewPortScene *m_scene_2;
    ViewPortScene *m_scene_3;
    Map model;

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
