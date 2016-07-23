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

#include "brush.h"
#include "polygoniser.h"
#define PI 3.14159265
//!
//! \brief Plane::Plane Contruct a plane with 3 vertex
//! \param top_left - Defines the bottom left vertex - Defines the bottom left vertex
//! \param top_left - Defines the top left vertex
//! \param top_left - Defines the top right vertex - Defines the top right vertex
//!
Plane::Plane(QVector3D bot_left, QVector3D top_left, QVector3D top_right) {
  if(!checkValid(bot_left, top_left, top_right)) {
    m_bot_left = bot_left;
    m_top_left = top_left;
    m_top_right = top_right;
  }
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
//! \brief Plane::setBotLeft
//! \param top_left - Defines the bottom left vertex
//!
void Plane::setBotLeft(QVector3D bot_left) {
  m_bot_left = bot_left;
}
//!
//! \brief Plane::setTopRight
//! \param top_left - Defines the top right vertex
//!
void Plane::setTopRight(QVector3D top_right) {
  m_top_right = top_right;
}
//!
//! \brief Plane::setTopLeft
//! \param top_left - Defines the top left vertex
//!
void Plane::setTopLeft(QVector3D top_left) {
  m_top_left = top_left;
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
//! \param top_left - Defines the bottom left vertex
//! \param top_left - Defines the top left vertex
//! \param top_left - Defines the top right vertex
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
//! \brief Brush::Brush default (invalid) constructor
//!
Brush::Brush() {

}
//!
//! \brief Brush::Brush
//! \param planes
//!
Brush::Brush(QList<Plane *> planes) {
  //if(!checkValid(planes))
    m_planes = planes;
}
//!
//! \brief checkValid
//! The whole system relies on the fact that you cant have more than one face
//! on the same plane, this iterates the entire list of planes to check this.
//! \param planes
//! \return 1 for error
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
//! \return Number of planes in the brush
//!
int Brush::getNumOfSides() {
  return m_planes.size();
}
//!
//! \brief Brush::setXMinMax
//!
void Brush::setXMinMax() {
  QPointF result;
  qreal f=DBL_MIN;
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
  f=DBL_MAX;
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
  qreal f=DBL_MIN;
  Plane *plane;
  //! Maximum
  foreach (plane, m_planes) {
    if(plane->getBotLeft().y() > f)
      f = plane->getBotLeft().y();
    if(plane->getTopLeft().y() > f)
      f = plane->getTopLeft().y();
    if(plane->getTopRight().y() > f )
      f = plane->getTopRight().y();
  }
  result.setX(f);
  f=DBL_MAX;
  //! Minimum
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
  qreal f=DBL_MIN;
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
  f=DBL_MAX;
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
//! \param primary - The arbitrary horizontal axis in a 2D view
//! \param secondary - The arbitrary vertical axis in a 2D view
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
    case axis::X_AXIS:
      vec.setX(m_x_max_min.y());
      break;
    case axis::Y_AXIS:
      vec.setX(m_y_max_min.y());
      break;
    case axis::Z_AXIS:
      vec.setX(m_z_max_min.y());
      break;
    default:
      break;
    }
    switch (secondary) {
    case axis::X_AXIS:
      vec.setY(m_x_max_min.x());
      break;
    case axis::Y_AXIS:
      vec.setY(m_y_max_min.x());
      break;
    case axis::Z_AXIS:
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
//! \param primary - The arbitrary horizontal axis in a 2D view
//! \param secondary - The arbitrary vertical axis in a 2D view
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
    case axis::X_AXIS:
      vec.setX(m_x_max_min.x());
      break;
    case axis::Y_AXIS:
      vec.setX(m_y_max_min.x());
      break;
    case axis::Z_AXIS:
      vec.setX(m_z_max_min.x());
      break;
    default:
      break;
    }
    switch (secondary) {
    case axis::X_AXIS:
      vec.setY(m_x_max_min.x());
      break;
    case axis::Y_AXIS:
      vec.setY(m_y_max_min.x());
      break;
    case axis::Z_AXIS:
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
//! \param primary - The arbitrary horizontal axis in a 2D view
//! \param secondary - The arbitrary vertical axis in a 2D view
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
    case axis::X_AXIS:
      vec.setX(m_x_max_min.y());
      break;
    case axis::Y_AXIS:
      vec.setX(m_y_max_min.y());
      break;
    case axis::Z_AXIS:
      vec.setX(m_z_max_min.y());
      break;
    default:
      break;
    }
    switch (secondary) {
    case axis::X_AXIS:
      vec.setY(m_x_max_min.y());
      break;
    case axis::Y_AXIS:
      vec.setY(m_y_max_min.y());
      break;
    case axis::Z_AXIS:
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
//! \param primary - The arbitrary horizontal axis in a 2D view
//! \param secondary - The arbitrary vertical axis in a 2D view
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
    case axis::X_AXIS:
      vec.setX(m_x_max_min.x());
      break;
    case axis::Y_AXIS:
      vec.setX(m_y_max_min.x());
      break;
    case axis::Z_AXIS:
      vec.setX(m_z_max_min.x());
      break;
    default:
      break;
    }
    switch (secondary) {
    case axis::X_AXIS:
      vec.setY(m_x_max_min.y());
      break;
    case axis::Y_AXIS:
      vec.setY(m_y_max_min.y());
      break;
    case axis::Z_AXIS:
      vec.setY(m_z_max_min.y());
      break;
    default:
      break;
    }
  }
  return vec;
}
//!
//! \brief Brush::getBottom
//! \param primary - The arbitrary horizontal axis in a 2D view
//! \param secondary - The arbitrary vertical axis in a 2D view
//! \return
//!
QVector2D Brush::getBottom(axis primary, axis secondary) {
  QVector2D bottomRight = getBottomRight(primary,secondary);
  QVector2D bottomLeft = getBottomLeft(primary,secondary);
  return (bottomRight + bottomLeft) / 2;
}
//!
//! \brief Brush::getTop
//! \param primary - The arbitrary horizontal axis in a 2D view
//! \param secondary - The arbitrary vertical axis in a 2D view
//! \return
//!
QVector2D Brush::getTop(axis primary, axis secondary) {
  QVector2D topRight = getTopRight(primary,secondary);
  QVector2D topLeft = getTopLeft(primary,secondary);
  return (topRight + topLeft) / 2;
}
//!
//! \brief Brush::getLeft
//! \param primary - The arbitrary horizontal axis in a 2D view
//! \param secondary - The arbitrary vertical axis in a 2D view
//! \return
//!
QVector2D Brush::getLeft(axis primary, axis secondary) {
  QVector2D topLeft = getTopLeft(primary,secondary);
  QVector2D bottomLeft = getBottomLeft(primary,secondary);
  return (bottomLeft + topLeft) / 2;
}
//!
//! \brief Brush::getRight
//! \param primary - The arbitrary horizontal axis in a 2D view
//! \param secondary - The arbitrary vertical axis in a 2D view
//! \return
//!
QVector2D Brush::getRight(axis primary, axis secondary) {
  QVector2D topRight = getTopRight(primary,secondary);
  QVector2D bottomRight = getBottomRight(primary,secondary);
  return (bottomRight + topRight) / 2;
}
//!
//! \brief Brush::getCenter
//! \param primary - The arbitrary horizontal axis in a 2D view
//! \param secondary - The arbitrary vertical axis in a 2D view
//! \return
//!
QVector2D Brush::getCenter(axis primary, axis secondary) {
  return ((getBottom(primary,secondary) + getTop(primary,secondary)) / 2);
}
//!
//! \brief Brush::translate
//! \param primary - The arbitrary horizontal axis in a 2D view
//! \param secondary - The arbitrary vertical axis in a 2D view
//! \param transform
//!
void Brush::translate(axis primary, axis secondary, QVector2D transform) {
  QMatrix4x4 matrix;
  switch (primary) {
  case axis::X_AXIS:
    matrix.translate(transform.x(), 0, 0);
    break;
  case axis::Y_AXIS:
    matrix.translate(0, transform.x(), 0);
    break;
  case axis::Z_AXIS:
    matrix.translate(0, 0, transform.x());
    break;
  default:
    break;
  }
  switch (secondary) {
  case axis::X_AXIS:
    matrix.translate(transform.y(), 0, 0);
    break;
  case axis::Y_AXIS:
    matrix.translate(0, transform.y(), 0);
    break;
  case axis::Z_AXIS:
    matrix.translate(0, 0, transform.y());
    break;
  default:
    break;
  }
  Plane *pla;
  foreach(pla, m_planes) {
    pla->setBotLeft(matrix.map(pla->getBotLeft()));
    pla->setTopLeft(matrix.map(pla->getTopLeft()));
    pla->setTopRight(matrix.map(pla->getTopRight()));
  }
}
//!
//! \brief Brush::rotate
//! \param primary - The arbitrary horizontal axis in a 2D view
//! \param secondary - The arbitrary vertical axis in a 2D view
//! \param angle
//!
void Brush::rotate(axis primary, axis secondary, float angle) {

  angle = angle * PI/180;
  // Move the object to the center of the grid!
  QVector2D center = getCenter(primary, secondary);
  translate(primary,secondary,-center);
  Plane *pla;
  bool rotateX = true;
  bool rotateY = true;
  bool rotateZ = true;
  // Remember if your editing the X against Z axis, you do the
  // bounding box and start to rotate your going to be wanting
  // to rotate around the Z axis...
  if((primary == axis::X_AXIS) || (secondary == axis::X_AXIS))
    rotateX = false;
  if((primary == axis::Y_AXIS) || (secondary == axis::Y_AXIS))
    rotateY = false;
  if((primary == axis::Z_AXIS) || (secondary == axis::Z_AXIS))
    rotateZ = false;

  // for some reason i couldnt understand the matrix.rotate wouldnt work..?
  // Goto link for more info:
  // http://inside.mines.edu/fs_home/gmurray/ArbitraryAxisRotation/
  QMatrix4x4 matrix;
  if(rotateZ) {
    matrix.setRow(0, QVector4D(cos(angle), -sin(angle),0,0));
    matrix.setRow(1, QVector4D(sin(angle), cos(angle) ,0,0));
    matrix.setRow(2, QVector4D(0,0          ,1,0));
    matrix.setRow(3, QVector4D(0,0          ,0,1));
  }
  if(rotateY) {
    matrix.setRow(0, QVector4D(cos(angle),0,sin(angle),0));
    matrix.setRow(1, QVector4D(0, 1,0,0));
    matrix.setRow(2, QVector4D(-sin(angle),0,cos(angle),0));
    matrix.setRow(3, QVector4D(0,0,0,1));
  }
  if(rotateX) {
    matrix.setRow(0, QVector4D(1,0,0,0));
    matrix.setRow(1, QVector4D(0,cos(angle),-sin(angle),0));
    matrix.setRow(2, QVector4D(0,sin(angle),cos(angle),0));
    matrix.setRow(3, QVector4D(0,0,0,1));
  }
  foreach(pla, m_planes) {
    pla->setBotLeft(matrix.map(pla->getBotLeft()));
    pla->setTopLeft(matrix.map(pla->getTopLeft()));
    pla->setTopRight(matrix.map(pla->getTopRight()));
  }
  // Move the object back to where it came from!
  translate(primary,secondary,center);

}
//!
//! \brief Brush::scale
//! \param primary - The arbitrary horizontal axis in a 2D view
//! \param secondary - The arbitrary vertical axis in a 2D view
//! \param scaleFactor
//!
void Brush::scale(axis primary, axis secondary, QVector2D scaleFactor) {
  QMatrix4x4 matrix;
  switch (primary) {
  case axis::X_AXIS:
    matrix.scale(scaleFactor.x(),1,1);
    break;
  case axis::Y_AXIS:
    matrix.scale(1, scaleFactor.x(), 1);
    break;
  case axis::Z_AXIS:
    matrix.scale(1, 1, scaleFactor.x());
    break;
  default:
    break;
  }
  switch (secondary) {
  case axis::X_AXIS:
    matrix.scale(scaleFactor.y(), 1, 1);
    break;
  case axis::Y_AXIS:
    matrix.scale(1, scaleFactor.y(), 1);
    break;
  case axis::Z_AXIS:
    matrix.scale(1, 1, scaleFactor.y());
    break;
  default:
    break;
  }
  Plane *pla;
  foreach(pla, m_planes) {
    pla->setBotLeft(matrix.map(pla->getBotLeft()));
    pla->setTopLeft(matrix.map(pla->getTopLeft()));
    pla->setTopRight(matrix.map(pla->getTopRight()));
  }
}
//!
void Brush::transform(boundingBox box, axis primary, axis secondary, QVector2D transform) {

  QVector2D coords;
  switch (box) {
  case  BOUND_BOX__TOP_LEFT:
    coords = getBottomRight(primary, secondary);
    break;
  case  BOUND_BOX__TOP_RIGHT:
    coords = getBottomLeft(primary, secondary);
    break;
  case  BOUND_BOX__BOTTOM_RIGHT:
    coords = getTopLeft(primary, secondary);
    break;
  case  BOUND_BOX__BOTTOM_LEFT:
    coords = getTopRight(primary, secondary);
    break;
  case  BOUND_BOX__TOP:
    coords = getBottom(primary, secondary);
    break;
  case  BOUND_BOX__RIGHT:
    coords = getLeft(primary, secondary);
    break;
  case  BOUND_BOX__BOTTOM:
    coords = getTop(primary, secondary);
    break;
  case  BOUND_BOX__LEFT:
    coords = getRight(primary, secondary);
    break;
  default  :
    break;
  }
  translate(primary,secondary,-coords);
  QVector2D size;
  switch (box) {
  case  BOUND_BOX__TOP_LEFT:
    size = getTopLeft(primary,secondary);
    break;
  case  BOUND_BOX__TOP_RIGHT:
    size = getTopRight(primary,secondary);
    break;
  case  BOUND_BOX__BOTTOM_RIGHT:
    size = getBottomRight(primary,secondary);
    break;
  case  BOUND_BOX__BOTTOM_LEFT:
    size = getBottomLeft(primary,secondary);
    break;
  case  BOUND_BOX__TOP:
    size = getTop(primary,secondary);
    break;
  case  BOUND_BOX__RIGHT:
    size = getLeft(primary,secondary);
    break;
  case  BOUND_BOX__BOTTOM:
    size = getTop(primary,secondary);
    break;
  case  BOUND_BOX__LEFT:
    size = getRight(primary,secondary);
    break;
  default:
    break;
  }
  QVector2D newSize = size + transform;
  scale(primary,secondary,newSize/size);
  translate(primary,secondary,coords);
}

