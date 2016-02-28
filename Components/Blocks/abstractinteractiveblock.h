/*
 * abstractinteractiveblock.h:  Block which can be interacted with using mouse presses
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

#ifndef ABSTRACTINTERACTIVEBLOCK_H
#define ABSTRACTINTERACTIVEBLOCK_H

#include "Components/Blocks/abstractinstantrespondingblock.h"

class AbstractInteractiveBlock : public AbstractInstantRespondingBlock
{
    Q_OBJECT

    protected:
        AbstractInteractiveBlock(ComponentArea *parent = 0, QPoint location = QPoint(0,0), QSize size = QSize(0,0), QColor color = Qt::black, bool positionLocked = false);

        virtual void userInteractionBeginEvent() = 0;
        virtual void userInteractionEndEvent() = 0;

    private:
        void afterMousePressed(QMouseEvent* event);
        void afterMouseReleased(QMouseEvent* event);
};

#endif // ABSTRACTINTERACTIVEBLOCK_H
