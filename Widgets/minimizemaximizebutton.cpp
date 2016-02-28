/*
 *  minimizemaximizebutton.cpp: Implementation of minimizemaximizebutton.h
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

#include "minimizemaximizebutton.h"

MinimizeMaximizeButton::MinimizeMaximizeButton(QWidget *parent) : QToolButton(parent)
{
    initWidget();
}

void MinimizeMaximizeButton::initWidget()
{
    minimizeIcon.addFile(QStringLiteral("cancel_26px.png"), QSize(), QIcon::Normal, QIcon::Off);
    maximizeIcon.addFile(QStringLiteral(":/images/Resources/GenericIcons/maximize_window_26px.png"), QSize(), QIcon::Normal, QIcon::Off);

    setText("");
    setIcon(minimizeIcon);
    connect(this, SIGNAL(clicked(bool)), this, SLOT(minimizeMaximize()));
}

void MinimizeMaximizeButton::minimizeMaximize()
{
    if(!maximized) triggerMaximize();
    else triggerMinimize();
}

void MinimizeMaximizeButton::triggerMaximize()
{
    maximized = true;
    setIcon(minimizeIcon);
    emit maximizeTriggered();
}
void MinimizeMaximizeButton::triggerMinimize()
{
    maximized = false;
    setIcon(maximizeIcon);
    emit minimizeTriggered();
}
