/*
 * errorblock.cpp: Implementation of errorblock.h
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

#include "errorblock.h"

ErrorBlock::ErrorBlock(ComponentArea *parent, QPoint location, QColor color, bool positionLocked) :
    ErrorBlock(parent, getNewBlockModel(parent, location, color, positionLocked))
{

}

ErrorBlock::ErrorBlock(ComponentArea *parent, BlockModel blockModel) :
    AbstractInstantRespondingBlock(parent, blockModel.location, defaultSize(), blockModel.color, blockModel.positionLocked)
{
    initSockets(blockModel);
}

ErrorBlock::ErrorBlock()
{

}

void ErrorBlock::drawBlockOnGivenPainter(QPainter *painter, bool paintHoverOutlines, bool selected)
{
    painter->eraseRect(QRect(QPoint(0,0), QPoint(defaultSize().width(), defaultSize().height())));
    painter->fillRect(1, 1, 50, 18, Qt::white);

    if(selected) painter->setPen(QPen(Qt::gray, 3, Qt::SolidLine, Qt::SquareCap));
    else if(paintHoverOutlines) painter->setPen(QPen(Qt::lightGray, 3, Qt::SolidLine, Qt::SquareCap));
    else painter->setPen(QPen(Qt::transparent, 0, Qt::SolidLine, Qt::SquareCap));

    painter->drawRect(1, 1, 50, 18);

    painter->setPen(QPen(this->getColor(), 2, Qt::SolidLine, Qt::SquareCap));
    painter->drawRect(1, 1, 50, 18);
    painter->drawText(3, 3, 44, 12, Qt::AlignCenter, QString("ERROR"));
}

void ErrorBlock::produceOutputValues()
{

}

QString ErrorBlock::getParameters()
{
    return "";
}

void ErrorBlock::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter* painter = new QPainter(this);
    drawBlockOnGivenPainter(painter, this->active, this->isSelected);
}

BlockModel ErrorBlock::getNewBlockModel(ComponentArea *parent, QPoint location, QColor color, bool positionLocked)
{
    BlockModel blockModel = BlockModel();
    blockModel.blockType = AbstractBlock::ERRORDISPLAY;
    blockModel.location = location;
    blockModel.color = color;
    blockModel.positionLocked = positionLocked;
    Q_UNUSED(parent);
    return blockModel;
}
