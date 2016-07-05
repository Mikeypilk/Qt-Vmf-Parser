#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QRectF>
#include <QtCore>
#include <QColor>
#include <QWheelEvent>
#include <QGraphicsItemGroup>
#include <QVector3D>

class ViewPortScene : public QGraphicsScene
{
    Q_OBJECT
    int roundGrid(int input, int units);

public:
    ViewPortScene();
    void drawBackground(QPainter *painter, const QRectF &rect);
    int m_default_size;
    qreal m_scale;
    int m_grid;

private:
    void drawGrid(int units, QPen pen, QPainter *painter, const QRectF &rect);


public slots:
    void setScale(qreal scale);
    void setGrid(bool step);
};



#endif // VIEWPORT_H
