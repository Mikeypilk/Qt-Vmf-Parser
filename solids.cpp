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

#include "solids.h"

//!
//! \brief Solids::Solids
//! \param parent
//!
Solids::Solids(QObject *parent)
    : QAbstractListModel(parent)
{
}
//!
//! \brief Solids::index
//! \param row
//! \param column
//! \param parent
//!
QModelIndex Solids::index(int row, int column, const QModelIndex &parent) const {
    return createIndex(row, column, parent.internalPointer());
}
//!
//! \brief Solids::parent
//! \param index
//!
QModelIndex Solids::parent(const QModelIndex &index) const {
    return index.parent();
}
//!
//! \brief Solids::columnCount
//! \param parent
//! \return
//!
int Solids::columnCount(const QModelIndex &parent) const {
    return 1;
}
//!
//! \brief Solids::rowCount
//! \param parent
//! \return
//!
int Solids::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_brushes.count();
}
//!
//! \brief Solids::data
//! \param index
//! \param role
//! \return
//!
QVariant Solids::data(const QModelIndex & index, int role) const {
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
//! \brief Solids::addBrush
//! \param newBrush
//!
void Solids::addSolid(const Brush &newBrush) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_brushes << newBrush;
    endInsertRows();
}
