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
#include "viewportview.h"
//!
//! \brief ViewPortView::ViewPortView
//! \param parent
//!
ViewPortView::ViewPortView ( QWidget * parent )
    : QGraphicsView(parent) {
    m_scale = 8;
}
//!
//! \brief ViewPortView::wheelEvent
//! \param event
//!
void ViewPortView::wheelEvent(QWheelEvent * event)
{
    if(event->modifiers() & Qt::ControlModifier)
    {
        QGraphicsView::wheelEvent(event);
    }
    else
    {
        // These are same constants that hammer uses
        if(event->delta() > 0)
        {
            if((m_scale!=2)) {
                scale(1.2,1.2);
                m_scale=m_scale*(1/1.2);
            }
        }
        else
        {
            scale(1/1.2,1/1.2);
            m_scale=m_scale*1.2;
        }
    }
    //! Can't figure out how to do this any other way...
    releaseScale();
}
//!
//! \brief ViewPortView::releaseScale
//!
void ViewPortView::releaseScale() {
    emit(scaleChanged(m_scale));
}

