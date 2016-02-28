/*
 * pushbuttonblock.h: Interactive PushButton
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

#ifndef PUSHBUTTONBLOCK_H
#define PUSHBUTTONBLOCK_H

#include "Components/Blocks/abstractinteractiveblock.h"

class PushButtonBlock : public AbstractInteractiveBlock
{
    public:
        static PushButtonBlock* getVirtualInstance();
        AbstractBlock* createNewInstance(ComponentArea *parent, BlockModel blockModel) { return new PushButtonBlock(parent, blockModel); }
        AbstractBlock* createNewInstance(ComponentArea* parent) { return new PushButtonBlock(parent); }

        void drawBlockOnGivenPainter(QPainter *painter, bool active, bool isSelected);
        void drawBlockOnGivenPainter(QPainter *painter, bool active, bool isSelected, int leftConnectionPointY);
        QSize defaultSize();
        BlockType blockType() { return PUSHBUTTON; }

    protected:
        PushButtonBlock();
        PushButtonBlock(ComponentArea *parent, QPoint location = QPoint(0,0), QColor color = Qt::black, bool positionLocked = false);
        PushButtonBlock(ComponentArea *parent, BlockModel blockModel);

        void userInteractionBeginEvent();
        void userInteractionEndEvent();
        void produceOutputValues();
        QString getParameters();

    private:
        bool pushed = false;

        void paintEvent(QPaintEvent* event);

        static BlockModel getNewBlockModel(ComponentArea *parent, QPoint location = QPoint(0,0), QColor color = Qt::black, bool positionLocked = false);
};

#endif // PUSHBUTTONBLOCK_H
