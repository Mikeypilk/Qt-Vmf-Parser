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

    QPen pen(QColor("pink"));

    // How to add something to the group
    //    QGraphicsRectItem *rect = new QGraphicsRectItem;
    //    rect->setRect(0,0,1024,1024);
    //    rect->setPen(pen);
    //    brushes.addToGroup(rect);
    this->addItem(&brushes);
    brushes.show();


    QList<Plane*> planes;
    //  Plane *plane;
    //  planes.prepend(plane = new Plane(QVector3D(-128, 32, 128),QVector3D(128, 32, 128),QVector3D(128, 0, 128)));
    //  planes.prepend(plane = new Plane(QVector3D(-128, 0, 0),QVector3D(128, 0, 0),QVector3D(128, 32, 0)));
    //  planes.prepend(plane = new Plane(QVector3D(-128, 32, 128),QVector3D(-128, 0, 128),QVector3D(-128, 0, 0)));
    //  planes.prepend(plane = new Plane(QVector3D(128, 32, 0),QVector3D(128, 0, 0),QVector3D(128, 0, 128)));
    //  planes.prepend(plane = new Plane(QVector3D(128, 32, 128),QVector3D(-128, 32, 128),QVector3D(-128, 32, 0)));
    //  planes.prepend(plane = new Plane(QVector3D(128, 0, 0),QVector3D(-128, 0, 0),QVector3D(-128, 0, 128)));
    //  Brush brush(planes);

    //    planes.prepend(plane = new Plane(QVector3D(64, 32, 128),QVector3D(128, 32, 128),QVector3D(128, 16, 128)));
    //    planes.prepend(plane = new Plane(QVector3D(64, 16, 16),QVector3D(128, 16, 16),QVector3D(128, 32, 16)));
    //    planes.prepend(plane = new Plane(QVector3D(64, 32, 128),QVector3D(64, 16, 128),QVector3D(64, 16, 16)));
    //    planes.prepend(plane = new Plane(QVector3D(128, 32, 16),QVector3D(128, 16, 16),QVector3D(128, 16, 128)));
    //    planes.prepend(plane = new Plane(QVector3D(128, 32, 128),QVector3D(64, 32, 128),QVector3D(64, 32, 16)));
    //    planes.prepend(plane = new Plane(QVector3D(128, 16, 16),QVector3D(64, 16, 16),QVector3D(64, 16, 128)));
    //    Brush brush(planes);

    //  brush.rotate(Brush::X_AXIS, Brush::Z_AXIS, 45);
    //  brush.rotate(Brush::Y_AXIS, Brush::Z_AXIS, 45);

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


//    Plane *plane;
//    planes.prepend(plane = new Plane(QVector3D(32, -32, 64),QVector3D(-32, -32, 64),QVector3D(-32, 32, 64)));
//    planes.prepend(plane = new Plane(QVector3D(-32, -32, 0),QVector3D(32, -32, 0),QVector3D(32, 32, 0)));
//    planes.prepend(plane = new Plane(QVector3D(48, -48, 16),QVector3D(32, -64, 32),QVector3D(48, -48, 48)));
//    planes.prepend(plane = new Plane(QVector3D(-48, -48, 48),QVector3D(-32, -64, 32),QVector3D(-48, -48, 16)));
//    planes.prepend(plane = new Plane(QVector3D(-48, 48, 16),QVector3D(-32, 64, 32),QVector3D(-48, 48, 48)));
//    planes.prepend(plane = new Plane(QVector3D(64, 32, 32),QVector3D(48, 48, 48),QVector3D(32, 64, 32)));
//    planes.prepend(plane = new Plane(QVector3D(-32, 32, 0),QVector3D(32, 32, 0),QVector3D(48, 48, 16)));
//    planes.prepend(plane = new Plane(QVector3D(-32, -32, 0),QVector3D(-32, -32, 0),QVector3D(-48, -48, 16)));
//    planes.prepend(plane = new Plane(QVector3D(32, 32, 0),QVector3D(32, -32, 0),QVector3D(48, -48, 16)));
//    planes.prepend(plane = new Plane(QVector3D(-32, -32, 0),QVector3D(-32, 32, 0),QVector3D(-48, 48, 16)));
//    planes.prepend(plane = new Plane(QVector3D(-32, -64, 32),QVector3D(-48, -48, 48),QVector3D(-32, -32, 64)));
//    planes.prepend(plane = new Plane(QVector3D(32, 64, 32),QVector3D(48, 48, 48),QVector3D(32, 32, 64)));
//    planes.prepend(plane = new Plane(QVector3D(-64, 32, 32),QVector3D(-48, 48, 48),QVector3D(-32, 32, 64)));
//    planes.prepend(plane = new Plane(QVector3D(64, 32, 32),QVector3D(64, -32, 32),QVector3D(48, -48, 48)));
   Brush brush(planes);

    addBrush(&brush);

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
    QList<Plane*> planes = brush->getPlanes();
