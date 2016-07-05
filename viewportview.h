#ifndef VIEWPORTVIEW_H
#define VIEWPORTVIEW_H

#include <QGraphicsView>
#include <QObject>
#include <QWheelEvent>


class ViewPortView : public QGraphicsView
{
Q_OBJECT
private:
public:
    ViewPortView ( QWidget * parent = 0 );
    ViewPortView (QGraphicsScene *scene, QWidget * parent = 0 );
    void scrollContentsBy(int dx, int dy);
    void releaseScale();
    qreal m_scale;

signals:
    void scaleChanged(qreal scale);
    void sceneMoved();
protected:
    virtual void wheelEvent ( QWheelEvent * event );
};

#endif // VIEWPORTVIEW_H
