/*
 * inputsocket.h: Receives signal from OutputSocket, triggers an outputs-update of its parent.
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

#ifndef INPUTSOCKET_H
#define INPUTSOCKET_H

#include "Components/abstractsocket.h"
class OutputSocket;

class InputSocket : public AbstractSocket
{
    Q_OBJECT

    public:
        InputSocket(AbstractBlock* parent, QString socketId, bool addToParent = true);
        State getState();
        QPoint socketConnectionJoint() { return QPoint(0, size().height() /2); }

    public slots:
        void acceptConnection(OutputSocket* socket);
        void removeConnection(OutputSocket* socket);
        CanConnectWithResult canConnectWith(AbstractSocket* socket);
        bool isConnected();

        void remove();

    private:
        OutputSocket* connectedSocket = 0;
};

#endif // INPUTSOCKET_H
