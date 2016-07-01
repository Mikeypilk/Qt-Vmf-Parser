#ifndef ALLTESTS_H
#define ALLTESTS_H

#include <QObject>
#include "tests/brushtests.h"


class allTests : public QObject
{
    Q_OBJECT
public:
    explicit allTests(QObject *parent = 0);
    bool runTests();
};

#endif // ALLTESTS_H
