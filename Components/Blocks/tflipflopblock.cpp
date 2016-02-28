/*
 * tflipflopblock.cpp: Implementation of tflipflopblock.h
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

#include "tflipflopblock.h"

void TFlipFlopBlock::drawBlockOnGivenPainter(QPainter *painter, bool active, bool selected)
{

    painter->eraseRect(QRect(QPoint(0,0), QPoint(defaultSize().width(), defaultSize().height())));
    painter->fillRect(9, 1, 40, 40, Qt::white);

    if(selected) painter->setPen(QPen(Qt::gray, 3, Qt::SolidLine, Qt::SquareCap));
    else if(active) painter->setPen(QPen(Qt::lightGray, 3, Qt::SolidLine, Qt::SquareCap));
    else painter->setPen(QPen(Qt::transparent, 0, Qt::SolidLine, Qt::SquareCap));

    painter->drawRect(8, 1, 41, 40);

    painter->setPen(QPen(getColor(), 1, Qt::SolidLine, Qt::SquareCap));
    painter->drawRect(8, 1, 41, 40);
    painter->drawText(13, 11, 40, 40, Qt::AlignTop | Qt::AlignLeft, QString("T"));
    painter->drawText(13, 3, 32, 20, Qt::AlignTop | Qt::AlignRight, QString("Q"));
    painter->drawText(13, 20, 32, 40, Qt::AlignTop | Qt::AlignRight, QString("!Q"));
}

TFlipFlopBlock::TFlipFlopBlock()
{

}

TFlipFlopBlock::TFlipFlopBlock(ComponentArea *parent, QPoint location, QColor color, bool positionLocked) :
    TFlipFlopBlock(parent, getNewBlockModel(parent, location, color, positionLocked))
{

}

TFlipFlopBlock::TFlipFlopBlock(ComponentArea *parent, BlockModel blockModel) :
    AbstractInstantRespondingBlock(parent, blockModel.location, defaultSize(), blockModel.color, blockModel.positionLocked)
{
    initSockets(blockModel);
    produceOutputValues();
}

void TFlipFlopBlock::produceOutputValues()
{
    AbstractSocket::State currentInputState = getInputSockets().at(0)->getState();
    if(currentInputState != lastInputState)
    {
        if(currentInputState == AbstractSocket::HIGH)
        {
            if(getOutputSockets().at(0)->getState() == AbstractSocket::HIGH)
            {
                getOutputSockets().at(0)->changeToLow();
                getOutputSockets().at(1)->changeToHigh();
            }
            else
            {
                getOutputSockets().at(0)->changeToHigh();
                getOutputSockets().at(1)->changeToLow();
            }
        }
        lastInputState = currentInputState;
    }
}

QString TFlipFlopBlock::getParameters()
{
    return "";
}

void TFlipFlopBlock::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter* painter = new QPainter(this);
    drawBlockOnGivenPainter(painter, active, isSelected);
}

BlockModel TFlipFlopBlock::getNewBlockModel(ComponentArea *parent, QPoint location, QColor color, bool positionLocked)
{
    BlockModel blockModel = BlockModel();
    blockModel.blockType = AbstractBlock::TFLIPFLOP;
    blockModel.location = location;
    blockModel.color = color;
    blockModel.positionLocked = positionLocked;

    blockModel.inputSocketIds.append(parent->getNextSocketId());
    blockModel.outputSocketIds.append(parent->getNextSocketId()); blockModel.outputSocketIds.append(parent->getNextSocketId());

    return blockModel;

}

