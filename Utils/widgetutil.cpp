/*
 *  widgetutil.cpp: Implementation of widgetutil.h
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

#include "widgetutil.h"

#include <QMouseEvent>

bool WidgetUtil::widgetIsOnPoint(QPoint point_global, QWidget *widget)
{
    QRect rekt = QRect(
                widget->parentWidget()->mapToGlobal(widget->pos()),
                widget->size()
                );
    return rekt.contains(point_global);
}


QMouseEvent *WidgetUtil::mapMouseEvent(QWidget *from, QWidget *to, QMouseEvent *originalEvent)
{
    return new QMouseEvent(
                originalEvent->type(),
                to->mapFromGlobal(from->mapToGlobal(originalEvent->pos())),
                originalEvent->button(),
                originalEvent->buttons(),
                originalEvent->modifiers()
                );
}
