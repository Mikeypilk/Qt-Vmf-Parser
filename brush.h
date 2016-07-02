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

#ifndef BRUSH_H
#define BRUSH_H

#include <QObject>
#include <QtCore>
#include <QVector3D>
#include <QVector2D>
//!
//! \brief The Plane class represents a 2D plane
//!
class Plane
{
    QVector3D m_bot_left;
    QVector3D m_top_left;
    QVector3D m_top_right;
public:
    Plane(QVector3D bot_left, QVector3D top_left, QVector3D top_right);
    void setBotLeft(QVector3D bot_left);
    void setTopRight(QVector3D top_right);
    void setTopLeft(QVector3D top_left);
    QVector3D getBotLeft();
    QVector3D getTopRight();
    QVector3D getTopLeft();
    bool checkValid(QVector3D bot_left, QVector3D top_left, QVector3D top_right);
    QList<QVector3D*> getVertexes();

};

//!
//! \brief The Brush class represents a 3D solid
//!
class Brush
{
    QList<Plane*> m_planes;

    bool getBoundingBox();
    void setXMinMax();
    void setYMinMax();
    void setZMinMax();
    QPointF m_x_max_min;
    QPointF m_y_max_min;
    QPointF m_z_max_min;
    QList<QVector3D*> xMatch;
    QList<QVector3D*> yMatch;
    QList<QVector3D*> zMatch;

public:
    Brush(QList<Plane*> planes);
    bool checkValid(QList<Plane*> planes);
    int getNumOfSides();
    enum boundingBox {
        BOUND_BOX__TOP_LEFT,
        BOUND_BOX__TOP_RIGHT,
        BOUND_BOX__BOTTOM_RIGHT,
        BOUND_BOX__BOTTOM_LEFT,
        BOUND_BOX__LEFT,
        BOUND_BOX__TOP,
        BOUND_BOX__RIGHT,
        BOUND_BOX__BOTTOM,
    };
    enum axis {
        X_AXIS,
        Y_AXIS,
        Z_AXIS,
    };

    void matchingVertexes(axis primary, axis secondary, QVector2D checkpos);
    QVector2D getTopLeft(axis primary, axis secondary);
    QVector2D getTopRight(axis primary, axis secondary);
    QVector2D getBottomLeft(axis primary, axis secondary);
    QVector2D getBottomRight(axis primary, axis secondary);
    QVector2D getBottom(axis primary, axis secondary);
    QVector2D getTop(axis primary, axis secondary);
    QVector2D getLeft(axis primary, axis secondary);
    QVector2D getRight(axis primary, axis secondary);
    void transform(boundingBox box, axis primary, axis secondary, QPointF newpos);

};

#endif // BRUSH_H
