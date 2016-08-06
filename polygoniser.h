#ifndef POLYGONISER_H
#define POLYGONISER_H

#include <QVector>
#include <QPointF>
#include <QPolygonF>
#include <QVector3D>
#include <QStack>
#include <QDebug>

#include "brush.h"
//!
//! \brief The Polygoniser class
//!
class Polygoniser
{
    static int compare(const void *vp1, const void *vp2);
    static int orientation(QPointF p, QPointF q, QPointF r);
    static int distSq(QPointF p1, QPointF p2);
    static QPointF nextToTop(QStack<QPointF> &S);
    static QVector<QPointF> convexHull(QVector<QPointF> list);
    static bool planesConnected(QVector3D u);
    static QPointF toPointF(QVector3D vector, axis primary, axis secondary);

public:
   static QPolygonF poligonise(QVector<QPointF> points);
   static QList<QPolygonF> poligonise(Brush *brush, axis primary, axis secondary);

};

#endif // POLYGONISER_H
