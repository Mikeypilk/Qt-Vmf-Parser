#include "viewportscene.h"
#include <QStyleOptionGraphicsItem>
#include <QBrush>
#include <QTextItem>
#include "brush.h"
#define GRID_INCREMENT 0
#define GRID_DECREMENT 1

ViewPortScene::ViewPortScene()
{
    m_scale = 8;
    m_grid = 1;
    QBrush background("black");
    setBackgroundBrush(background);
}

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
    pen.setColor(QColor("dark orange").darker(200));
    drawGrid(1024,pen,painter,rect);
    pen.setWidth(major*2);
    pen.setColor(QColor("dark red").darker(200));
    drawGrid(16384,pen,painter,rect);
}

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

int ViewPortScene::roundGrid(int input, int units) {
    units = (units *64)-1;
    return (int)(input & ~units);
}

void ViewPortScene::setScale(qreal scale) {
    m_scale = scale;
}

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
    this->invalidate(this->sceneRect());
}



