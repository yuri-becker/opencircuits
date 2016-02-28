/*
 * errorblock.h: Used when a non-existing block is created.
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

#ifndef ERRORBLOCK_H
#define ERRORBLOCK_H

#include "Components/Blocks/abstractinstantrespondingblock.h"

class ErrorBlock : public AbstractInstantRespondingBlock
{
    Q_OBJECT

    public:
        static ErrorBlock* getVirtualInstance() { return new ErrorBlock(); }
        AbstractBlock* createNewInstance(ComponentArea *parent, BlockModel blockModel) { return new ErrorBlock(parent, blockModel); }
        AbstractBlock* createNewInstance(ComponentArea* parent) { return new ErrorBlock(parent); }

        void drawBlockOnGivenPainter(QPainter *painter, bool active, bool isSelected);
        QSize defaultSize() { return QSize(50,20); }
        BlockType blockType() { return ERRORDISPLAY; }

    protected:
        ErrorBlock();
        ErrorBlock(ComponentArea* parent, QPoint location = QPoint(0,0), QColor color = Qt::black, bool positionLocked = false);
        ErrorBlock(ComponentArea* parent, BlockModel blockModel);

        void produceOutputValues();
        QString getParameters();
        void afterMousePressed(QMouseEvent *event) {Q_UNUSED(event); }
        void afterMouseReleased(QMouseEvent* event) { Q_UNUSED(event); }

    private:
        void paintEvent(QPaintEvent* event);

        static BlockModel getNewBlockModel(ComponentArea *parent, QPoint location = QPoint(0,0), QColor color = Qt::black, bool positionLocked = false);
};

#endif // ERRORBLOCK_H
