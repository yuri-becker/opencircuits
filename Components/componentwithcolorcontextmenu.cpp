/*
 *  componentwithcolorcontextmenu.cpp: Implementation of componentwithcolorcontextmenu.h
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

#include "componentwithcolorcontextmenu.h"

ComponentWithColorContextMenu::ComponentWithColorContextMenu(QWidget *parent, QPoint location, QSize size, QColor color) :
    Component(parent, location, size, color)
{
    setContextMenuPolicy(Qt::CustomContextMenu);
    initContextMenu();
}

void ComponentWithColorContextMenu::contextMenu_colorTriggered_black()
{
    emit requestPropertyChange(property_component_color, QColor(Qt::black).name());
}

void ComponentWithColorContextMenu::contextMenu_colorTriggered_yellow()
{
    emit requestPropertyChange(property_component_color, QColor(Qt::yellow).name());
}

void ComponentWithColorContextMenu::contextMenu_colorTriggered_orange()
{
    emit requestPropertyChange(property_component_color, QColor::fromRgb(255,165,0,255).name());
}

void ComponentWithColorContextMenu::contextMenu_colorTriggered_red()
{
    emit requestPropertyChange(property_component_color, QColor(Qt::red).name());
}

void ComponentWithColorContextMenu::contextMenu_colorTriggered_violet()
{
    emit requestPropertyChange(property_component_color, QColor::fromRgb(238,130,238,255).name());
}

void ComponentWithColorContextMenu::contextMenu_colorTriggered_blue()
{
    emit requestPropertyChange(property_component_color, QColor(Qt::blue).name());
}

void ComponentWithColorContextMenu::contextMenu_colorTriggered_cyan()
{
    emit requestPropertyChange(property_component_color, QColor(Qt::cyan).name());
}

void ComponentWithColorContextMenu::contextMenu_colorTriggered_green()
{
    emit requestPropertyChange(property_component_color, QColor(Qt::darkGreen).name());
}

void ComponentWithColorContextMenu::initContextMenu()
{
    QList<QAction*> actions;
    {
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/Resources/ColorContextMenuIcons/black.png"), QSize(), QIcon::Normal, QIcon::Off);

        QAction* newAction = new QAction(icon, tr("Black"), 0);
        newAction->setIconVisibleInMenu(true);
        connect(newAction, &QAction::triggered, this, &ComponentWithColorContextMenu::contextMenu_colorTriggered_black);
        actions.append(newAction);
    }
    {
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/Resources/ColorContextMenuIcons/yellow.png"), QSize(), QIcon::Normal, QIcon::Off);

        QAction* newAction = new QAction(icon, tr("Yellow"), 0);
        newAction->setIconVisibleInMenu(true);
        connect(newAction, &QAction::triggered, this, &ComponentWithColorContextMenu::contextMenu_colorTriggered_yellow);
        actions.append(newAction);
    }
    {
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/Resources/ColorContextMenuIcons/orange.png"), QSize(), QIcon::Normal, QIcon::Off);

        QAction* newAction = new QAction(icon, tr("Orange"), 0);
        newAction->setIconVisibleInMenu(true);
        connect(newAction, &QAction::triggered, this, &ComponentWithColorContextMenu::contextMenu_colorTriggered_orange);
        actions.append(newAction);
    }
    {
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/Resources/ColorContextMenuIcons/red.png"), QSize(), QIcon::Normal, QIcon::Off);

        QAction* newAction = new QAction(icon, tr("Red"), 0);
        newAction->setIconVisibleInMenu(true);
        connect(newAction, &QAction::triggered, this, &ComponentWithColorContextMenu::contextMenu_colorTriggered_red);
        actions.append(newAction);
    }
    {
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/Resources/ColorContextMenuIcons/violett.png"), QSize(), QIcon::Normal, QIcon::Off);

        QAction* newAction = new QAction(icon, tr("Purple"), 0);
        newAction->setIconVisibleInMenu(true);
        connect(newAction, &QAction::triggered, this, &ComponentWithColorContextMenu::contextMenu_colorTriggered_violet);
        actions.append(newAction);
    }
    {
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/Resources/ColorContextMenuIcons/blue.png"), QSize(), QIcon::Normal, QIcon::Off);

        QAction* newAction = new QAction(icon, tr("Blue"), 0);
        newAction->setIconVisibleInMenu(true);
        connect(newAction, &QAction::triggered, this, &ComponentWithColorContextMenu::contextMenu_colorTriggered_blue);
        actions.append(newAction);
    }
    {
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/Resources/ColorContextMenuIcons/cyan.png"), QSize(), QIcon::Normal, QIcon::Off);

        QAction* newAction = new QAction(icon, tr("Cyan"), 0);
        newAction->setIconVisibleInMenu(true);
        connect(newAction, &QAction::triggered, this, &ComponentWithColorContextMenu::contextMenu_colorTriggered_cyan);
        actions.append(newAction);
    }
    {
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/Resources/ColorContextMenuIcons/green.png"), QSize(), QIcon::Normal, QIcon::Off);

        QAction* newAction = new QAction(icon, tr("Green"), 0);
        newAction->setIconVisibleInMenu(true);
        connect(newAction, &QAction::triggered, this, &ComponentWithColorContextMenu::contextMenu_colorTriggered_green);
        actions.append(newAction);
    }
    contextMenu.addActions(actions);
    contextMenu.addSeparator();
 }
