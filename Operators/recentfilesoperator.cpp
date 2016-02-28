/*
 *  recentfilesoperator.cpp: Implementation of recentfilesoperator.h
 *
 * Copyright (C) 2015 Yuri Becker <hi@yuri.li>
 *
 * This file is part of OpenCircuits.
 *
 * OpenCircuits is free software: you can redistribute it and/or modify it under the terms
 * of the GNU Lesser General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * OpenCircuits is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU  Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License along with
 * OpenCircuits. If not, see <http://www.gnu.org/licenses/>.
 * */

#include "recentfilesoperator.h"

#include <QStandardPaths>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QDir>

RecentFilesOperator::RecentFilesOperator()
{
    initFilePath();
    reloadOrCreate();
}

QStringList RecentFilesOperator::getRecentFiles()
{
    return recentFiles;
}

void RecentFilesOperator::clear()
{
    recentFiles = QStringList();
    emit recentFilesChanged();
    saveOrCreateNew();

}

bool RecentFilesOperator::addAndSave(QString recentFile)
{
    //If recentFile already exists, remove it
    if(recentFiles.contains(recentFile, Qt::CaseSensitive))
    {
        recentFiles.removeOne(recentFile);
    }

    //Prepend it
    recentFiles.prepend(recentFile);
    emit recentFilesChanged();
    return saveOrCreateNew();
}

bool RecentFilesOperator::saveOrCreateNew()
{
    QFileInfo fileInfo(filePath);
    QFile file(fileInfo.absoluteFilePath());
    if(file.open(QFile::WriteOnly))
    {
        QTextStream textStream(&file);
        Q_FOREACH(QString str, recentFiles)
        {
            textStream << str.append("\n");
        }
        file.close();
        return true;
    }
    else
    {
        return false;
    }
}

bool RecentFilesOperator::reloadOrCreate()
{
    QFileInfo fileInfo(filePath);
    QFile file(fileInfo.absoluteFilePath());
    //Create file if not existing
    if(!file.exists())
        saveOrCreateNew();

    if(file.open(QFile::ReadWrite| QFile::Text))
    {
        QTextStream textStream(&file);
        while(!textStream.atEnd())
        {
            recentFiles.append(textStream.readLine());
        }
        file.close();
        return true;
    }
    else
     {
        return false;
    }
}

void RecentFilesOperator::initFilePath()
{
    QString savesLocation = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    QDir dir(savesLocation);
    if(!dir.exists())
    {
        dir.mkdir(savesLocation);
    }
    filePath = savesLocation.append("/.recentFiles");
}
