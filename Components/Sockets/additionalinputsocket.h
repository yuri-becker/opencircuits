/*
 * addtionalinputsocket.h: Input socket which is a vertical line (instead of horizontal) and gets added at the bottom of a block.
 * Used for example as selection inputs at multiplexers.
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

#ifndef ADDITIONALINPUTSOCKET_H
#define ADDITIONALINPUTSOCKET_H

#include "Components/Sockets/inputsocket.h"

class AdditionalInputSocket : public InputSocket
{
        Q_OBJECT
    public:
        AdditionalInputSocket(AbstractBlock* parent, QString socketId);
        QPoint socketConnectionJoint() { return QPoint(size().width() /2, size().height()); }

    private:
        void paintEvent(QPaintEvent *event);
};

#endif // ADDITIONALINPUTSOCKET_H
