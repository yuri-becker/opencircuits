/*
 * outputsocket.h: Receives CurrentState from its parent, passes it to the connected InputSocket.
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

#ifndef OUTPUTSOCKET_H
#define OUTPUTSOCKET_H

#include "Components/abstractsocket.h"
class InputSocket;

class OutputSocket : public AbstractSocket
{
    Q_OBJECT

    public:
        OutputSocket(AbstractBlock* parent, QString socketId);
        State getState();
        QPoint socketConnectionJoint() { return QPoint(size().width(), size().height() /2); }

    public slots:
        void establishAdditionalConnection(InputSocket* socket);
        CanConnectWithResult canConnectWith(AbstractSocket* socket);
        void acceptConnectionRemoval(InputSocket* socket);

        void changeState(State state);
        void changeToHigh();
        void changeToLow();
        void remove();

    private:
        QList<InputSocket*> connectedSockets = QList<InputSocket*>();
        State state = NONE;
};

#endif // OUTPUTSOCKET_H
