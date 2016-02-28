/*
 *  blockcatalog.h: Catalog from which blocks can be dragged into the ComponentArea in order
 * to create them.
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

#ifndef BLOCKCATALOG_H
#define BLOCKCATALOG_H

#include <QTabWidget>

class BlockCatalog : public QTabWidget
{
    Q_OBJECT
    public:
        BlockCatalog(QWidget* parent = 0);

     signals:
       void catalogBlock_whatIsThisTriggered(int targetBlockType);

    private slots:
       void pass_catalogBlock_whatIsThisTriggered(int targetBlockType) { emit catalogBlock_whatIsThisTriggered(targetBlockType); }

    private:
        void initWidget();
        void initPages();

};

#endif // BLOCKCATALOG_H
