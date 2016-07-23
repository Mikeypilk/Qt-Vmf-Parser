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

#ifndef MAP_H
#define MAP_H
#include <QAbstractItemModel>
#include <QObject>
#include "brush.h"
//!
//! \brief The Map class is a model that holds all the brushes
//!
//! I want it to be like this so that if I come to make this app multi user
//! then i can properly manage changes in a stateful way
//!
//! Also its gonna make it super easy to have a nice tree/table ui widget to allow the
//! user to easily edit/view all the brush data.
//!
class Map : public QAbstractItemModel
{
    Q_OBJECT
    QList<Brush>  m_brushes;

public:
    enum MapRoles {
        BrushRole = Qt::UserRole + 1,
    };

    Map(QObject *parent = 0);
    QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex & index) const;
    int columnCount(const QModelIndex & parent = QModelIndex()) const;
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    void addBrush(const Brush &newBrush);


};

#endif // MAP_H
