/*
 *  applicationproperties.h: Values primary used in the AboutDialog.
 *
 * Copyright (C) 2015-2016 Yuri Becker <hi@yuri.li>
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

#ifndef APPLICATIONPROPERTIES
#define APPLICATIONPROPERTIES

#include <QString>

class ApplicationProperties
{
    public:
        static const QString name;
        static const QString version;
        static const QString copyrightYear;

        static const QString link_qt;
        static const QString link_icons8;
        static const QString link_githubRepo;
        static const QString link_wikiHome;
};

#endif // APPLICATIONPROPERTIES

