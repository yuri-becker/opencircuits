/*
 * abstractinstantrespondingblock.h: Calculates outputs undelayed when receiving new inputs.
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

#ifndef INSTANTRESPONDINGBLOCK_H
#define INSTANTRESPONDINGBLOCK_H

#include "Components/abstractblock.h"

class AbstractInstantRespondingBlock : public AbstractBlock
{
    Q_OBJECT

    public:
        void updateOutputs();

    protected:
        AbstractInstantRespondingBlock(ComponentArea *parent = 0, QPoint location = QPoint(0,0), QSize size = QSize(0,0), QColor color = Qt::black, bool positionLocked = false);

};

#endif // INSTANTRESPONDINGBLOCK_H
