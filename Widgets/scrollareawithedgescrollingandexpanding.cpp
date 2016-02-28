/*
 *  scrollareawithedgescrollingandexpanding.cpp: Implementation of scrollareawithedgescrollingandexpanding.h
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

 #include "scrollareawithedgescrollingandexpanding.h"
#include <QScrollBar>
#include <QMouseEvent>
#include <QPoint>
#include <QMessageBox>

ScrollAreaWithEdgeScrollingAndExpanding::ScrollAreaWithEdgeScrollingAndExpanding(QWidget *parent) :
    QScrollArea(parent)
{

}

void ScrollAreaWithEdgeScrollingAndExpanding::checkForEdgeScroll(QWidget* sender, QPoint mousePosition_sender)
{
    QPoint mousePosition_this = mapFromGlobal(sender->mapToGlobal(mousePosition_sender));

    if(mousePosition_sender.x() >= sender->width() - scrollAndExpandAreaWidth)
    {
        sender->setMinimumWidth(sender->width() + expandPerStep);
    }
    if(mousePosition_sender.y() >= sender->height() - scrollAndExpandAreaWidth)
    {
        sender->setMinimumHeight(sender->height() + expandPerStep);
    }

    if(mousePosition_this.x() <= scrollAndExpandAreaWidth )
    {
        scrollContent(expandPerStep *-1, 0);
    }
    if(mousePosition_this.y() <= scrollAndExpandAreaWidth)
    {
        scrollContent(0, expandPerStep *-1);
    }
    if(mousePosition_this.x() >= visibleRegion().boundingRect().width() - scrollAndExpandAreaWidth)
    {
        scrollContent(expandPerStep, 0);
    }
    if(mousePosition_this.y() >= visibleRegion().boundingRect().height() - scrollAndExpandAreaWidth)
    {
        scrollContent(0, expandPerStep);
    }

}

void ScrollAreaWithEdgeScrollingAndExpanding::scrollContent(int dx, int dy)
{
    horizontalScrollBar()->setValue(horizontalScrollBar()->value() + dx);
    verticalScrollBar()->setValue(verticalScrollBar()->value() + dy);
}
