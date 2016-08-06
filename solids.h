#ifndef SOLIDS_H
#define SOLIDS_H

#include <QObject>
#include <QAbstractListModel>
#include "brush.h"

//!
//! \brief The Solids List Model contains all the data defined by the world
//!
class Solids : public QAbstractListModel
{
    Q_OBJECT
    QList<Brush> m_brushes; //! The Brushes defining the 3D blocks in the game world

public:
    enum SolidsRoles {
        BrushRole = Qt::UserRole + 1,
    };

    Solids(QObject *parent = 0);
    QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    void addSolid(const Brush &newBrush);

};

#endif // SOLIDS_H
