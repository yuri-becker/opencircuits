/*
 * andgateblock.h: AND-Gate
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

#ifndef ANDGATEBLOCK_H
#define ANDGATEBLOCK_H

#include "Components/Blocks/abstractinstantrespondingblock.h"

class AndGateBlock : public AbstractInstantRespondingBlock
{
    Q_OBJECT

    public:
        static AndGateBlock* getVirtualInstance() {  return new AndGateBlock(); }
        AbstractBlock* createNewInstance(ComponentArea *parent, BlockModel blockModel) { return new AndGateBlock(parent, blockModel); }
        AbstractBlock* createNewInstance(ComponentArea* parent) { return new AndGateBlock(parent); }

        void drawBlockOnGivenPainter(QPainter *painter, bool active, bool isSelected);
        QSize defaultSize() { return QSize(45,42); }
        BlockType blockType() { return ANDGATE; }

    protected:
        AndGateBlock();
        AndGateBlock(ComponentArea *parent, QPoint location = QPoint(0,0), QColor color = Qt::black, bool positionLocked = false);
        AndGateBlock(ComponentArea *parent, BlockModel blockModel);

        void produceOutputValues();
        QString getParameters();
        void afterMousePressed(QMouseEvent *event) {Q_UNUSED(event); }
        void afterMouseReleased(QMouseEvent* event) { Q_UNUSED(event); }

    private:
        void paintEvent(QPaintEvent *event);

        static BlockModel getNewBlockModel(ComponentArea *parent, QPoint location = QPoint(0,0), QColor color = Qt::black, bool positionLocked = false);
};

#endif // ANDGATEBLOCK_H
