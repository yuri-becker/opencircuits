/*
 *  blockcatalogpage.h: Page in the BlockCatalog, aka. a QWidget drawing a white background
 * which is not overridden by certain desktop environments like xfce.
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

#ifndef BLOCKCATALOGPAGE_H
#define BLOCKCATALOGPAGE_H

#include <QWidget>

class BlockCatalogPage : public QWidget
{
    Q_OBJECT

    public:
        explicit BlockCatalogPage(QWidget *parent = 0);

    private:
        void paintEvent(QPaintEvent* event);
};

#endif // BLOCKCATALOGPAGE_H
