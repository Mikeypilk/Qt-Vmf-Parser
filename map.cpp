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

#include "map.h"

//!
//! \brief Map::Map
//! \param parent
//!
Map::Map(QObject *parent)
    : QAbstractItemModel(parent)
{
}
//!
//! \brief Map::index
//! \param row
//! \param column
//! \param parent
//!
QModelIndex Map::index(int row, int column, const QModelIndex &parent) const {
    return createIndex(row, column, parent.internalPointer());
}
//!
//! \brief Map::parent
//! \param index
//!
QModelIndex Map::parent(const QModelIndex &index) const {
    return index.parent();
}
//!
//! \brief Map::columnCount
//! \param parent
//! \return
//!
int Map::columnCount(const QModelIndex &parent) const {
    return 1;
}
//!
//! \brief Map::rowCount
//! \param parent
//! \return
//!
int Map::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_brushes.count();
}
//!
//! \brief Map::data
//! \param index
//! \param role
//! \return
//!
QVariant Map::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_brushes.count())
        return QVariant();

    const Brush &brush = m_brushes[index.row()];

    if (role == BrushRole) {
        QVariant v;
        v.setValue(brush);
        return v;
    }
}
//!
//! \brief Map::addBrush
//! \param newBrush
//!
void Map::addBrush(const Brush &newBrush) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_brushes << newBrush;
    endInsertRows();
}
