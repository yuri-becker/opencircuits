/*
 * jkflipflopblock.h: JK flip-flop
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

#ifndef JKFLIPFLOPBLOCK_H
#define JKFLIPFLOPBLOCK_H

#include "Components/Blocks/abstractinstantrespondingblock.h"

class JKFlipFlopBlock : public AbstractInstantRespondingBlock
{
    // Q_OBJECT //Doesn't compile with this macro

    public:
        static JKFlipFlopBlock* getVirtualInstance() { return new JKFlipFlopBlock(); }
        JKFlipFlopBlock* createNewInstance(ComponentArea *parent, BlockModel blockModel) { return new JKFlipFlopBlock(parent, blockModel); }
        JKFlipFlopBlock* createNewInstance(ComponentArea *parent) { return new JKFlipFlopBlock(parent); }

        void drawBlockOnGivenPainter(QPainter* painter, bool active, bool isSelected);
        QSize defaultSize() { return QSize(58, 42); }
        BlockType blockType() { return JKFLIPFLOP; }

    protected:
        JKFlipFlopBlock();
        JKFlipFlopBlock(ComponentArea* parent, QPoint location = QPoint(0,0), QColor color = Qt::black, bool positionLocked = false);
        JKFlipFlopBlock(ComponentArea *parent, BlockModel blockModel);

        void produceOutputValues();
        QString getParameters();
        void afterMousePressed(QMouseEvent* event) { Q_UNUSED(event); }
        void afterMouseReleased(QMouseEvent* event) { Q_UNUSED(event); }

    private:
        void paintEvent(QPaintEvent *event);

        static BlockModel getNewBlockModel(ComponentArea *parent, QPoint location = QPoint(0,0), QColor color = Qt::black, bool positionLocked = false);
        bool toggled = false;
};

#endif // JKFLIPFLOPBLOCK_H
