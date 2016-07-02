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
//! \brief getVertexes returns pointers to vertexes for editing
//! Remember to validate the vertexes when using this!
//! \return
//!
QList<QVector3D*> Plane::getVertexes() {
    QList<QVector3D*> list;
    list.append(&m_bot_left);
    list.append(&m_top_left);
    list.append(&m_top_right);
    return list;
};
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
//!
//! \brief Brush::getBottom i.e. the center between bottom left and right
//! \param primary
//! \param secondary
//! \return
//!
QVector2D Brush::getBottom(axis primary, axis secondary) {
    QVector2D bottomRight = getBottomRight(primary,secondary);
    QVector2D bottomLeft = getBottomLeft(primary,secondary);
    return (bottomRight + bottomLeft) / 2;
}
//!
//! \brief Brush::getTop
//! \param primary
//! \param secondary
//! \return
//!
QVector2D Brush::getTop(axis primary, axis secondary) {
    QVector2D topRight = getTopRight(primary,secondary);
    QVector2D topLeft = getTopLeft(primary,secondary);
    return (topRight + topLeft) / 2;
}
//!
//! \brief Brush::getLeft
//! \param primary
//! \param secondary
//! \return
//!
QVector2D Brush::getLeft(axis primary, axis secondary) {
    QVector2D topLeft = getTopLeft(primary,secondary);
    QVector2D bottomLeft = getBottomLeft(primary,secondary);
    return (bottomLeft + topLeft) / 2;
}
//!
//! \brief Brush::getRight
//! \param primary
//! \param secondary
//! \return
//!
QVector2D Brush::getRight(axis primary, axis secondary) {
    QVector2D topRight = getTopRight(primary,secondary);
    QVector2D bottomRight = getBottomRight(primary,secondary);
    return (bottomRight + topRight) / 2;
}
//!
//! \brief Brush::transform
//! \param corner
//! \param primary
//! \param secondary
//! \param newpos
//!
void Brush::transform(boundingBox box, axis primary, axis secondary, QPointF newpos) {
    QVector2D coords;
    switch (box) {
    case  BOUND_BOX__TOP_LEFT:
        coords = getTopLeft(primary, secondary);
        break;
    case  BOUND_BOX__TOP_RIGHT:
        coords = getTopRight(primary, secondary);
        break;
    case  BOUND_BOX__BOTTOM_RIGHT:
        coords = getBottomRight(primary, secondary);
        break;
    case  BOUND_BOX__BOTTOM_LEFT:
        coords = getBottomLeft(primary, secondary);
        break;
    case  BOUND_BOX__TOP:
        coords = getTop(primary, secondary);
        break;
    case  BOUND_BOX__RIGHT:
        coords = getRight(primary, secondary);
        break;
    case  BOUND_BOX__BOTTOM:
        coords = getBottom(primary, secondary);
        break;
    case  BOUND_BOX__LEFT:
        coords = getLeft(primary, secondary);
        break;
    default  :
        break;
    }
    matchingVertexes(primary,secondary,coords);
    QVector3D *vec;
    switch (primary) {
    case X_AXIS:
        foreach(vec, xMatch) {
            vec->setX(newpos.x());
        }
        break;
    case Y_AXIS:
        foreach(vec, yMatch) {
            vec->setY(newpos.x());
        }
        break;
    case Z_AXIS:
        foreach(vec, zMatch) {
            vec->setZ(newpos.x());
        }
        break;
    default:
        break;
    }
    switch (secondary) {
    case X_AXIS:
        foreach(vec, xMatch) {
            vec->setX(newpos.y());
        }
        break;
    case Y_AXIS:
        foreach(vec, yMatch) {
            vec->setY(newpos.y());
        }
        break;
    case Z_AXIS:
        foreach(vec, zMatch) {
            vec->setZ(newpos.y());
        }
        break;
    default:
        break;
    }
}
//!
//! \brief Brush::matchingVertexes
//! \param primary
//! \param secondary
//! \param checkpos
//!
void  Brush::matchingVertexes(axis primary, axis secondary, QVector2D checkpos) {
    Plane *pla;
    axis thisAxis = X_AXIS;
    xMatch.clear();
    yMatch.clear();
    zMatch.clear();
    for(int i=0; i<2; i++) {
        qreal val;
        if (0==i)
            thisAxis = primary;
        if (1==i)
            thisAxis = secondary;
        switch (thisAxis) {
        case X_AXIS:
            if(1==i)
                val = checkpos.y();
            else
                val = checkpos.x();
            foreach(pla,m_planes) {
                QList<QVector3D*> list = pla->getVertexes();
                if(pla->getTopLeft().x()==val)
                    xMatch.append(list.at(0));
                if(pla->getBotLeft().x()==val)
                    xMatch.append(list.at(1));
                if(pla->getTopRight().x()==val)
                    xMatch.append(list.at(2));
            }
            break;
        case Y_AXIS:
            if(1==i)
                val = checkpos.y();
            else
                val = checkpos.x();
            foreach(pla,m_planes) {
                QList<QVector3D*> list = pla->getVertexes();
                if(pla->getTopLeft().y()==val)
                    yMatch.append(list.at(0));
                if(pla->getBotLeft().y()==val)
                    yMatch.append(list.at(1));
                if(pla->getTopRight().y()==val)
                    yMatch.append(list.at(2));
            }
            break;
        case Z_AXIS:
            if(1==i)
                val = checkpos.y();
            else
                val = checkpos.x();
            foreach(pla,m_planes) {
                QList<QVector3D*> list = pla->getVertexes();
                if(pla->getTopLeft().z()==val)
                    zMatch.append(list.at(0));
                if(pla->getBotLeft().z()==val)
                    zMatch.append(list.at(1));
                if(pla->getTopRight().z()==val)
                    zMatch.append(list.at(2));
            }
            break;
        default:
            break;
        }
    }
}

