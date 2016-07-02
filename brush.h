#ifndef BRUSH_H
#define BRUSH_H

#include <QObject>
#include <QtCore>
#include <QVector3D>

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
};

class Brush
{
    QList<Plane*> m_planes;
public:
    Brush(QList<Plane*> planes);
    bool checkValid(QList<Plane*> planes);
    int getNumOfSides();
};

#endif // BRUSH_H
