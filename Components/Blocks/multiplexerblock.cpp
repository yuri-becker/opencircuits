/*
 * multiplexerblock.cpp: Implementation of multiplexerblock.h.
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

#include "multiplexerblock.h"

MultiplexerBlock::MultiplexerBlock(ComponentArea* parent, QPoint location, QColor color, bool positionLocked) :
    MultiplexerBlock(parent, getNewBlockModel(parent, location, color, positionLocked))
{

}

MultiplexerBlock::MultiplexerBlock(ComponentArea* parent, BlockModel blockModel) :
    AbstractInstantRespondingBlock(parent, blockModel.location, defaultSize(), blockModel.color, blockModel.positionLocked)
{
    initSockets(blockModel);
}

void MultiplexerBlock::produceOutputValues()
{
    QString selInputs = "";
    Q_FOREACH(AdditionalInputSocket* additionalInput, getAdditionalInputSockets())
    {
        selInputs =  selInputs.append(QString::number(AbstractSocket::stateToBool(additionalInput->getState())));
    }

    int selectedInput = selInputs.toInt(0, 2);

    getOutputSockets().at(0)->changeState(getInputSockets().at(selectedInput)->getState());
}

QString MultiplexerBlock::getParameters()
{
    return "";
}

void MultiplexerBlock::drawBlockOnGivenPainter(QPainter* painter, bool active, bool isSelected)
{
    painter->eraseRect(QRect(QPoint(0,0), QPoint(defaultSize().width(), defaultSize().height())));
    painter->fillRect(9,9,27,68, Qt::white);

    if(isSelected) painter->setPen(QPen(Qt::gray, 3, Qt::SolidLine, Qt::SquareCap));
    else if(active) painter->setPen(QPen(Qt::lightGray, 3, Qt::SolidLine, Qt::SquareCap));
    else painter->setPen(QPen(Qt::transparent, 0, Qt::SolidLine, Qt::SquareCap));

    QVector<QPoint> vector;
    vector.append(QPoint(8,9));
    vector.append(QPoint(8, 77));

    vector.append(QPoint(30, 77));
    vector.append(QPoint(36, 71));
    vector.append(QPoint(36, 15));
    vector.append(QPoint(30, 9));
    vector.append(QPoint(8,9));
    QPolygon polygon = QPolygon(vector);

    painter->drawPolygon(polygon);

    painter->setPen(QPen(this->getColor(), 1, Qt::SolidLine, Qt::SquareCap));
    painter->drawPolygon(polygon);

    painter->drawText(QRect(0, 0, defaultSize().width(), defaultSize().height()), Qt::AlignHCenter | Qt::AlignVCenter, "m\nu\nx");
}

MultiplexerBlock::MultiplexerBlock()
{

}


void MultiplexerBlock::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)
    QPainter* painter = new QPainter(this);
    drawBlockOnGivenPainter(painter, active, isSelected);
}

BlockModel MultiplexerBlock::getNewBlockModel(ComponentArea* parent, QPoint location, QColor color, bool positionLocked)
{
    BlockModel blockModel = BlockModel();
    blockModel.blockType = AbstractBlock::MULTIPLEXER;
    blockModel.location = location;
    blockModel.color = color;
    blockModel.positionLocked = positionLocked;

    blockModel.additionalInputSocketIds.append(parent->getNextSocketId());
    blockModel.additionalInputSocketIds.append(parent->getNextSocketId());

    blockModel.inputSocketIds.append(parent->getNextSocketId());
    blockModel.inputSocketIds.append(parent->getNextSocketId());
    blockModel.inputSocketIds.append(parent->getNextSocketId());
    blockModel.inputSocketIds.append(parent->getNextSocketId());

    blockModel.outputSocketIds.append(parent->getNextSocketId());

    return blockModel;
}
