/*
 * switchblock.cpp: Implementaion of switchblock.h
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

#include "switchblock.h"

SwitchBlock::SwitchBlock(ComponentArea *parent, QPoint location, QColor color, bool positionLocked) :
    SwitchBlock(parent, getNewBlockModel(parent, location, color, positionLocked))
{

}

SwitchBlock::SwitchBlock(ComponentArea *parent, BlockModel blockModel) :
    AbstractInteractiveBlock(parent, blockModel.location, defaultSize(), blockModel.color, blockModel.positionLocked)
{
    initSockets(blockModel);
    switched = blockModel.parameters.toInt();
    produceOutputValues();
}

SwitchBlock::SwitchBlock()
{
}

SwitchBlock* SwitchBlock::getVirtualInstance()
{
    return new SwitchBlock();
}

void SwitchBlock::drawBlockOnGivenPainter(QPainter *painter, bool paintHoverOutlines, bool selected)
{
    drawBlockOnGivenPainter(painter, paintHoverOutlines, selected, 7);
}

void SwitchBlock::drawBlockOnGivenPainter(QPainter *painter, bool paintHoverOutlines, bool selected, int leftConnectionPointY)
{
    painter->eraseRect(QRect(QPoint(0,0), QPoint(defaultSize().width(), defaultSize().height())));
    painter->fillRect(9, 1, 22, 20, Qt::white);

    if(selected) painter->setPen(QPen(Qt::gray, 3, Qt::SolidLine, Qt::SquareCap));
    else if(paintHoverOutlines) painter->setPen(QPen(Qt::lightGray, 3, Qt::SolidLine, Qt::SquareCap));
    else painter->setPen(QPen(Qt::transparent, 0, Qt::SolidLine, Qt::SquareCap));

    painter->drawRect(8,1,24,20);
    painter->drawLine(8, leftConnectionPointY, 13, leftConnectionPointY);
    painter->drawLine(13, leftConnectionPointY, 26, (int)(defaultSize().height() /2));
    painter->drawLine(26, (int)(defaultSize().height() /2), 31, (int)(defaultSize().height() /2));

    painter->setPen(QPen(this->getColor(), 1, Qt::SolidLine, Qt::SquareCap));
    painter->drawRect(8,1,24,20);
    painter->drawLine(8, 7, 13, 7);
    painter->drawLine(8, 14, 13, 14);
    painter->drawLine(8, leftConnectionPointY, 13, leftConnectionPointY);
    painter->drawLine(13, leftConnectionPointY, 26, (int)(defaultSize().height() /2));
    painter->drawLine(26, (int)(defaultSize().height() /2), 31, (int)(defaultSize().height() /2));
}

QSize SwitchBlock::defaultSize()
{
    return QSize(40, 22);
}

void SwitchBlock::produceOutputValues()
{
    if(!switched)
    {
        getOutputSockets().at(0)->changeState(getInputSockets().at(0)->getState());
    }
    else
    {
        getOutputSockets().at(0)->changeState(getInputSockets().at(1)->getState());
    }
}

QString SwitchBlock::getParameters()
{
    return QString::number(switched);
}

void SwitchBlock::userInteractionBeginEvent()
{
    switched = !switched;
    updateOutputs();
    emit requestRepaint();
}

void SwitchBlock::userInteractionEndEvent()
{
    //Empty
}

void SwitchBlock::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter *painter = new QPainter(this);
    int leftConnectionY;
    if(!switched)
    {
        leftConnectionY = getInputSockets().at(0)->pos().y() + getInputSockets().at(0)->size().height() /2;
    }
    else
    {
        leftConnectionY = getInputSockets().at(1)->pos().y() + getInputSockets().at(1)->size().height() /2;
    }
    drawBlockOnGivenPainter(painter, active, isSelected, leftConnectionY);

}

BlockModel SwitchBlock::getNewBlockModel(ComponentArea *parent, QPoint location, QColor color, bool positionLocked)
{
    BlockModel blockModel = BlockModel();
    blockModel.blockType = AbstractBlock::PUSHBUTTON;
    blockModel.location = location;
    blockModel.color = color;
    blockModel.parameters = QString::number(0);
    blockModel.positionLocked =positionLocked;

    blockModel.inputSocketIds.append(parent->getNextSocketId());
    blockModel.inputSocketIds.append(parent->getNextSocketId());
    blockModel.outputSocketIds.append(parent->getNextSocketId());

    return blockModel;
}

