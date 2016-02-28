/*
 *  scrollareawithedgescrollingandexpanding.h: QScrollArea which can be told to expand its content
 * or to scroll.
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

#ifndef SCROLLAREAWITHEDGESCROLLING_H
#define SCROLLAREAWITHEDGESCROLLING_H

#include <QScrollArea>

class ScrollAreaWithEdgeScrollingAndExpanding : public QScrollArea
{
    Q_OBJECT
    public:
        ScrollAreaWithEdgeScrollingAndExpanding(QWidget* parent = 0);

    public slots:
        void checkForEdgeScroll(QWidget* sender, QPoint mousePosition_sender);
        void scrollContent(int dx, int dy);

    private:
        const int scrollAndExpandAreaWidth = 20;
        const int expandPerStep = 10;

};

#endif // SCROLLAREAWITHEDGESCROLLING_H
