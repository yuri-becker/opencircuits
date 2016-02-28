/*
 * gatedsrnorlatchblock.h: Gated SR-NOR-Latch
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

#ifndef GATEDSRNORLATCHBLOCK_H
#define GATEDSRNORLATCHBLOCK_H

#include "Components/Blocks/abstractinstantrespondingblock.h"

class GatedSrNorLatchBlock : public AbstractInstantRespondingBlock
{
        Q_OBJECT

    public:
        static GatedSrNorLatchBlock* getVirtualInstance() { return new GatedSrNorLatchBlock(); }
        GatedSrNorLatchBlock* createNewInstance(ComponentArea *parent, BlockModel blockModel) { return new GatedSrNorLatchBlock(parent, blockModel); }
        GatedSrNorLatchBlock* createNewInstance(ComponentArea *parent) { return new GatedSrNorLatchBlock(parent); }

        void drawBlockOnGivenPainter(QPainter* painter, bool active, bool isSelected);
        QSize defaultSize() { return QSize(58, 50); }
        BlockType blockType() { return GATEDSRNORLATCH; }

    protected:
        GatedSrNorLatchBlock();
        GatedSrNorLatchBlock(ComponentArea* parent, QPoint location = QPoint(0,0), QColor color = Qt::black, bool positionLocked = false);
        GatedSrNorLatchBlock(ComponentArea *parent, BlockModel blockModel);

        void produceOutputValues();
        QString getParameters();
        void afterMousePressed(QMouseEvent* event) { Q_UNUSED(event); }
        void afterMouseReleased(QMouseEvent* event) { Q_UNUSED(event); }

    private:
        void paintEvent(QPaintEvent *event);

        static BlockModel getNewBlockModel(ComponentArea *parent, QPoint location = QPoint(0,0), QColor color = Qt::black, bool positionLocked = false);
};

#endif // GATEDSRNORLATCHBLOCK_H
