/*
 * notgateblock.h: NOT-Gate
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

#ifndef NOTGATEBLOCK_H
#define NOTGATEBLOCK_H

#include "Components/Blocks/abstractinstantrespondingblock.h"

class NotGateBlock : public AbstractInstantRespondingBlock
{
    public:
        static NotGateBlock* getVirtualInstance();
        AbstractBlock* createNewInstance(ComponentArea *parent, BlockModel blockModel) { return new NotGateBlock(parent, blockModel); }
        AbstractBlock* createNewInstance(ComponentArea* parent) { return new NotGateBlock(parent); }

        void drawBlockOnGivenPainter(QPainter *painter, bool active, bool isSelected);
        QSize defaultSize();
        BlockType blockType() { return NOTGATE; }

    protected:
        NotGateBlock();
        NotGateBlock(ComponentArea* parent, QPoint location = QPoint(0,0), QColor color = Qt::black, bool positionLocked = false);
        NotGateBlock(ComponentArea *parent, BlockModel blockModel);

        void produceOutputValues();
        QString getParameters();
        void afterMousePressed(QMouseEvent *event) {Q_UNUSED(event); }
        void afterMouseReleased(QMouseEvent* event) { Q_UNUSED(event); }

    private:
        void paintEvent(QPaintEvent *event);

        static BlockModel getNewBlockModel(ComponentArea* parent, QPoint location = QPoint(0,0), QColor color = Qt::black, bool positionLocked = false);
};

#endif // NOTGATEBLOCK_H
