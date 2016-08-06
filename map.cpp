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
        qDebug() << line;
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
        if(!populateEditorSetting(&list)) {
            list.clear();
            goto MASTER;
        }
        else {
            qWarning("Invalid .vmf: Parsing ViewSettings Failed!");
            qDebug() << &list;
            return 1;
        }
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

bool Map::populateEditorSetting(QStringList *genericList) {
    bool ok;
    m_editorSettings.bSnapToGrid = QString(genericList->at(genericList->indexOf(QRegularExpression("bSnapToGrid")) + 1)).toInt(&ok);
    m_editorSettings.bShowGrid = QString(genericList->at(genericList->indexOf(QRegularExpression("bShowGrid")) + 1)).toInt(&ok);
    m_editorSettings.ShowLogicalGrid = QString(genericList->at(genericList->indexOf(QRegularExpression("ShowLogicalGrid")) + 1)).toInt(&ok);
    m_editorSettings.nGridSpacing = QString(genericList->at(genericList->indexOf(QRegularExpression("nGridSpacing")) + 1)).toInt(&ok);
    m_editorSettings.bShow3DGrid = QString(genericList->at(genericList->indexOf(QRegularExpression("bShow3DGrid")) + 1)).toInt(&ok);
    if(ok)
        return 0;
    else
        return 1;
}
