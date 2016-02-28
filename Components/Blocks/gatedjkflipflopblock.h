/*
 * gatedjkflipflopblock.h: Gated JK flip-flop
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

#ifndef GATEDJKFLIPFLOPBLOCK_H
#define GATEDJKFLIPFLOPBLOCK_H

#include "Components/Blocks/abstractinstantrespondingblock.h"

class GatedJKFlipFlopBlock : public AbstractInstantRespondingBlock
{
    public:
        static GatedJKFlipFlopBlock* getVirtualInstance() { return new GatedJKFlipFlopBlock(); }
        GatedJKFlipFlopBlock* createNewInstance(ComponentArea *parent, BlockModel blockModel) { return new GatedJKFlipFlopBlock(parent, blockModel); }
        GatedJKFlipFlopBlock* createNewInstance(ComponentArea *parent) { return new GatedJKFlipFlopBlock(parent); }

        void drawBlockOnGivenPainter(QPainter* painter, bool active, bool isSelected);
        QSize defaultSize() { return QSize(58, 50); }
        BlockType blockType() { return GATEDJKFLIPFLOP; }

    protected:
        GatedJKFlipFlopBlock();
        GatedJKFlipFlopBlock(ComponentArea* parent, QPoint location = QPoint(0,0), QColor color = Qt::black, bool positionLocked = false);
        GatedJKFlipFlopBlock(ComponentArea *parent, BlockModel blockModel);

        void produceOutputValues();
        QString getParameters();
        void afterMousePressed(QMouseEvent* event) { Q_UNUSED(event); }
        void afterMouseReleased(QMouseEvent* event) { Q_UNUSED(event); }

    private:
        void paintEvent(QPaintEvent *event);

        static BlockModel getNewBlockModel(ComponentArea *parent, QPoint location = QPoint(0,0), QColor color = Qt::black, bool positionLocked = false);
        bool toggled = false;
};

#endif // GATEDJKFLIPFLOPBLOCK_H
