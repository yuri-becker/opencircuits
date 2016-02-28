/*
 * addtionalinputsocket.cpp: Implementation of additionalinputsocket.h
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

#include "additionalinputsocket.h"
#include "Components/abstractblock.h"

AdditionalInputSocket::AdditionalInputSocket(AbstractBlock* parent, QString socketId) : InputSocket(parent, socketId, false)
{
    parent->addSocketAndFixPosition(this);
}

void AdditionalInputSocket::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)

    QPainter* painter = new QPainter(this);
    painter->eraseRect(QRect(QPoint(0,0), QPoint(this->size().width(), this->size().height())));
    if(this->active)
    {
        painter->setPen(QPen(Qt::lightGray, 4, Qt::SolidLine, Qt::SquareCap));
        painter->drawLine(this->size().width() /2, 0, this->size().width() /2, this->size().height());
    }
    painter->setPen(QPen(this->getColor(), 1, Qt::SolidLine,Qt::SquareCap));
    painter->drawLine(this->size().width() /2, 0, this->size().width() /2, this->size().height());

}

