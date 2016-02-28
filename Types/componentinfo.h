/*
 *  componentinfo.h: Object which can hold user-targeted information about a block.
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

#ifndef COMPONENTINFO_H
#define COMPONENTINFO_H

#include <QString>

class ComponentInfo
{
    public:
        ComponentInfo(int targetBlockType, QString blockName, QString wikiUrl);
        ComponentInfo();

        int targetBlockType;
        QString blockName;
        QString wikiUrl;
};

#endif // COMPONENTINFO_H
