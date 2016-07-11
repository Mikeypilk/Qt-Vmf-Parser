#ifndef CONTROLLERTESTS_H
#define CONTROLLERTESTS_H

#include <QObject>
#include <QTest>

class ControllerTests : public QObject
{
    Q_OBJECT
public:
  void init();
  void cleanup();
  void testTranslate();
};

#endif // CONTROLLERTESTS_H
