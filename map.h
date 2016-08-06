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
//! \brief The Map class is the model that holds all the data for a map
//!
class Map : public QAbstractItemModel
{
    Q_OBJECT
    QList<Brush> m_brushes; //! The Brushes defining the 3D blocks in the game world

    struct {
        int editorVersion;  //! The version of Hammer used to create the file.
        int editorBuild;    //! The patch number of Hammer the file was generated with.
        int mapVersion;     //! represents how many times you've saved the file.
        int formatVersion;  //! (Most likely the VMF file format version)
        int prefab;         //! a full map or simply a collection of prefabs.
    } m_versionInfo;

    struct {
        bool bSnapToGrid;   //! Whether the map has the grid snapping feature enabled.
        bool bShowGrid;     //! Whether the map is showing the 2D grid.
        bool ShowLogicalGrid; //! Changes whether the hidden "Logical View" should show a grid
        int nGridSpacing;   //! The value the grid lines are spaced at.
        bool bShow3DGrid;   //! Whether the map is showing the 3D grid.
    } m_editorSettings;

    void parseGenericStruct(QTextStream *txt, QStringList *genericStruct);
    bool populateVersionInfo(QStringList *genericList);
    bool populateEditorSetting(QStringList *genericList);

public:
    enum MapRoles {
        BrushRole = Qt::UserRole + 1,
    };
    QModelIndex *SOLIDS;

    Map(QObject *parent = 0);
    QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    void addBrush(const Brush &newBrush);
    bool readVMF(const QString &filename);


};

#endif // MAP_H
