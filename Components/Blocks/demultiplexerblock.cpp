/*
 * demultiplexerblock.cpp: Implementation of demultiplexerblock.h
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

#include "demultiplexerblock.h"

DemultiplexerBlock::DemultiplexerBlock(ComponentArea* parent, QPoint location, QColor color, bool positionLocked) :
    DemultiplexerBlock(parent, getNewBlockModel(parent, location, color, positionLocked))
{

}

DemultiplexerBlock::DemultiplexerBlock(ComponentArea* parent, BlockModel blockModel) :
    AbstractInstantRespondingBlock(parent, blockModel.location, defaultSize(), blockModel.color, blockModel.positionLocked)
{
    initSockets(blockModel);
}

void DemultiplexerBlock::drawBlockOnGivenPainter(QPainter* painter, bool active, bool isSelected)
{
    painter->eraseRect(QRect(QPoint(0,0), QPoint(defaultSize().width(), defaultSize().height())));
    painter->fillRect(9,9,27,68, Qt::white);

    if(isSelected) painter->setPen(QPen(Qt::gray, 3, Qt::SolidLine, Qt::SquareCap));
    else if(active) painter->setPen(QPen(Qt::lightGray, 3, Qt::SolidLine, Qt::SquareCap));
    else painter->setPen(QPen(Qt::transparent, 0, Qt::SolidLine, Qt::SquareCap));

    QVector<QPoint> vector;
    vector.append(QPoint(36,9));
    vector.append(QPoint(36,77));
    vector.append(QPoint(14,77));
    vector.append(QPoint(8,71));
    vector.append(QPoint(8,15));
    vector.append(QPoint(14,9));
    vector.append(QPoint(36,9));

    QPolygon polygon = QPolygon(vector);
    painter->drawPolygon(polygon);

    painter->setPen(QPen(this->getColor(), 1, Qt::SolidLine, Qt::SquareCap));
    painter->drawPolygon(polygon);

    painter->drawText(QRect(0, 0, defaultSize().width(), defaultSize().height()), Qt::AlignHCenter | Qt::AlignVCenter, "d\ne\nm\nu\nx");
}

DemultiplexerBlock::DemultiplexerBlock()
{

}

void DemultiplexerBlock::produceOutputValues()
{

    QString selInputs = "";
    Q_FOREACH(AdditionalInputSocket* additionalInput, getAdditionalInputSockets())
    {
        selInputs =  selInputs.append(QString::number(AbstractSocket::stateToBool(additionalInput->getState())));
    }

    int selectedOutput = selInputs.toInt(0,2);

    for(int i = 0; i < getOutputSockets().size(); i++)
    {
        if(i == selectedOutput) getOutputSockets().at(i)->changeState(getInputSockets().at(0)->getState());
        else getOutputSockets().at(i)->changeState(AbstractSocket::LOW);
    }

}

QString DemultiplexerBlock::getParameters()
{
    return "";
}

void DemultiplexerBlock::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)
    QPainter* painter = new QPainter(this);
    drawBlockOnGivenPainter(painter, active, isSelected);
}

BlockModel DemultiplexerBlock::getNewBlockModel(ComponentArea* parent, QPoint location, QColor color, bool positionLocked)
{
    BlockModel blockModel = BlockModel();
    blockModel.blockType = AbstractBlock::DEMULTIPLEXER;
    blockModel.location = location;
    blockModel.color = color;
    blockModel.positionLocked = positionLocked;

    blockModel.additionalInputSocketIds.append(parent->getNextSocketId());
    blockModel.additionalInputSocketIds.append(parent->getNextSocketId());

    blockModel.inputSocketIds.append(parent->getNextSocketId());

    blockModel.outputSocketIds.append(parent->getNextSocketId());
    blockModel.outputSocketIds.append(parent->getNextSocketId());
    blockModel.outputSocketIds.append(parent->getNextSocketId());
    blockModel.outputSocketIds.append(parent->getNextSocketId());

    return blockModel;
}