#define SMALL_NUM   0.00001

    foreach(Plane *pla1, planes) {
        QVector<QPointF> list;

        foreach(Plane *pla2, planes) {
            QVector3D Pn1 = QVector3D::normal(pla1->getTopRight(), pla1->getTopLeft(), pla1->getBotLeft() );
            QVector3D Po1 = pla1->getTopRight();
            QVector3D Pn2 = QVector3D::normal(pla2->getTopRight(), pla2->getTopLeft(), pla2->getBotLeft() );
            QVector3D Po2 = pla2->getTopLeft();
            QVector3D u = QVector3D::crossProduct(Pn1, Pn2);          // cross product

            float    ax = (u.x() >= 0 ? u.x() : -u.x());
            float    ay = (u.y() >= 0 ? u.y() : -u.y());
            float    az = (u.z() >= 0 ? u.z() : -u.z());

            if ((ax+ay+az) < SMALL_NUM) {        // Pn1 and Pn2 are near parallel
                QVector3D v = Po2 - Po1;
                if (QVector3D::dotProduct(Pn1, v) == 0) {
                    qDebug() << "Pn1 and Pn2 coincide";
                    continue;
                }
                else {
                    qDebug() << "Pn1 and Pn2 are parrallel";
                    continue;
                }
            }
            qDebug() << "Pn1 and Pn2 are connected";
            if(pla2->getBotLeft().distanceToPlane(pla1->getBotLeft(),
                                                  pla1->getTopLeft(),
                                                  pla1->getTopRight()) < 8)
                list.append( QPointF(pla2->getBotLeft().x(), pla2->getBotLeft().y()) );
            if(pla2->getTopLeft().distanceToPlane(pla1->getBotLeft(),
                                                  pla1->getTopLeft(),
                                                  pla1->getTopRight()) < 8)
                list.append( QPointF(pla2->getTopLeft().x(), pla2->getTopLeft().y()) );
            if(pla2->getTopRight().distanceToPlane(pla1->getBotLeft(),
                                                   pla1->getTopLeft(),
                                                   pla1->getTopRight()) < 8)
                list.append( QPointF(pla2->getTopRight().x(), pla2->getTopRight().y()) );
        }

        // Remove any duplicates
        if(!list.empty()) {
            foreach(QPointF point, list) {
                if(list.contains(point)) {
                    list.removeAll(point);
                    list.append(point);
                }
            }
            list = convexHull(list);
        }
        qDebug() << list;

        for(int j=0; j<list.size(); j++) {
            list[j].setX(list[j].x() * -64);
            list[j].setY(list[j].y() * -64);
        }

        //qDebug() << points;
        QPolygonF poly(list);
        poly.translate(32768*32,32768*32);

        brushes.addToGroup(new QGraphicsPolygonItem(poly));


        qDebug() << "------------------------------";
    }
}

QPointF p0;

// A utility function to find next to top in a stack
QPointF ViewPortScene::nextToTop(QStack<QPointF> &S)
{
    QPointF p = S.takeFirst();
    S.pop();
    QPointF res = S.top();
    S.push(p);
    return res;

}

// A utility function to return square of distance
// between p1 and p2
int ViewPortScene::distSq(QPointF p1, QPointF p2)
{
    return (p1.x() - p2.x())*(p1.x() - p2.x()) +
          (p1.y() - p2.y())*(p1.y() - p2.y());
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int ViewPortScene::orientation(QPointF p, QPointF q, QPointF r)
{
    int val = (q.y() - p.y()) * (r.x() - q.x()) -
              (q.x() - p.x()) * (r.y() - q.y());

    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}

// A function used by library function qsort() to sort an array of
// points with respect to the first point
int ViewPortScene::compare(const void *vp1, const void *vp2)
{
   QPointF *p1 = (QPointF *)vp1;
   QPointF *p2 = (QPointF *)vp2;

   // Find orientation
   int o = orientation(p0, *p1, *p2);
   if (o == 0)
     return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1;

   return (o == 2)? -1: 1;
}
QVector<QPointF> ViewPortScene::convexHull(QVector<QPointF> points)
{
   int n = points.size();
   // Find the bottommost point
   int ymin = points[0].y(), min = 0;
   for (int i = 1; i < n; i++)
   {
     int y = points[i].y();

     // Pick the bottom-most or chose the left
     // most point in case of tie
     if ((y < ymin) || (ymin == y &&
         points[i].x() < points[min].x()))
        ymin = points[i].y(), min = i;
   }

   // Place the bottom-most point at first position
   QPointF temp = points.at(0);
   points[0] = points[min];
   points[min] = temp;

   points[0];

   // Sort n-1 points with respect to the first point.
   // A point p1 comes before p2 in sorted ouput if p2
   // has larger polar angle (in counterclockwise
   // direction) than p1
   p0 = points[0];
   qsort(&points[1], n-1, sizeof(QPointF), &ViewPortScene::compare);
   // If two or more points make same angle with p0,
   // Remove all but the one that is farthest from p0
   // Remember that, in above sorting, our criteria was
   // to keep the farthest point at the end when more than
   // one points have same angle.
   int m = 1; // Initialize size of modified array
   for (int i=1; i<n; i++)
   {
       // Keep removing i while angle of i and i+1 is same
       // with respect to p0
       while (i < n-1 && orientation(p0, points[i],
                                    points[i+1]) == 0)
          i++;


       points[m] = points[i];
       m++;  // Update size of modified array
   }

   // If modified array of points has less than 3 points,
   // convex hull is not possible
   if (m < 3) return points;

   // Create an empty stack and push first three points
   // to it.
   QStack<QPointF> S;
   S.push(points[0]);
   S.push(points[1]);
   S.push(points[2]);

   // Process remaining n-3 points
   for (int i = 3; i < m; i++)
   {
      // Keep removing top while the angle formed by
      // points next-to-top, top, and points[i] makes
      // a non-left turn
      while (orientation(nextToTop(S), S.top(), points[i]) != 2)
         S.pop();
      S.push(points[i]);
   }

   // Now stack has the output points, print contents of stack
   while (!S.empty())
   {
       QPointF p = S.top();
       qDebug() << "(" << p.x() << ", " << p.y() <<")";
       S.pop();
   }
   return points;
}
