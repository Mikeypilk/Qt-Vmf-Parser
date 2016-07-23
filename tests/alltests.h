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

#ifndef ALLTESTS_H
#define ALLTESTS_H

#include <QObject>
#include "tests/brushtests.h"
#include "tests/maptests.h"

class allTests : public QObject
{
    Q_OBJECT
public:
    explicit allTests(QObject *parent = 0);
    bool runTests();
};

#endif // ALLTESTS_H
