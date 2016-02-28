/*
 * srnorlatchblock.cpp: Implementation of srnorlatchblock.h
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

#include "srnorlatchblock.h"

SrNorLatchBlock::SrNorLatchBlock(ComponentArea *parent, QPoint location, QColor color, bool positionLocked) :
    SrNorLatchBlock(parent, getNewBlockModel(parent, location, color, positionLocked))
{

}

SrNorLatchBlock::SrNorLatchBlock(ComponentArea *parent, BlockModel blockModel) :
    AbstractInstantRespondingBlock(parent, blockModel.location, defaultSize(), blockModel.color, blockModel.positionLocked)
{
    initSockets(blockModel);
    produceOutputValues();
}

SrNorLatchBlock::SrNorLatchBlock()
{

}

void SrNorLatchBlock::drawBlockOnGivenPainter(QPainter *painter, bool active, bool selected)
{
    painter->eraseRect(QRect(QPoint(0,0), QPoint(defaultSize().width(), defaultSize().height())));
    painter->fillRect(9, 1, 40, 40, Qt::white);

    if(selected) painter->setPen(QPen(Qt::gray, 3, Qt::SolidLine, Qt::SquareCap));
    else if(active) painter->setPen(QPen(Qt::lightGray, 3, Qt::SolidLine, Qt::SquareCap));
    else painter->setPen(QPen(Qt::transparent, 0, Qt::SolidLine, Qt::SquareCap));

    painter->drawRect(8, 1, 41, 40);

    painter->setPen(QPen(getColor(), 1, Qt::SolidLine, Qt::SquareCap));
    painter->drawRect(8, 1, 41, 40);
    painter->drawText(13, 3, 40, 40, Qt::AlignTop | Qt::AlignLeft, QString("R"));
    painter->drawText(13, 20, 40, 40, Qt::AlignTop | Qt::AlignLeft, QString("S"));
    painter->drawText(13, 3, 32, 20, Qt::AlignTop | Qt::AlignRight, QString("Q"));
    painter->drawText(13, 20, 32, 40, Qt::AlignTop | Qt::AlignRight, QString("!Q"));
}

void SrNorLatchBlock::produceOutputValues()
{
    AbstractSocket::State s = getInputSockets().at(1)->getState();
    AbstractSocket::State r = getInputSockets().at(0)->getState();

    if(s == AbstractSocket::HIGH && r != AbstractSocket::HIGH) {
        getOutputSockets().at(0)->changeState(AbstractSocket::HIGH);
        getOutputSockets().at(1)->changeState(AbstractSocket::LOW);
    }
    else if (s != AbstractSocket::HIGH && r == AbstractSocket::HIGH) {
        getOutputSockets().at(0)->changeState(AbstractSocket::LOW);
        getOutputSockets().at(1)->changeState(AbstractSocket::HIGH);
    }

}

QString SrNorLatchBlock::getParameters()
{
    return "";
}

void SrNorLatchBlock::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter* painter = new QPainter(this);
    drawBlockOnGivenPainter(painter, active, isSelected);
}

BlockModel SrNorLatchBlock::getNewBlockModel(ComponentArea *parent, QPoint location, QColor color, bool positionLocked)
{
    BlockModel blockModel = BlockModel();
    blockModel.blockType = AbstractBlock::SRNORLATCH;
    blockModel.location = location;
    blockModel.color = color;
    blockModel.positionLocked = positionLocked;

    blockModel.inputSocketIds.append(parent->getNextSocketId());
    blockModel.inputSocketIds.append(parent->getNextSocketId());
    blockModel.outputSocketIds.append(parent->getNextSocketId());
    blockModel.outputSocketIds.append(parent->getNextSocketId());

    return blockModel;
}
