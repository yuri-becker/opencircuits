/*
 * gatedsrnorlatchblock.cpp: Implementation of gatedsrnorlatchblock.h
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

#include "gatedsrnorlatchblock.h"

GatedSrNorLatchBlock::GatedSrNorLatchBlock(ComponentArea *parent, QPoint location, QColor color, bool positionLocked) :
    GatedSrNorLatchBlock(parent, getNewBlockModel(parent, location, color, positionLocked))
{

}

GatedSrNorLatchBlock::GatedSrNorLatchBlock(ComponentArea *parent, BlockModel blockModel) :
    AbstractInstantRespondingBlock(parent, blockModel.location, defaultSize(), blockModel.color, blockModel.positionLocked)
{
    initSockets(blockModel);
}

GatedSrNorLatchBlock::GatedSrNorLatchBlock()
{

}

void GatedSrNorLatchBlock::drawBlockOnGivenPainter(QPainter *painter, bool active, bool selected)
{
    painter->eraseRect(QRect(QPoint(0,0), QPoint(defaultSize().width(), defaultSize().height())));
    painter->fillRect(9, 1, 40, 48, Qt::white);

    if(selected) painter->setPen(QPen(Qt::gray, 3, Qt::SolidLine, Qt::SquareCap));
    else if(active) painter->setPen(QPen(Qt::lightGray, 3, Qt::SolidLine, Qt::SquareCap));
    else painter->setPen(QPen(Qt::transparent, 0, Qt::SolidLine, Qt::SquareCap));

    painter->drawRect(8, 1, 41, 48);

    painter->setPen(QPen(getColor(), 1, Qt::SolidLine, Qt::SquareCap));
    painter->drawRect(8, 1, 41, 48);
    painter->drawText(13, 3, 40, 40, Qt::AlignTop | Qt::AlignLeft, QString("R"));
    painter->drawText(13, 17, 40, 40, Qt::AlignTop | Qt::AlignLeft, QString("E"));
    painter->drawText(13, 31, 40, 40, Qt::AlignTop | Qt::AlignLeft, QString("S"));
    painter->drawText(13, 7, 32, 20, Qt::AlignTop | Qt::AlignRight, QString("Q"));
    painter->drawText(13, 25, 32, 40, Qt::AlignTop | Qt::AlignRight, QString("!Q"));
}

void GatedSrNorLatchBlock::produceOutputValues()
{

    AbstractSocket::State r = getInputSockets().at(0)->getState();
    AbstractSocket::State gate = getInputSockets().at(1)->getState();
    AbstractSocket::State s = getInputSockets().at(2)->getState();

    if(gate == AbstractSocket::HIGH)
    {

        if(s == AbstractSocket::HIGH && r != AbstractSocket::HIGH) {
            getOutputSockets().at(0)->changeState(AbstractSocket::HIGH);
            getOutputSockets().at(1)->changeState(AbstractSocket::LOW);
        }
        else if (s != AbstractSocket::HIGH && r == AbstractSocket::HIGH) {
            getOutputSockets().at(0)->changeState(AbstractSocket::LOW);
            getOutputSockets().at(1)->changeState(AbstractSocket::HIGH);
        }
    }

}

QString GatedSrNorLatchBlock::getParameters()
{
    return "";
}

void GatedSrNorLatchBlock::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter* painter = new QPainter(this);
    drawBlockOnGivenPainter(painter, active, isSelected);
}

BlockModel GatedSrNorLatchBlock::getNewBlockModel(ComponentArea *parent, QPoint location, QColor color, bool positionLocked)
{
    BlockModel blockModel = BlockModel();
    blockModel.blockType = AbstractBlock::GATEDSRNORLATCH;
    blockModel.location = location;
    blockModel.color = color;
    blockModel.positionLocked = positionLocked;

    blockModel.inputSocketIds.append(parent->getNextSocketId());
    blockModel.inputSocketIds.append(parent->getNextSocketId());
    blockModel.inputSocketIds.append(parent->getNextSocketId());
    blockModel.outputSocketIds.append(parent->getNextSocketId());
    blockModel.outputSocketIds.append(parent->getNextSocketId());

    return blockModel;
}
