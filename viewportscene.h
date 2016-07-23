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
#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QGraphicsScene>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QGraphicsItemGroup>
#include "brush.h"
//!
//! \brief The ViewPortScene class
//! The view port for editing the 3d brushes in 2 dimensions
//!
class ViewPortScene : public QGraphicsScene
{
    Q_OBJECT
    int roundGrid(int input, int units);
    QGraphicsItemGroup brushes;

public:
    ViewPortScene();
    void drawBackground(QPainter *painter, const QRectF &rect);
    int m_default_size;
    qreal m_scale;
    int m_grid;

    Brush *m_brush;
    axis m_primary;
    axis m_secondary;
    void addBrush(Brush *brush);



private:
    void drawGrid(int units, QPen pen, QPainter *painter, const QRectF &rect);

public slots:
    void setScale(qreal scale);
    void setGrid(bool step);
};



#endif // VIEWPORT_H
