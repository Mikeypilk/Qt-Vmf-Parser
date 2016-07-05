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
#ifndef VIEWPORTVIEW_H
#define VIEWPORTVIEW_H

#include <QGraphicsView>
#include <QObject>
#include <QWheelEvent>

//!
//! \brief The ViewPortView class
//! I've overwrited this class so that I can steal the mouse
//! wheel events from the scroll bars and send them to my scene
//! to use for zooming in and out
//!
class ViewPortView : public QGraphicsView
{
Q_OBJECT
private:
public:
    ViewPortView ( QWidget * parent = 0 );
    void releaseScale();
    qreal m_scale;
signals:
    void scaleChanged(qreal scale);
protected:
    virtual void wheelEvent ( QWheelEvent * event );
};

#endif // VIEWPORTVIEW_H
