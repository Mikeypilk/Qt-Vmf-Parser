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
/*
 * Source: http://www.geeksforgeeks.org/convex-hull-set-2-graham-scan/
 *
*/

#include "polygoniser.h"

//! first point.
static QPointF p0;

//!
//! \brief Polygoniser::turns a list of points into a convex polygon
//! \param points
//! \return
//!
QPolygonF Polygoniser::poligonise(QVector<QPointF> points) {
    points = convexHull(points);
    return QPolygonF(points);
}

//!
//! \brief Polygoniser::planesConnected
//! \param u cross product
//! \return true - planes are connected, false - planes are parrallel in some way
//!
bool Polygoniser::planesConnected(QVector3D u)
{
#define SMALL_NUM   0.001
    float    ax = (u.x() >= 0 ? u.x() : -u.x());
    float    ay = (u.y() >= 0 ? u.y() : -u.y());
    float    az = (u.z() >= 0 ? u.z() : -u.z());
    if ((ax+ay+az) < SMALL_NUM) {        // Pn1 and Pn2 are near parallel
        return false; // "Pn1 and Pn2 are parrallel";
    }
    return true; // Pn1 and Pn2 are connected in some way
}

//!
//! \brief Polygoniser::poligonise
//! \param brush
//! \return
//!
QList<QPolygonF> Polygoniser::poligonise(Brush *brush, axis primary, axis secondary) {
    QList<QPolygonF> polygons;
    QList<Plane*> planes = brush->getPlanes();
    foreach(Plane *pla1, planes) {
        // List of points that intersect the plane
        QVector<QPointF> list;
        foreach(Plane *pla2, planes) {

            QVector3D crossProduct = QVector3D::crossProduct(
                        QVector3D::normal(pla1->getTopRight(), pla1->getTopLeft(), pla1->getBotLeft()),
                        QVector3D::normal(pla2->getTopRight(), pla2->getTopLeft(), pla2->getBotLeft())
                        );

            // If the planes are parrallel dont bother...
            if(!planesConnected(crossProduct)) {
                continue;
            }

            // Pn1 and Pn2 are connected
            if(pla2->getBotLeft().distanceToPlane(pla1->getBotLeft(),
                                                  pla1->getTopLeft(),
                                                  pla1->getTopRight()) < 0.5)
                list.append(toPointF(pla2->getBotLeft(), primary, secondary));

            if(pla2->getTopLeft().distanceToPlane(pla1->getBotLeft(),
                                                  pla1->getTopLeft(),
                                                  pla1->getTopRight()) < 0.5)
                list.append(toPointF(pla2->getTopLeft(), primary, secondary));

            if(pla2->getTopRight().distanceToPlane(pla1->getBotLeft(),
                                                   pla1->getTopLeft(),
                                                   pla1->getTopRight()) < 0.5)
                list.append(toPointF(pla2->getTopRight(), primary, secondary));
        }

        list.append(toPointF(pla1->getBotLeft(),primary,secondary));
        list.append(toPointF(pla1->getTopLeft(),primary,secondary));
        list.append(toPointF(pla1->getTopRight(),primary,secondary));

        // Remove any duplicates
        if(!list.empty()) {
            foreach(QPointF point, list) {
                if(list.contains(point)) {
                    list.removeAll(point);
                    list.append(point);
                }
            }

            polygons.append( convexHull(list) );
        }
    }
    return polygons;
}
//!
//! \brief Polygoniser::nextToTop next to top in a stack of points
//! A utility function to find next to top in a stack of points
//! \param S Stack of points
//! \return next to top point
QPointF Polygoniser::nextToTop(QStack<QPointF> &S)
{
    QPointF p = S.takeFirst();
    S.pop();
    QPointF res = S.top();
    S.push(p);
    return res;

}
//!
//! \brief Polygoniser::distSq square distance p1 and p2
//! A utility function to return square of distance between p1 and p2
//! \param p1 first point
//! \param p2 second point
//! \return square distance p1 and p2
//!
int Polygoniser::distSq(QPointF p1, QPointF p2)
{
    return (p1.x() - p2.x())*(p1.x() - p2.x()) +
            (p1.y() - p2.y())*(p1.y() - p2.y());
}

//!
//! \brief Polygoniser::orientation To find orientation of ordered triplet.
//! \param p
//! \param q
//! \param r
//! \return The function returns following values
//! 0 --> p, q and r are colinear
//! 1 --> Clockwise
//! 2 --> Counterclockwise
//!
int Polygoniser::orientation(QPointF p, QPointF q, QPointF r)
{
    int val = (q.y() - p.y()) * (r.x() - q.x()) -
            (q.x() - p.x()) * (r.y() - q.y());

    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}

//!
//! \brief Polygoniser::compare
//! A function used by library function qsort() to sort an array of
//! points with respect to the first point. A point p1 comes before p2 in sorted
//! ouput if p2 has larger polar angle (in counterclockwise direction) than p1
//! \param vp1
//! \param vp2
//! \return 1 after, -1 before
//!
int Polygoniser::compare(const void *vp1, const void *vp2)
{
    QPointF *p1 = (QPointF *)vp1;
    QPointF *p2 = (QPointF *)vp2;

    // Find orientation
    int o = orientation(p0, *p1, *p2);
    if (o == 0)
        return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1;

    return (o == 2)? -1: 1;
}
//!
//! \brief Polygoniser::convexHull Graham Scan - Convex Hull Algorithm
//! Returns a list of points which have been ordered such that they form
//! a convex polygon.
//! \param points Input list of points
//! \return
//!
QVector<QPointF> Polygoniser::convexHull(QVector<QPointF> points)
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
    p0 = points[0];
    qsort(&points[1], n-1, sizeof(QPointF), &Polygoniser::compare);

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
        //qDebug() << "(" << p.x() << ", " << p.y() <<")";
        S.pop();
    }
    return points;
}

//!
//! \brief Polygoniser::toPointF
//! \param vector 3D input vector
//! \param primary first coordinate axis
//! \param secondary second coordinate axis
//! \return point in primary and secondary axis
//!
QPointF Polygoniser::toPointF(QVector3D vector, axis primary, axis secondary) {

    QPointF output;

    if(primary == secondary) {
        qWarning("primary=secondary");
        return QPointF();
    }
    switch (primary) {
    case X_AXIS:
        output.setX(vector.x());
        break;
    case Y_AXIS:
        output.setX(vector.y());
        break;
    case Z_AXIS:
        output.setX(vector.z());
        break;
    default:
        break;
    }
    switch (secondary) {
    case X_AXIS:
        output.setY(vector.x());
        break;
    case Y_AXIS:
        output.setY(vector.y());
        break;
    case Z_AXIS:
        output.setY(vector.z());
        break;
    default:
        break;
    }
    return output;
}
