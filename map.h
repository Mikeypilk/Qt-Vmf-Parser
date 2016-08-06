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
#include <QObject>
#include "brush.h"
#include "solids.h"

class Map : public QObject {

    Q_OBJECT

    //! versioninfo{}
    struct {
        int editorVersion;  //! The version of Hammer used to create the file.
        int editorBuild;    //! The patch number of Hammer the file was generated with.
        int mapVersion;     //! represents how many times you've saved the file.
        int formatVersion;  //! (Most likely the VMF file format version)
        int prefab;         //! a full map or simply a collection of prefabs.
    } m_versionInfo;

    //! visgroups{}

    //! viewsettings{}
    struct {
        bool bSnapToGrid;   //! Whether the map has the grid snapping feature enabled.
        bool bShowGrid;     //! Whether the map is showing the 2D grid.
        bool ShowLogicalGrid; //! Changes whether the hidden "Logical View" should show a grid
        int nGridSpacing;   //! The value the grid lines are spaced at.
        bool bShow3DGrid;   //! Whether the map is showing the 3D grid.
    } m_viewSettings;

    //! world{}
    Solids m_solids; //! This is a model that holds the blocks

    //!    entity{}
    //!    hidden{}

    //!    cameras{}
    int m_activecamera;     //! Sets the currently active camera used for the Hammer 3D View.
    //! When no cameras are present in the .VMF, this value is set to -1
    //! and the camera position defaults to the world origin, facing North.
    struct s_cameras {
        QVector3D position; //! The eye position of the camera in the map.
        QVector3D look; //! The position of the camera target -- the point the camera is looking toward.
    };

    //!    cordon{}

    void parseGenericStruct(QTextStream *txt, QStringList *genericStruct);
    void parseWorld(QTextStream *txt);
    bool populateVersionInfo(QStringList *genericList);
    bool populateViewSettings(QStringList *genericList);

public:
    bool readVMF(const QString &filename);
};

#endif // MAP_H
