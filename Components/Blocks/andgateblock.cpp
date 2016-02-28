/*
 * andgateblock.cpp: Implementation of andgateblock.h
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

#include "andgateblock.h"

#include <QPainter>

AndGateBlock::AndGateBlock(ComponentArea *parent, QPoint location, QColor color, bool positionLocked) :
    AndGateBlock(parent, getNewBlockModel(parent, location, color, positionLocked))
{

}

AndGateBlock::AndGateBlock(ComponentArea *parent, BlockModel blockModel) :
    AbstractInstantRespondingBlock(parent, blockModel.location, defaultSize(), blockModel.color, blockModel.positionLocked)
{
    initSockets(blockModel);
    this->produceOutputValues();
}

AndGateBlock::AndGateBlock()
{
}

void AndGateBlock::drawBlockOnGivenPainter(QPainter *painter, bool paintHoverOutlines, bool selected)
{
    painter->eraseRect(QRect(QPoint(0,0), QPoint(defaultSize().width(), defaultSize().height())));
    painter->fillRect(9, 1, 27, 40, Qt::white);

    if(selected) painter->setPen(QPen(Qt::gray, 3, Qt::SolidLine, Qt::SquareCap));
    else if(paintHoverOutlines) painter->setPen(QPen(Qt::lightGray, 3, Qt::SolidLine, Qt::SquareCap));
    else painter->setPen(QPen(Qt::transparent, 0, Qt::SolidLine, Qt::SquareCap));

    painter->drawRect(8, 1, 28, 40);

    painter->setPen(QPen(this->getColor(), 1, Qt::SolidLine, Qt::SquareCap));
    painter->drawRect(8, 1, 28, 40);
    painter->drawText(1, 1, 43, 40, Qt::AlignCenter, QString("&"));
}

void AndGateBlock::produceOutputValues()
{
    if(getInputSockets().at(0)->getState() != AbstractSocket::NONE ||
            getInputSockets().at(1)->getState() != AbstractSocket::NONE)
    {
        bool val1 = getInputSockets().at(0)->getState() == AbstractSocket::HIGH;
        bool val2 = getInputSockets().at(1)->getState() == AbstractSocket::HIGH;
        bool res = val1 && val2;
        getOutputSockets().at(0)->changeState(AbstractSocket::stateFromBool(res));
    }
    else
    {
        getOutputSockets().at(0)->changeState(AbstractSocket::NONE);
    }
}

QString AndGateBlock::getParameters()
{
    return "";
}

void AndGateBlock::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter* painter = new QPainter(this);
    drawBlockOnGivenPainter(painter, active, isSelected);
}

BlockModel AndGateBlock::getNewBlockModel(ComponentArea *parent, QPoint location, QColor color, bool positionLocked)
{
    BlockModel blockModel = BlockModel();
    blockModel.blockType = AbstractBlock::ANDGATE;
    blockModel.location = location;
    blockModel.color = color;
    blockModel.positionLocked = positionLocked;

    blockModel.inputSocketIds.append(parent->getNextSocketId());
    blockModel.inputSocketIds.append(parent->getNextSocketId());
    blockModel.outputSocketIds.append(parent->getNextSocketId());

    return blockModel;
}
