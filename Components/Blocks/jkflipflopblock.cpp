/*
 * jkflipflopblock.cpp: Implementation of jkflipflopblock.h
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

#include "jkflipflopblock.h"

JKFlipFlopBlock::JKFlipFlopBlock(ComponentArea *parent, QPoint location, QColor color, bool positionLocked) :
    JKFlipFlopBlock(parent, getNewBlockModel(parent, location, color, positionLocked))
{

}

JKFlipFlopBlock::JKFlipFlopBlock(ComponentArea *parent, BlockModel blockModel) :
    AbstractInstantRespondingBlock(parent, blockModel.location, defaultSize(), blockModel.color, blockModel.positionLocked)
{
    initSockets(blockModel);
}

JKFlipFlopBlock::JKFlipFlopBlock()
{

}

void JKFlipFlopBlock::drawBlockOnGivenPainter(QPainter *painter, bool active, bool selected)
{
    painter->eraseRect(QRect(QPoint(0,0), QPoint(defaultSize().width(), defaultSize().height())));
    painter->fillRect(9, 1, 40, 40, Qt::white);

    if(selected) painter->setPen(QPen(Qt::gray, 3, Qt::SolidLine, Qt::SquareCap));
    else if(active) painter->setPen(QPen(Qt::lightGray, 3, Qt::SolidLine, Qt::SquareCap));
    else painter->setPen(QPen(Qt::transparent, 0, Qt::SolidLine, Qt::SquareCap));

    painter->drawRect(8, 1, 41, 40);

    painter->setPen(QPen(getColor(), 1, Qt::SolidLine, Qt::SquareCap));
    painter->drawRect(8, 1, 41, 40);
    painter->drawText(13, 3, 40, 40, Qt::AlignTop | Qt::AlignLeft, QString("J"));
    painter->drawText(13, 20, 40, 40, Qt::AlignTop | Qt::AlignLeft, QString("K"));
    painter->drawText(13, 3, 32, 20, Qt::AlignTop | Qt::AlignRight, QString("Q"));
    painter->drawText(13, 20, 32, 40, Qt::AlignTop | Qt::AlignRight, QString("!Q"));
}

void JKFlipFlopBlock::produceOutputValues()
{
    AbstractSocket::State j = getInputSockets().at(0)->getState();
    AbstractSocket::State k = getInputSockets().at(1)->getState();

    if(j == AbstractSocket::HIGH && k != AbstractSocket::HIGH) {
        getOutputSockets().at(0)->changeState(AbstractSocket::HIGH);
        getOutputSockets().at(1)->changeState(AbstractSocket::LOW);
        toggled = false;
    }
    else if (j != AbstractSocket::HIGH && k == AbstractSocket::HIGH )
    {
        getOutputSockets().at(0)->changeState(AbstractSocket::LOW);
        getOutputSockets().at(1)->changeState(AbstractSocket::HIGH);
        toggled = false;
    }
    else if(j == AbstractSocket::HIGH && k == AbstractSocket::HIGH && !toggled)
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
        toggled = true;
    }
    else if(j != AbstractSocket::HIGH && k != AbstractSocket::HIGH)
    {
        toggled = false;
    }
}

QString JKFlipFlopBlock::getParameters()
{
    return "";
}

void JKFlipFlopBlock::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter* painter = new QPainter(this);
    drawBlockOnGivenPainter(painter, active, isSelected);
}

BlockModel JKFlipFlopBlock::getNewBlockModel(ComponentArea *parent, QPoint location, QColor color, bool positionLocked)
{
    BlockModel blockModel = BlockModel();
    blockModel.blockType = AbstractBlock::JKFLIPFLOP;
    blockModel.location = location;
    blockModel.color = color;
    blockModel.positionLocked = positionLocked;

    blockModel.inputSocketIds.append(parent->getNextSocketId());
    blockModel.inputSocketIds.append(parent->getNextSocketId());
    blockModel.outputSocketIds.append(parent->getNextSocketId());
    blockModel.outputSocketIds.append(parent->getNextSocketId());
    return blockModel;
}
