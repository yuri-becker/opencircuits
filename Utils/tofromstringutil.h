/*
 *  tofromstringutil.h: Collection of methods for converting strings into and from other stuff.
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

#ifndef TOFROMSTRINGUTIL_H
#define TOFROMSTRINGUTIL_H

#include <QPoint>
#include <QStringList>
#include <QString>

class ToFromStringUtil
{
    public:
        static QString pointToString(QPoint point);
        static QPoint pointFromString(QString point);

        static QString listOfStringsToString(QStringList list);
        static QStringList listOfStringsFromString(QString list);

    private:
        ToFromStringUtil();
};

#endif // TOFROMSTRINGUTIL_H
