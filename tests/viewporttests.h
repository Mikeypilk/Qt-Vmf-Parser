#ifndef VIEWPORTTESTS_H
#define VIEWPORTTESTS_H

#include <QObject>
#include <QTest>

#include "map.h"
#include "viewportscene.h"

class ViewPortTests : public QObject
{
    Q_OBJECT
private slots:
    void testAddBlock();

};

#endif // VIEWPORTTESTS_H
