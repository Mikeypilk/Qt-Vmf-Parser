#ifndef PLANE_H
#define PLANE_H

#include <QObject>
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
    Plane(QVector3D bot_left, QVector3D top_left, QVector3D top_right) {
        m_bot_left = bot_left;
        m_top_left = top_left;
        m_top_right = top_right;
    }
    void setBotLeft(QVector3D bot_left) {
        m_bot_left = bot_left;
    }
    void setTopRight(QVector3D top_right) {
        m_top_right = top_right;
    }
    void setTopLeft(QVector3D top_left) {
        m_top_left = top_left;
    }
    QVector3D getBotLeft() {
        return m_bot_left;
    }
    QVector3D getTopRight() {
        return m_top_right;
    }
    QVector3D getTopLeft() {
        return m_top_left;
    }
};

#endif // PLANE_H
