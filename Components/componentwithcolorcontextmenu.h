/*
 *  componentwithcolorcontextmenu.h: Color can be changed via context-menu
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

#ifndef COMPONENTWITHCOLORCONTEXTMENU_H
#define COMPONENTWITHCOLORCONTEXTMENU_H

#include <QWidget>
#include <QList>
#include <QIcon>

#include "Components/component.h"

class ComponentWithColorContextMenu : public Component
{

    Q_OBJECT


    public:
        ComponentWithColorContextMenu(QWidget *parent, QPoint location, QSize size, QColor color = Qt::black);

    private slots:
        void contextMenu_colorTriggered_black();
        void contextMenu_colorTriggered_yellow();
        void contextMenu_colorTriggered_orange();
        void contextMenu_colorTriggered_red();
        void contextMenu_colorTriggered_violet();
        void contextMenu_colorTriggered_blue();
        void contextMenu_colorTriggered_cyan();
        void contextMenu_colorTriggered_green();

    private:
        void initContextMenu();
};

#endif // COMPONENTWITHCOLORCONTEXTMENU_H
