/*
 * inputsocket.cpp: Implementation of inputsocket.h
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

#include "inputsocket.h"

#include "Components/Sockets/outputsocket.h"
#include "Components/abstractblock.h"

InputSocket::InputSocket(AbstractBlock *parent, QString socketId, bool addToParent) :
    AbstractSocket(parent, socketId)
{
    if(addToParent) parent->addSocketAndFixPosition(this);
}

AbstractSocket::State InputSocket::getState()
{
    if(connectedSocket == 0) return State::NONE;
    else return connectedSocket->getState();
}

void InputSocket::acceptConnection(OutputSocket *socket)
{
    connectedSocket = socket;
}

AbstractSocket::CanConnectWithResult InputSocket::canConnectWith(AbstractSocket *socket)
{
    if(isConnected())
    {
        return AbstractSocket::INPUT_OCCUPIED;
    }
    else if(qobject_cast<OutputSocket*>(socket) == 0)
    {
        return AbstractSocket::SOCKETTYPE_EQUIVALENT;
    }
    else
    {
        return AbstractSocket::OKAY;
    }
}

bool InputSocket::isConnected()
{
    return connectedSocket != 0;
}

void InputSocket::remove()
{
    if(connectedSocket != 0)
    {
        parent->getParentComponentArea()->removeSocketConnection(this, connectedSocket);
    }
    close();
    socketId ="";
}

void InputSocket::removeConnection(OutputSocket *socket)
{
    if(connectedSocket == socket)
    {
        socket->acceptConnectionRemoval(this);
        connectedSocket = 0;
    }
}
