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
//!
//! \brief Plane::setBotLeft
//! \param bot_left
//!
void Plane::setBotLeft(QVector3D bot_left) {
    if(!checkValid(bot_left, m_top_left, m_top_right)) {
        m_bot_left = bot_left;
    }
}
//!
//! \brief Plane::setTopRight
//! \param top_right
//!
void Plane::setTopRight(QVector3D top_right) {
    if(!checkValid(m_bot_left, m_top_left, top_right)) {
        m_top_right = top_right;
    }
}
//!
//! \brief Plane::setTopLeft
//! \param top_left
//!
void Plane::setTopLeft(QVector3D top_left) {
    if(!checkValid(m_bot_left, top_left, m_top_right)) {
        m_top_left = top_left;
    }
}
//!
//! \brief Plane::getBotLeft
//! \return
//!
QVector3D Plane::getBotLeft() {
    return m_bot_left;
}
//!
//! \brief Plane::getTopRight
//! \return
//!
QVector3D Plane::getTopRight() {
    return m_top_right;
}
//!
//! \brief Plane::getTopLeft
//! \return
//!
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
//!
//! \brief Brush::Brush
//! \param planes
//!
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
//!
//! \brief Brush::getNumOfSides
//! \return
//!
int Brush::getNumOfSides() {
    return m_planes.size();
}
//!
//! \brief Brush::setXMinMax
//!
void Brush::setXMinMax() {
    QPointF result;
    qreal f=0;
    Plane *plane;
    foreach (plane, m_planes) {
        if(plane->getBotLeft().x() > f)
            f = plane->getBotLeft().x();
        if(plane->getTopLeft().x() > f)
            f = plane->getTopLeft().x();
        if(plane->getTopRight().x() > f )
            f = plane->getTopRight().x();
    }
    result.setX(f);
    f=0;
    foreach (plane, m_planes) {
        if(plane->getBotLeft().x() < f)
            f = plane->getBotLeft().x();
        if(plane->getTopLeft().x() < f)
            f = plane->getTopLeft().x();
        if(plane->getTopRight().x() < f )
            f = plane->getTopRight().x();
    }
    result.setY(f);
    m_x_max_min = result;
}
//!
//! \brief Brush::setYMinMax
//!
void Brush::setYMinMax() {
    QPointF result;
    qreal f=0;
    Plane *plane;
    foreach (plane, m_planes) {
        if(plane->getBotLeft().y() > f)
            f = plane->getBotLeft().y();
        if(plane->getTopLeft().y() > f)
            f = plane->getTopLeft().y();
        if(plane->getTopRight().y() > f )
            f = plane->getTopRight().y();
    }
    result.setX(f);
    f=0;
    foreach (plane, m_planes) {
        if(plane->getBotLeft().y() < f)
            f = plane->getBotLeft().y();
        if(plane->getTopLeft().y() < f)
            f = plane->getTopLeft().y();
        if(plane->getTopRight().y() < f )
            f = plane->getTopRight().y();
    }
    result.setY(f);
    m_y_max_min = result;
}
//!
//! \brief Brush::setZMinMax
//!
void Brush::setZMinMax() {
    QPointF result;
    qreal f=0;
    Plane *plane;
    foreach (plane, m_planes) {
        if(plane->getBotLeft().z() > f)
            f = plane->getBotLeft().z();
        if(plane->getTopLeft().z() > f)
            f = plane->getTopLeft().z();
        if(plane->getTopRight().z() > f )
            f = plane->getTopRight().z();
    }
    result.setX(f);
    f=0;
    foreach (plane, m_planes) {
        if(plane->getBotLeft().z() < f)
            f = plane->getBotLeft().z();
        if(plane->getTopLeft().z() < f)
            f = plane->getTopLeft().z();
        if(plane->getTopRight().z() < f )
            f = plane->getTopRight().z();
    }
    result.setY(f);
    m_z_max_min = result;
}
//!
//! \brief Brush::getBoundingBox
//! \return
//!
bool Brush::getBoundingBox() {
    setXMinMax();
    setYMinMax();
    setZMinMax();
    return 0;
}
//!
//! \brief Brush::getTopLeft
//! \param primary
//! \param secondary
//! \return
//!
QVector2D Brush::getTopLeft(axis primary, axis secondary) {
    QVector2D vec;
    if(primary == secondary) {
        qWarning("primary=secondary");
        return vec;
    }
    if(!getBoundingBox()) {
        switch (primary) {
        case X_AXIS:
            vec.setX(m_x_max_min.y());
            break;
        case Y_AXIS:
            vec.setX(m_y_max_min.y());
            break;
        case Z_AXIS:
            vec.setX(m_z_max_min.y());
            break;
        default:
            break;
        }
        switch (secondary) {
        case X_AXIS:
            vec.setY(m_x_max_min.x());
            break;
        case Y_AXIS:
            vec.setY(m_y_max_min.x());
            break;
        case Z_AXIS:
            vec.setY(m_z_max_min.x());
            break;
        default:
            break;
        }
    }
    return vec;
}
//!
//! \brief Brush::getTopRight
//! \param primary
//! \param secondary
//! \return
//!
QVector2D Brush::getTopRight(axis primary, axis secondary) {
    QVector2D vec;
    if(primary == secondary) {
        qWarning("primary=secondary");
        return vec;
    }
    if(!getBoundingBox()) {
        switch (primary) {
        case X_AXIS:
            vec.setX(m_x_max_min.x());
            break;
        case Y_AXIS:
            vec.setX(m_y_max_min.x());
            break;
        case Z_AXIS:
            vec.setX(m_z_max_min.x());
            break;
        default:
            break;
        }
        switch (secondary) {
        case X_AXIS:
            vec.setY(m_x_max_min.x());
            break;
        case Y_AXIS:
            vec.setY(m_y_max_min.x());
            break;
        case Z_AXIS:
            vec.setY(m_z_max_min.x());
            break;
        default:
            break;
        }
    }
    return vec;
}
//!
//! \brief Brush::getBottomLeft
//! \param primary
//! \param secondary
//! \return
//!
QVector2D Brush::getBottomLeft(axis primary, axis secondary) {
    QVector2D vec;
    if(primary == secondary) {
        qWarning("primary=secondary");
        return vec;
    }
    if(!getBoundingBox()) {
        switch (primary) {
        case X_AXIS:
            vec.setX(m_x_max_min.y());
            break;
        case Y_AXIS:
            vec.setX(m_y_max_min.y());
            break;
        case Z_AXIS:
            vec.setX(m_z_max_min.y());
            break;
        default:
            break;
        }
        switch (secondary) {
        case X_AXIS:
            vec.setY(m_x_max_min.y());
            break;
        case Y_AXIS:
            vec.setY(m_y_max_min.y());
            break;
        case Z_AXIS:
            vec.setY(m_z_max_min.y());
            break;
        default:
            break;
        }
    }
    return vec;
}
//!
//! \brief Brush::getBottomRight
//! \param primary
//! \param secondary
//! \return
//!
QVector2D Brush::getBottomRight(axis primary, axis secondary) {
    QVector2D vec;
    if(primary == secondary) {
        qWarning("primary=secondary");
        return vec;
    }
    if(!getBoundingBox()) {
        switch (primary) {
        case X_AXIS:
            vec.setX(m_x_max_min.x());
            break;
        case Y_AXIS:
            vec.setX(m_y_max_min.x());
            break;
        case Z_AXIS:
            vec.setX(m_z_max_min.x());
            break;
        default:
            break;
        }
        switch (secondary) {
        case X_AXIS:
            vec.setY(m_x_max_min.y());
            break;
        case Y_AXIS:
            vec.setY(m_y_max_min.y());
            break;
        case Z_AXIS:
            vec.setY(m_z_max_min.y());
            break;
        default:
            break;
        }
    }
    return vec;
}

