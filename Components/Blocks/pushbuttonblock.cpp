/*
 * pushbuttonblock.cpp: Implementation of pushbuttonblock.h
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

#include "pushbuttonblock.h"

PushButtonBlock::PushButtonBlock(ComponentArea *parent, QPoint location, QColor color, bool positionLocked) :
    PushButtonBlock(parent, getNewBlockModel(parent, location, color, positionLocked))
{

}

PushButtonBlock::PushButtonBlock(ComponentArea *parent, BlockModel blockModel) :
    AbstractInteractiveBlock(parent, blockModel.location, defaultSize(), blockModel.color, blockModel.positionLocked)
{
    initSockets(blockModel);
    produceOutputValues();
}

PushButtonBlock::PushButtonBlock()
{
}

PushButtonBlock* PushButtonBlock::getVirtualInstance()
{
    return new PushButtonBlock();
}

void PushButtonBlock::drawBlockOnGivenPainter(QPainter *painter, bool paintHoverOutlines, bool selected)
{
    drawBlockOnGivenPainter(painter, paintHoverOutlines, selected, 10);
}

void PushButtonBlock::drawBlockOnGivenPainter(QPainter *painter, bool paintHoverOutlines, bool selected, int leftConnectionPointY)
{
    painter->eraseRect(QRect(QPoint(0,0), QPoint(defaultSize().width(), defaultSize().height())));
    painter->fillRect(9, 1, 22, 25, Qt::white);

    if(selected) painter->setPen(QPen(Qt::gray, 3, Qt::SolidLine, Qt::SquareCap));
    else if(paintHoverOutlines) painter->setPen(QPen(Qt::lightGray, 3, Qt::SolidLine, Qt::SquareCap));
    else painter->setPen(QPen(Qt::transparent, 0, Qt::SolidLine, Qt::SquareCap));


    painter->drawRect(8,6,24,20);
    painter->drawLine(8, leftConnectionPointY, 13, leftConnectionPointY);
    painter->drawLine(13, leftConnectionPointY, 26, (int)(defaultSize().height() /2));
    painter->drawLine(26, (int)(defaultSize().height() /2), 31, (int)(defaultSize().height() /2));

    painter->drawLine(20, leftConnectionPointY + (defaultSize().height() /2 - leftConnectionPointY) /2, 20, 0 + (leftConnectionPointY - 10) /2);
    painter->drawLine(16, 0 + (leftConnectionPointY - 10) /2, 24, 0 + (leftConnectionPointY - 10) /2);


    painter->setPen(QPen(this->getColor(), 1, Qt::SolidLine, Qt::SquareCap));
    painter->drawRect(8,6,24,20);
    painter->setPen(QPen(this->getColor(), 1, Qt::SolidLine, Qt::SquareCap));
    painter->drawLine(8, 10, 13, 10);
    painter->drawLine(8, 20, 13, 20);
    painter->drawLine(8, leftConnectionPointY, 13, leftConnectionPointY);
    painter->drawLine(13, leftConnectionPointY, 26, (int)(defaultSize().height() /2));
    painter->drawLine(26, (int)(defaultSize().height() /2), 31, (int)(defaultSize().height() /2));

    painter->drawLine(20, leftConnectionPointY + (defaultSize().height() /2 - leftConnectionPointY) /2, 20, 0 + (leftConnectionPointY - 10) /2);
    painter->drawLine(16, 0 + (leftConnectionPointY - 10) /2, 24, 0 + (leftConnectionPointY - 10) /2);
}

QSize PushButtonBlock::defaultSize()
{
    return QSize(40, 32);
}

void PushButtonBlock::produceOutputValues()
{
    if(!pushed)
    {
        getOutputSockets().at(0)->changeState(getInputSockets().at(0)->getState());
    }
    else
    {
        getOutputSockets().at(0)->changeState(getInputSockets().at(1)->getState());
    }
}

QString PushButtonBlock::getParameters()
{
    return "";
}

void PushButtonBlock::userInteractionBeginEvent()
{
    pushed = true;
    updateOutputs();
    emit requestRepaint();
}

void PushButtonBlock::userInteractionEndEvent()
{
    pushed = false;
    updateOutputs();
    emit requestRepaint();
}

void PushButtonBlock::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter* painter = new QPainter(this);
    int leftConnectionY;
    if(!pushed)
    {
        leftConnectionY = getInputSockets().at(0)->pos().y() + getInputSockets().at(0)->size().height() /2;
    }
    else
    {
        leftConnectionY = getInputSockets().at(1)->pos().y() + getInputSockets().at(1)->size().height() /2;
    }

    drawBlockOnGivenPainter(painter, active, isSelected,leftConnectionY);
}

BlockModel PushButtonBlock::getNewBlockModel(ComponentArea *parent, QPoint location, QColor color, bool positionLocked)
{
    BlockModel blockModel = BlockModel();
    blockModel.blockType = AbstractBlock::PUSHBUTTON;
    blockModel.location = location;
    blockModel.color = color;
    blockModel.positionLocked = positionLocked;

    blockModel.inputSocketIds.append(parent->getNextSocketId());
    blockModel.inputSocketIds.append(parent->getNextSocketId());
    blockModel.outputSocketIds.append(parent->getNextSocketId());

    return blockModel;
}
