/*
 * abstractsocket.cpp: Implementation orf abstractsocket.h
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

#include <Components/abstractsocket.h>

#include <QToolTip>
#include "Components/abstractblock.h"

AbstractSocket::AbstractSocket(AbstractBlock *parent, QString socketId) :
    Component(parent, QPoint(0,0), QSize(8,8), parent->getColor())
{
    this->parent = parent;
    this->socketId = socketId;
    parent->getParentComponentArea()->registerSocketId(socketId);

    connect(this, SIGNAL(destroyed(QObject*)), this, SLOT(invalidate()));
    connect(parent, SIGNAL(simStarted()), this, SLOT(activeStateToolTip()));
    connect(parent, SIGNAL(simStopped()), this, SLOT(deactivateStateToolTip()));
}

void AbstractSocket::deactivateStateToolTip()
{
    stateToolTipActivated = false;
}

void AbstractSocket::activeStateToolTip()
{
    stateToolTipActivated = true;
}

QString AbstractSocket::getSocketId()
{
    return this->socketId;
}

AbstractSocket::State AbstractSocket::stateFromBool(bool value)
{
    if(!value) return State::LOW;
    if(value) return State::HIGH;
    return State::NONE;
}

bool AbstractSocket::stateToBool(AbstractSocket::State state)
{
    if(state == State::HIGH) return true;
    return false;
}

AbstractBlock* AbstractSocket::getParent()
{
    return this->parent;
}

void AbstractSocket::onEnter()
{
    active = true;
    repaint();
}

void AbstractSocket::onMouseMove(QMouseEvent *event)
{
    showTooltip(event->pos());
}

void AbstractSocket::onLeave()
{
    active = false;
    repaint();
}

void AbstractSocket::onMousePress(QMouseEvent *event)
{
    emit mousePressed(this, event);
}

void AbstractSocket::onMouseRelease(QMouseEvent *event)
{
    emit mouseReleased(this, event);
}

void AbstractSocket::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter* painter = new QPainter(this);
    painter->eraseRect(QRect(QPoint(0,0), QPoint(this->size().width(), this->size().height())));
    if(this->active)
    {
        painter->setPen(QPen(Qt::lightGray, 4, Qt::SolidLine, Qt::SquareCap));
        painter->drawLine(0, this->size().height() /2, this->size().width(), this->size().height() /2);
    }
    painter->setPen(QPen(this->getColor(), 1, Qt::SolidLine,Qt::SquareCap));
    painter->drawLine(0, this->size().height() /2, this->size().width(), this->size().height() /2);
}

void AbstractSocket::showTooltip(QPoint pos)
{
    if(stateToolTipActivated)
    {
        QString tooltipText = "UNKNOWN";
        if (getState() == NONE) tooltipText = "NONE";
        else if (getState() == LOW) tooltipText = "LOW";
        else if (getState() == HIGH) tooltipText = "HIGH";

        QToolTip::showText(mapToGlobal(pos), tooltipText, this);
    }
}

void AbstractSocket::invalidate()
{
    socketId = "";
    Component::invalidate();
}
