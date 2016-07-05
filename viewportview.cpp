
#include "viewportview.h"

ViewPortView::ViewPortView ( QWidget * parent )
    : QGraphicsView(parent) {
    m_scale = 8;
}

ViewPortView::ViewPortView (QGraphicsScene *scene, QWidget * parent)
    : QGraphicsView(scene,parent) {
}

void ViewPortView::scrollContentsBy(int dx, int dy) {
    QGraphicsView::scrollContentsBy(dx,dy);
    emit(sceneMoved());
}

void ViewPortView::wheelEvent(QWheelEvent * event)
{
    //your functionality, for example:
    //if ctrl pressed, use original functionality
    if(event->modifiers() & Qt::ControlModifier)
    {
        QGraphicsView::wheelEvent(event);
    }
    //otherwise, do yours
    else
    {
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
    releaseScale();

}

void ViewPortView::releaseScale() {
    emit(scaleChanged(m_scale));
}

