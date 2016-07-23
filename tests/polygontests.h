#ifndef POLYGONTESTS_H
#define POLYGONTESTS_H

#include <QObject>
#include <QTest>
#include "polygoniser.h"

class PolygonTests : public QObject
{
    Q_OBJECT
    QPolygonF expected;
    QPolygonF actual;

private slots:
    void cleanup();

    // Example 2D shapes
    void testSquare();
    void testPentagon();
    void testHexagon();
    void testOctagon();

    //Brushes
    void testCuboid();
    void testOctagonalPrism();

};

#endif // POLYGONTESTS_H
