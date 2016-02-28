/*
 * splitterblock.cpp: Implementation of splitterblock.h
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

#include "splitterblock.h"

SplitterBlock::SplitterBlock(ComponentArea *parent, QPoint location, QColor color, bool positionLocked) :
    SplitterBlock(parent, getNewBlockModel(parent, location, color, positionLocked))
{

}

SplitterBlock::SplitterBlock(ComponentArea *parent, BlockModel blockModel) :
    AbstractInstantRespondingBlock(parent, blockModel.location, defaultSize(), blockModel.color, blockModel.positionLocked)
{
    initSockets(blockModel);
    this->produceOutputValues();
}

SplitterBlock::SplitterBlock()
{
}

SplitterBlock* SplitterBlock::getVirtualInstance()
{
    return new SplitterBlock();
}

void SplitterBlock::drawBlockOnGivenPainter(QPainter *painter, bool paintHoverOutlines, bool selected)
{
    painter->eraseRect(QRect(QPoint(0,0), QPoint(defaultSize().width(), defaultSize().height())));
    painter->fillRect(9, 1, 27, 33, Qt::white);

    if(selected) painter->setPen(QPen(Qt::gray, 3, Qt::SolidLine, Qt::SquareCap));
    else if(paintHoverOutlines) painter->setPen(QPen(Qt::lightGray, 3, Qt::SolidLine, Qt::SquareCap));
    else painter->setPen(QPen(Qt::transparent, 0, Qt::SolidLine, Qt::SquareCap));

    painter->drawRect(9, 1, 27, 33);

    painter->setPen(QPen(this->getColor(), 2, Qt::SolidLine, Qt::SquareCap));
    painter->drawRect(9, 1, 27, 33);
    painter->drawText(1, 1, 43, 33, Qt::AlignCenter, QString("SPLT"));
}

QSize SplitterBlock::defaultSize()
{
    return QSize(45, 35);
}

void SplitterBlock::produceOutputValues()
{
    AbstractSocket::State val = getInputSockets().at(0)->getState();
    Q_FOREACH(OutputSocket *socket, getOutputSockets())
    {
        socket->changeState(val);
    }
}

QString SplitterBlock::getParameters()
{
    return "";
}

void SplitterBlock::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter* painter = new QPainter(this);
    drawBlockOnGivenPainter(painter, this->active, this->isSelected);
}

BlockModel SplitterBlock::getNewBlockModel(ComponentArea *parent, QPoint location, QColor color, bool positionLocked)
{
    BlockModel blockModel = BlockModel();
    blockModel.blockType = AbstractBlock::SPLITTER;
    blockModel.location = location;
    blockModel.color = color;
    blockModel.positionLocked = positionLocked;

    blockModel.inputSocketIds.append(parent->getNextSocketId());
    blockModel.outputSocketIds.append(parent->getNextSocketId());
    blockModel.outputSocketIds.append(parent->getNextSocketId());

    return blockModel;
}
