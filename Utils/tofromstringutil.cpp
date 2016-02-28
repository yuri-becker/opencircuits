/*
 *  tofromstringutil.cpp: Implementation of tofromstringutil.h
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

#include "tofromstringutil.h"

QString ToFromStringUtil::pointToString(QPoint point)
{
    QString retVal = "";
    retVal = retVal.append(QString::number(point.x()));
    retVal = retVal.append(",");
    retVal = retVal.append(QString::number(point.y()));
    return retVal;
}

QPoint ToFromStringUtil::pointFromString(QString point)
{
    int x = point.split(",", QString::SkipEmptyParts, Qt::CaseSensitive).at(0).toInt();
    int y = point.split(",", QString::SkipEmptyParts, Qt::CaseSensitive).at(1).toInt();
    return QPoint(x,y);
}

QString ToFromStringUtil::listOfStringsToString(QStringList list)
{
    QString retVal = "";
    Q_FOREACH(QString string, list)
    {
        retVal = retVal.append(string).append(",");
    }

    return retVal;
}

QStringList ToFromStringUtil::listOfStringsFromString(QString list)
{
    QStringList retVal = QStringList();
    retVal = list.split(",", QString::SkipEmptyParts, Qt::CaseSensitive);
    return retVal;
}





ToFromStringUtil::ToFromStringUtil()
{
}
