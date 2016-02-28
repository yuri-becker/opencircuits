/*
 *  abstractsocket.h: Provides general functionality for Sockets.
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

#ifndef SOCKET_H
#define SOCKET_H

#include <QString>
#include <QWidget>
#include <QColor>
#include <QPainter>

#include "Components/component.h"
class AbstractBlock;

class AbstractSocket : public Component
{

    Q_OBJECT

    public:
        enum CanConnectWithResult {OKAY, SOCKETTYPE_EQUIVALENT, INPUT_OCCUPIED, CONNECTION_EXISTING};
        enum State {NONE, HIGH, LOW};

        QString getSocketId();
        AbstractBlock* getParent();
        virtual State getState() = 0;
        virtual QPoint socketConnectionJoint() = 0;

        static State stateFromBool(bool value);
        static bool stateToBool(State state);

    public slots:
        virtual CanConnectWithResult canConnectWith(AbstractSocket* socket) = 0;
        void invalidate();
        virtual void remove() = 0;

    signals:
        void mousePressed(AbstractSocket* sender, QMouseEvent* event);
        void mouseReleased(AbstractSocket* sender, QMouseEvent* event);

    protected:
        AbstractSocket(AbstractBlock *parent, QString socketId);
        AbstractBlock* parent;
        QString socketId;

    private slots:
        void deactivateStateToolTip();
        void activeStateToolTip();

    private:
        bool stateToolTipActivated = false;

        void onEnter();
        void onMouseMove(QMouseEvent* event);
        void onLeave();
        void beforeMousePress(QMouseEvent *event) { Q_UNUSED(event); }
        void onMousePress(QMouseEvent *event);
        void onMouseRelease(QMouseEvent *event);
        void paintEvent(QPaintEvent *event);

        void showTooltip(QPoint pos);

};

#endif // SOCKET_H
