#include "brush.h"
//!
//! \brief Plane::Plane Contruct a plane with 3 vertex
//! \param bot_left - Defines the bottom left vertex
//! \param top_left - Defines the top left vertex
//! \param top_right - Defines the top right vertex
//!
Plane::Plane(QVector3D bot_left, QVector3D top_left, QVector3D top_right) {
    if(!checkValid(bot_left, top_left, top_right)) {
        m_bot_left = bot_left;
        m_top_left = top_left;
        m_top_right = top_right;
    }
}
void Plane::setBotLeft(QVector3D bot_left) {
    if(!checkValid(bot_left, m_top_left, m_top_right)) {
        m_bot_left = bot_left;
    }
}
void Plane::setTopRight(QVector3D top_right) {
    if(!checkValid(m_bot_left, m_top_left, top_right)) {
        m_top_right = top_right;
    }
}
void Plane::setTopLeft(QVector3D top_left) {
    if(!checkValid(m_bot_left, top_left, m_top_right)) {
        m_top_left = top_left;
    }
}
QVector3D Plane::getBotLeft() {
    return m_bot_left;
}
QVector3D Plane::getTopRight() {
    return m_top_right;
}
QVector3D Plane::getTopLeft() {
    return m_top_left;
}

//!
//! \brief Plane::checkValid check that each vertex is unique
//! \param bot_left
//! \param top_left
//! \param top_right
//! \return
//!
bool Plane::checkValid(QVector3D bot_left, QVector3D top_left, QVector3D top_right) {
    if (bot_left == top_left ||
            bot_left == top_right ||
            top_left == top_right) {
        qWarning("registered an invalid plane");
        return 1;
    }
    else
        return 0;
}

Brush::Brush(QList<Plane *> planes) {
       if(!checkValid(planes))
           m_planes = planes;
}

//!
//! \brief checkValid
//! The whole system relies on the fact that you cant have more than one face
//! on the same plane, this iterates the entire list of planes to check this.
//! \param planes
//! \return
//!
bool Brush::checkValid(QList<Plane*> planes) {
    Plane *plane;
    Plane *plane2;
    foreach (plane, planes) {
        foreach (plane2, planes) {
            if(plane != plane2) {
                if(plane->getBotLeft().distanceToPlane(plane2->getBotLeft(),
                                                       plane2->getTopLeft(),
                                                       plane2->getTopRight()) == 0)
                    if(plane->getTopLeft().distanceToPlane(plane2->getBotLeft(),
                                                           plane2->getTopLeft(),
                                                           plane2->getTopRight()) == 0)
                        if(plane->getTopRight().distanceToPlane(plane2->getBotLeft(),
                                                                plane2->getTopLeft(),
                                                                plane2->getTopRight()) == 0 ) {
                            qWarning("registered an invalid block");
                            return 1;
                        }
            }
        }
    }
    return 0;
}

int Brush::getNumOfSides() {
    return m_planes.size();
}
