/*
 * abstractinteractiveblock.cpp:  Implementation of abstractinteractiveblock.h
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

#include "abstractinteractiveblock.h"
#include "Widgets/componentarea.h"

AbstractInteractiveBlock::AbstractInteractiveBlock(ComponentArea *parent, QPoint location, QSize size, QColor color, bool positionLocked)
    : AbstractInstantRespondingBlock(parent, location, size, color, positionLocked)
{

}

void AbstractInteractiveBlock::afterMousePressed(QMouseEvent *event)
{
    if(parent->simIsRunning() && event->button() == Qt::LeftButton)
    {
        userInteractionBeginEvent();
    }
}

void AbstractInteractiveBlock::afterMouseReleased(QMouseEvent *event)
{
    if(parent->simIsRunning() && event->button() == Qt::LeftButton)
    {
        userInteractionEndEvent();
    }
}

