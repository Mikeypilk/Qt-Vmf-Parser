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
//! \brief Map::parseGenericStruct converts generic vmf text stucture into a QStringList
//!  The structure looks like this
//!  @verbatim
//!  title
//!  {
//!     "variable" "value"
//!     "variable" "value"
//!  }
//! \param txt
//! \param versionInfo
//!
void Map::parseGenericStruct(QTextStream *txt, QStringList *genericStruct)
{
    QString line;
    bool open = false;
    while (txt->readLineInto(&line)) {
        if(line.contains("{")) {
            open = true;
            continue;
        }
        if(line.contains("}")) {
            open = false;
        }
        if(open) {
            genericStruct->append(line.remove("\t").remove(" ")
                                  .split(QRegularExpression("\""),
                                         QString::SkipEmptyParts));
        }
        else {
            return;
        }
    }
}

bool Map::parseWorld(QTextStream *txt) {
    QStringList worldSettings;
    QString line;
    QList<Plane*> planes;
    bool open = false;

MASTER:

    while (txt->readLineInto(&line)) {
        if(line.remove("\t") == "solid") {
            planes.clear();
            goto SOLID;
        }
        if(line.contains("{")) {
            open = true;
            continue;
        }
        if(line.contains("}")) {
            open = false;
        }
        if(open) {
            worldSettings.append(line.remove("\t").remove(" ")
                                 .split(QRegularExpression("\""),
                                        QString::SkipEmptyParts));
        }
        else {
            return 0;
        }
    }
SOLID:
    while (txt->readLineInto(&line)) {
        if(line.remove("\t") == "side") {
            goto SIDE;
        }
        if(line.contains("{")) {
            open = true;
            continue;
        }
        if(line.contains("}")) {
            open = false;
        }
        if(open) {
//            qDebug() << "id = " << line;
        }
        else {
            Brush b(planes);
            m_solids.addSolid(b);
            goto MASTER;
        }
    }
SIDE:
    while (txt->readLineInto(&line)) {
        if(line.contains("{")) {
            open = true;
            continue;
        }
        if(line.contains("}")) {
            open = false;
        }
        if(open) {
            QStringList list;
            list.append(line.remove("\t").split(QRegularExpression("\""),
                                                QString::SkipEmptyParts));
            list.removeAll(" ");
            if(list.at(0) == "plane") {
                QString splane = list.at(1);
                QStringList vertexes;
                vertexes.append(splane.remove("(").remove(")").split(" "));
                if(vertexes.size() == 9) {
                    bool ok;
                    Plane *p = new Plane(QVector3D(QString(vertexes.at(0)).toInt(&ok),
                                      QString(vertexes.at(1)).toInt(&ok),
                                      QString(vertexes.at(2)).toInt(&ok)),
                            QVector3D(QString(vertexes.at(3)).toInt(&ok),
                                      QString(vertexes.at(4)).toInt(&ok),
                                      QString(vertexes.at(5)).toInt(&ok)),
                            QVector3D(QString(vertexes.at(6)).toInt(&ok),
                                      QString(vertexes.at(7)).toInt(&ok),
                                      QString(vertexes.at(8)).toInt(&ok)));
                    planes.append(p);
                    if(!ok) {
                        qWarning("Invalid .vmf: Vertex in plane not int");
                        return 1;
                    }
                }
                else {
                    qWarning("Invalid .vmf: Incorrect number of points defining a plane");
                    return 1;
                }
            }

        }
        else {
            goto SOLID;
        }
    }
}

//!
//! \brief Map::readVMF
//! \param filename
//!
bool Map::readVMF(const QString &filename) {

    QFile file(filename);
    if (file.open(QFile::ReadOnly)) {
        QTextStream txt(&file);
        QString line;
        QStringList list;

MASTER:

        while (txt.readLineInto(&line)) {
            if(line == "versioninfo")
                goto VERSION;
            if(line == "visgroups")
                goto VISGROUPS;
            if(line == "viewsettings")
                goto VIEWSETTINGS;
            if(line == "world")
                goto WORLD;
            return 0;
        }

VERSION:
        parseGenericStruct(&txt, &list);
        if(!populateVersionInfo(&list)) {
            list.clear();
            goto MASTER;
        }
        else {
            qWarning("Invalid .vmf: Parsing VersionInfo Failed!");
            qDebug() << &list;
            return 1;
        }

VISGROUPS:
        parseGenericStruct(&txt, &list);
        list.clear();
        goto MASTER;

VIEWSETTINGS:
        parseGenericStruct(&txt, &list);
        if(!populateViewSettings(&list)) {
            list.clear();
            goto MASTER;
        }
        else {
            qWarning("Invalid .vmf: Parsing ViewSettings Failed!");
            qDebug() << &list;
            return 1;
        }

WORLD:
        parseWorld(&txt);

    }
}

bool Map::populateVersionInfo(QStringList *genericList) {

    bool ok;
    m_versionInfo.editorBuild = QString(genericList->at(genericList->indexOf(QRegularExpression("editorbuild")) + 1)).toInt(&ok);
    m_versionInfo.editorVersion = QString(genericList->at(genericList->indexOf(QRegularExpression("editorversion")) + 1)).toInt(&ok);
    m_versionInfo.mapVersion = QString(genericList->at(genericList->indexOf(QRegularExpression("mapversion")) + 1)).toInt(&ok);
    m_versionInfo.formatVersion = QString(genericList->at(genericList->indexOf(QRegularExpression("formatversion")) + 1)).toInt(&ok);
    m_versionInfo.prefab = QString(genericList->at(genericList->indexOf(QRegularExpression("prefab")) + 1)).toInt(&ok);
    if(ok)
        return 0;
    else
        return 1;
}

bool Map::populateViewSettings(QStringList *genericList) {
    bool ok;
    m_viewSettings.bSnapToGrid = QString(genericList->at(genericList->indexOf(QRegularExpression("bSnapToGrid")) + 1)).toInt(&ok);
    m_viewSettings.bShowGrid = QString(genericList->at(genericList->indexOf(QRegularExpression("bShowGrid")) + 1)).toInt(&ok);
    m_viewSettings.ShowLogicalGrid = QString(genericList->at(genericList->indexOf(QRegularExpression("ShowLogicalGrid")) + 1)).toInt(&ok);
    m_viewSettings.nGridSpacing = QString(genericList->at(genericList->indexOf(QRegularExpression("nGridSpacing")) + 1)).toInt(&ok);
    m_viewSettings.bShow3DGrid = QString(genericList->at(genericList->indexOf(QRegularExpression("bShow3DGrid")) + 1)).toInt(&ok);
    if(ok)
        return 0;
    else
        return 1;
}
