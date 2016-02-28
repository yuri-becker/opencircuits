/*
 * outputsocket.cpp: Implementation of outputsocket.h
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

#include "outputsocket.h"
#include "Components/Sockets/inputsocket.h"
#include "Components/abstractblock.h"


OutputSocket::OutputSocket(AbstractBlock *parent, QString socketId) :
    AbstractSocket(parent, socketId)
{
    parent->addSocketAndFixPosition(this);
}

AbstractSocket::State OutputSocket::getState()
{
    return state;
}

void OutputSocket::changeState(State state)
{
    this->state = state;
}

void OutputSocket::changeToHigh()
{
    changeState(AbstractSocket::HIGH);
}

void OutputSocket::changeToLow()
{
    changeState(AbstractSocket::LOW);
}

void OutputSocket::establishAdditionalConnection(InputSocket *socket)
{
    if(canConnectWith(socket) == OKAY && socket->canConnectWith(this) == OKAY)
    {
        connectedSockets.append(socket);
        socket->acceptConnection(this);
    }
}

AbstractSocket::CanConnectWithResult OutputSocket::canConnectWith(AbstractSocket *socket)
{
    InputSocket* inputSocket_cast = qobject_cast<InputSocket*>(socket);
    if(inputSocket_cast == 0)
    {
        return AbstractSocket::SOCKETTYPE_EQUIVALENT;
    }
    else if(inputSocket_cast != 0 && connectedSockets.contains(inputSocket_cast))
    {
        return AbstractSocket::CONNECTION_EXISTING;
    }
    else
    {
        return AbstractSocket::OKAY;
    }
}

void OutputSocket::remove()
{
    Q_FOREACH(InputSocket* connectedSocket, connectedSockets)
    {
        connectedSocket->removeConnection(this);
        parent->getParentComponentArea()->removeSocketConnection(this, connectedSocket);
    }
    close();
    socketId = "";
}

void OutputSocket::acceptConnectionRemoval(InputSocket *socket)
{
    //Does NOT remove the opposite connection, only disconnects itself
    connectedSockets.removeOne(socket);
}
