#include "alltests.h"



allTests::allTests(QObject *parent) : QObject(parent)
{

}

bool allTests::runTests() {
    //! Run Plane tests
    PlaneTests planeTest;
    QTest::qExec(&planeTest);

    //! Run Brush tests
    BrushTests brushTest;
    QTest::qExec(&brushTest);
    return 0;
}
