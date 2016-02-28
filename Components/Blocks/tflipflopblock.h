/*
 * tflipflopblock.h: T flip-flop
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

#ifndef TFLIPFLOPBLOCK_H
#define TFLIPFLOPBLOCK_H

#include "Components/Blocks/abstractinstantrespondingblock.h"

class TFlipFlopBlock : public AbstractInstantRespondingBlock
{
    Q_OBJECT

    public:
        static TFlipFlopBlock* getVirtualInstance() { return new TFlipFlopBlock(); }
        TFlipFlopBlock* createNewInstance(ComponentArea *parent, BlockModel blockModel) { return new TFlipFlopBlock(parent, blockModel); }
        TFlipFlopBlock* createNewInstance(ComponentArea *parent) { return new TFlipFlopBlock(parent); }

        void drawBlockOnGivenPainter(QPainter* painter, bool active, bool isSelected);
        QSize defaultSize() { return QSize(58, 42); }
        BlockType blockType() { return TFLIPFLOP; }

    protected:
        TFlipFlopBlock();
        TFlipFlopBlock(ComponentArea* parent, QPoint location = QPoint(0,0), QColor color = Qt::black, bool positionLocked = false);
        TFlipFlopBlock(ComponentArea *parent, BlockModel blockModel);

        void produceOutputValues();
        QString getParameters();
        void afterMousePressed(QMouseEvent* event) { Q_UNUSED(event); }
        void afterMouseReleased(QMouseEvent* event) { Q_UNUSED(event); }

    private:
        void paintEvent(QPaintEvent *event);

        static BlockModel getNewBlockModel(ComponentArea *parent, QPoint location = QPoint(0,0), QColor color = Qt::black, bool positionLocked = false);

        AbstractSocket::State lastInputState = AbstractSocket::NONE;
};

#endif // TFLIPFLOPBLOCK_H
