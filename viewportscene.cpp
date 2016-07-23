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


#include "viewportscene.h"
#define GRID_INCREMENT 0
#define GRID_DECREMENT 1
//!
//! \brief ViewPortScene::ViewPortScene
//!
ViewPortScene::ViewPortScene()
{
    m_scale = 8;

    m_grid = 1;

    QBrush background("black");
    setBackgroundBrush(background);
    // How to add something to the group
    //    QGraphicsRectItem *rect = new QGraphicsRectItem;
    //    rect->setRect(0,0,1024,1024);
    //    rect->setPen(pen);
    //    brushes.addToGroup(rect);
    this->addItem(&brushes);
    brushes.show();
    setScale(m_scale);

}
//!
//! \brief ViewPortScene::drawBackground
//! \param painter
//! \param rect
//!
void ViewPortScene::drawBackground(QPainter *painter, const QRectF &rect) {

    // Get the coordinates of the viewport rectangle;
    // We only want to remake the lines when the viewport is either zoomed or panned
    QGraphicsScene::drawBackground(painter, rect);

    QPen pen(QColor(128, 128, 128), 1*(m_scale/32), Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin);

    qreal major = m_scale/16;
    qreal minor = m_scale/32;
    if(major < 1) {
        major = 1;
    }
    if(minor < 1) {
        minor = 1;
    }
    if(m_scale < 150) {
        pen.setColor(QColor("light gray").lighter(50));
        pen.setWidth(minor);
        drawGrid(m_grid, pen, painter, rect);
        pen.setColor(QColor("light gray"));
        pen.setWidth(major);
        if(m_grid <= 8)
            drawGrid(8, pen, painter, rect);
    }
    pen.setWidth(major);
    int zoom = 150;
    int grid = 8;
    for(int i = 1; i < 8; i++) {
        if ((m_scale > zoom) && (m_scale < zoom*2)){
            if(m_grid > grid) {
                drawGrid(m_grid,pen,painter,rect);
            }
            else {
                drawGrid(grid,pen,painter,rect);
            }
        }
        zoom = zoom * 2;
        grid = grid * 2;
    }
    // 1024 Step Lines
    pen.setColor(QColor("dark orange").darker(200));
    drawGrid(1024,pen,painter,rect);
    // Center cross lines
    pen.setWidth(major*2);
    pen.setColor(QColor("dark red").darker(200));
    drawGrid(16384,pen,painter,rect);
}
//!
//! \brief ViewPortScene::drawGrid
//! \param units
//! \param pen
//! \param painter
//! \param rect
//!
void ViewPortScene::drawGrid(int units, QPen pen, QPainter *painter, const QRectF &rect) {

    qreal x1, x2, y1, y2;
    rect.getCoords(&x1,&y1,&x2,&y2);
    painter->setPen(pen);

    pen.setWidth(pen.width()*(units/8));
    int startx = roundGrid(x1, units);
    int starty = roundGrid(y1, units);
    int endx = roundGrid(x2, units);
    int endy = roundGrid(y2, units);

    if( (startx < 0) || ( starty < 0 ) || (endx < 32768) || (endy < 32768) ){
        for(int i = 0; i<=32768*64; i=i+(units*64)) {
            painter->drawLine(i,0,i,32768*64);
        }
        for(int i = 0; i<=32768*64; i=i+(units*64)) {
            painter->drawLine(0,i,32768*64,i);
        }
    }
    else {
        for(int i = startx; i<x2; i=i+(units*64)) {
            painter->drawLine(i,starty,i,y2);
        }
        for(int i = starty; i<y2; i=i+(units*64)) {
            painter->drawLine(startx,i,x2,i);
        }
    }
}
//!
//! \brief ViewPortScene::roundGrid rounds the input to the nearest units
//! \param input
//! \param units
//! \return
//!
int ViewPortScene::roundGrid(int input, int units) {
    units = (units *64)-1;
    return (int)(input & ~units);
}
//!
//! \brief ViewPortScene::setScale
//! \param scale
//!
void ViewPortScene::setScale(qreal scale) {
    m_scale = scale;
    foreach(QGraphicsItem *itm, brushes.childItems()) {
        QGraphicsPolygonItem *pol = qgraphicsitem_cast<QGraphicsPolygonItem*>(itm);
        QBrush outline(QColor("pink"));
        pol->setPen(QPen(outline, m_scale/8, Qt::DashLine));
    }
}
//!
//! \brief ViewPortScene::setGrid changes the grid depth
//! \param step 0 for increment, 1 for decrement
//!
void ViewPortScene::setGrid(bool step) {
    switch(step) {
    case GRID_INCREMENT:
        if(m_grid !=1024)
            m_grid = m_grid*2;
        break;
    case GRID_DECREMENT:
        if(m_grid !=1)
            m_grid = m_grid/2;
        break;
    }
    // Causes the scene to redraw its contents
    this->invalidate(this->sceneRect());
}
//!
//! \brief ViewPortScene::addBrush
//! \param brush
//!
void ViewPortScene::addBrush(Brush *brush) {

    //        for(int j=0; j<list.size(); j++) {
    //            list[j].setX(list[j].x() * -64);
    //            list[j].setY(list[j].y() * -64);
    //        }

    //qDebug() << points;
//    QPolygonF poly(list);
//    poly.translate(32768*32,32768*32);

//    brushes.addToGroup(new QGraphicsPolygonItem(poly));

}

