/*
 * srnorlatchblock.h: SR-NOR-Latch
 *
 * Copyright (C) 2016 Yuri Becker <hi@yuri.li>
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

#ifndef SRNORLATCHBLOCK_H
#define SRNORLATCHBLOCK_H

#include "Components/Blocks/abstractinstantrespondingblock.h"

class SrNorLatchBlock : public AbstractInstantRespondingBlock
{
    Q_OBJECT

    public:
        static SrNorLatchBlock* getVirtualInstance() { return new SrNorLatchBlock(); }
        SrNorLatchBlock* createNewInstance(ComponentArea *parent, BlockModel blockModel) { return new SrNorLatchBlock(parent, blockModel); }
        SrNorLatchBlock* createNewInstance(ComponentArea *parent) { return new SrNorLatchBlock(parent); }

        void drawBlockOnGivenPainter(QPainter* painter, bool active, bool isSelected);
        QSize defaultSize() { return QSize(58, 42); }
        BlockType blockType() { return SRNORLATCH; }

    protected:
        SrNorLatchBlock();
        SrNorLatchBlock(ComponentArea* parent, QPoint location = QPoint(0,0), QColor color = Qt::black, bool positionLocked = false);
        SrNorLatchBlock(ComponentArea *parent, BlockModel blockModel);

        void produceOutputValues();
        QString getParameters();
        void afterMousePressed(QMouseEvent* event) { Q_UNUSED(event); }
        void afterMouseReleased(QMouseEvent* event) { Q_UNUSED(event); }

   private:
        void paintEvent(QPaintEvent *event);

        static BlockModel getNewBlockModel(ComponentArea *parent, QPoint location = QPoint(0,0), QColor color = Qt::black, bool positionLocked = false);
};

    #endif // SRNORLATCHBLOCK_H