//!
//! \brief Brush::matchingVertexes
//! \param primary - The arbitrary horizontal axis in a 2D view
//! \param secondary - The arbitrary vertical axis in a 2D view
//! \param checkpos
//!
void  Brush::matchingVertexes(axis primary, axis secondary, QVector2D checkpos) {

  m_xMatch.clear();
  m_yMatch.clear();
  m_zMatch.clear();

  Plane *pla;
  axis thisAxis = axis::X_AXIS;
  for(int i=0; i<2; i++) {
    qreal check;
    if (0==i)
      thisAxis = primary;
    if (1==i)
      thisAxis = secondary;
    switch (thisAxis) {
    case axis::X_AXIS:
      if(1==i) {
        check = checkpos.y();
      }
      else {
        check = checkpos.x();
      }
      foreach(pla,m_planes) {
        QList<QVector3D*> list = pla->getVertexes();
        if(pla->getTopLeft().x()==check)
          m_xMatch.append(list.at(0));
        if(pla->getBotLeft().x()==check)
          m_xMatch.append(list.at(1));
        if(pla->getTopRight().x()==check)
          m_xMatch.append(list.at(2));
      }
      break;
    case axis::Y_AXIS:
      if(1==i) {
        check = checkpos.y();
      }
      else {
        check = checkpos.x();
      }
      foreach(pla,m_planes) {
        QList<QVector3D*> list = pla->getVertexes();
        if(pla->getTopLeft().y()==check)
          m_yMatch.append(list.at(0));
        if(pla->getBotLeft().y()==check)
          m_yMatch.append(list.at(1));
        if(pla->getTopRight().y()==check)
          m_yMatch.append(list.at(2));
      }
      break;
    case axis::Z_AXIS:
      if(1==i) {
        check = checkpos.y();
      }
      else {
        check = checkpos.x();
      }
      foreach(pla,m_planes) {
        QList<QVector3D*> list = pla->getVertexes();
        if(pla->getTopLeft().z()==check)
          m_zMatch.append(list.at(0));
        if(pla->getBotLeft().z()==check)
          m_zMatch.append(list.at(1));
        if(pla->getTopRight().z()==check)
          m_zMatch.append(list.at(2));
      }
      break;
    default:
      break;
    }
  }
}
//!
//! \brief Brush::translateMyVertexes
//! \param primary - The arbitrary horizontal axis in a 2D view
//! \param secondary - The arbitrary vertical axis in a 2D view
//! \param transform
//!
void  Brush::translateMyVertexes(axis primary, axis secondary, QVector2D transform) {
  QMatrix4x4 matrix;
  switch (primary) {
  case axis::X_AXIS:
    matrix.translate(transform.x(), 0, 0);
    break;
  case axis::Y_AXIS:
    matrix.translate(0, transform.x(), 0);
    break;
  case axis::Z_AXIS:
    matrix.translate(0, 0, transform.x());
    break;
  default:
    break;
  }
  switch (secondary) {
  case axis::X_AXIS:
    matrix.translate(transform.y(), 0, 0);
    break;
  case axis::Y_AXIS:
    matrix.translate(0, transform.y(), 0);
    break;
  case axis::Z_AXIS:
    matrix.translate(0, 0, transform.y());
    break;
  default:
    break;
  }
  QVector3D *vec;
  foreach(vec, m_xMatch) {
    vec->setX(matrix.map(QVector3D(vec->x(),0,0)).x());
  }
  foreach(vec, m_yMatch) {
    vec->setY(matrix.map(QVector3D(0,vec->y(),0)).y());
  }
  foreach(vec, m_zMatch) {
    vec->setZ(matrix.map(QVector3D(0,0,vec->z())).z());
  }
}
//!
//! \brief Brush::getPlanes
//! \return
//!
QList<Plane*> Brush::getPlanes() {
  return m_planes;
}

QList<QPolygonF> Brush::polygonise(axis primary, axis secondary) {
    return Polygoniser::poligonise(this, primary, secondary);
}
