/*
 * sourceblock.cpp: Implementation of sourceblock.h
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

#include "sourceblock.h"

#include "Components/Sockets/outputsocket.h"

SourceBlock::SourceBlock(ComponentArea *parent, QPoint location, QColor color, bool positionLocked) :
    SourceBlock(parent, getNewBlockModel(parent, location, color, positionLocked))
{
}

SourceBlock::SourceBlock(ComponentArea *parent, BlockModel blockModel) :
    AbstractInstantRespondingBlock(parent, blockModel.location, defaultSize(), blockModel.color, blockModel.positionLocked)
{
    initSockets(blockModel);
    initContextMenu();
    connect(this, SIGNAL(incomingProperyChange(QString,QString)), this, SLOT(changeProperty(QString,QString)));
    this->produceOutputValues();
    setOutputHigh(blockModel.parameters.toInt());
}

SourceBlock::SourceBlock()
{

}

void SourceBlock::drawBlockOnGivenPainter(QPainter *painter, bool paintHoverOutlines, bool selected)
{
    painter->eraseRect(QRect(QPoint(0,0), QPoint(defaultSize().width(), defaultSize().height())));
    painter->fillRect(1, 1, 30, 18, Qt::white);

    if(selected) painter->setPen(QPen(Qt::gray, 3, Qt::SolidLine, Qt::SquareCap));
    else if(paintHoverOutlines) painter->setPen(QPen(Qt::lightGray, 3, Qt::SolidLine, Qt::SquareCap));
    else  painter->setPen(QPen(Qt::transparent, 0, Qt::SolidLine, Qt::SquareCap));

    painter->drawRect(1, 1, 30, 18);

    painter->setPen(QPen(this->getColor(), 1, Qt::SolidLine, Qt::SquareCap));

    painter->drawRect(1, 1, 30, 18);
    painter->drawText(3, 3, 24, 12, Qt::AlignCenter, QString("SRC"));
}

void SourceBlock::changeProperty(QString property, QString value)
{
    if(property == property_source_outputHigh) setOutputHigh(value.toInt());
}

void SourceBlock::produceOutputValues()
{
    getOutputSockets().at(0)->changeState(output);
}

QString SourceBlock::getParameters()
{
    if(getOutputSockets().at(0)->getState() == AbstractSocket::LOW)
        return QString::number(0);
    else
        return QString::number(1);
}

void SourceBlock::requestSetOutputHigh(bool value)
{
    emit requestPropertyChange(property_source_outputHigh, QString::number(value));
}

void SourceBlock::setOutputHigh(bool value)
{
    outputHighAction->setChecked(value);
    if(value == 0)
       output = AbstractSocket::LOW;
    if(value == 1)
        output = AbstractSocket::HIGH;
}

void SourceBlock::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter* painter = new QPainter(this);
    drawBlockOnGivenPainter(painter, this->active, this->isSelected);
}

void SourceBlock::initContextMenu()
{
    {
        outputHighAction = new QAction(tr("Output HIGH"), 0);
        outputHighAction->setCheckable(true);
        connect(outputHighAction, SIGNAL(toggled(bool)), this, SLOT(requestSetOutputHigh(bool)));
        contextMenu.addAction(outputHighAction);
    }
}


BlockModel SourceBlock::getNewBlockModel(ComponentArea *parent, QPoint location, QColor color, bool positionLocked)
{
    BlockModel blockModel = BlockModel();
    blockModel.blockType = AbstractBlock::SOURCE;
    blockModel.location = location;
    blockModel.color = color;
    blockModel.positionLocked = positionLocked;
    blockModel.outputSocketIds.append(parent->getNextSocketId());
    blockModel.parameters = QString::number(1);
    return blockModel;
}
