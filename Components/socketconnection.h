/*
 * socketconnection.h: Displays a connection between two sockets in the ComponentArea
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

#ifndef SOCKETCONNECTION_H
#define SOCKETCONNECTION_H

#include <QObject>
#include <QWidget>

class AbstractSocket;
class InputSocket;
class OutputSocket;

#include "Widgets/componentarea.h"
class ComponentArea;
#include "Components/componentwithcolorcontextmenu.h"
#include "Types/socketconnectionmodel.h"

class SocketConnection : public ComponentWithColorContextMenu
{

    Q_OBJECT

    public:
        explicit SocketConnection(ComponentArea* parent, OutputSocket* outputSocket, InputSocket* inputSocket, QColor color = Qt::black);
        static SocketConnection* fromUnspecifiedSockets(ComponentArea *parent, AbstractSocket* unspecifiedA, AbstractSocket* unspecifiedB, QColor color = Qt::black);

        OutputSocket* getOutputSocket();
        InputSocket* getInputSocket();
        void refresh();
        bool isInTriggerRects(QPoint globalPos);
        SocketConnectionModel toSocketConnectionModel();

    signals:
        void selected(SocketConnection* sender);
        void unselected(SocketConnection* sender);

    public slots:
        void remove();
        void select();
        void unselect();

    private:
        ComponentArea* parent;
        OutputSocket* outputSocket;
        InputSocket* inputSocket;
        bool socketDestroyed = false;
        QVector<QRect> triggerRects; //Local rectangles in which the component reacts to mouse
        bool isSelected = false;

        void initContextMenu();
        void paintEvent(QPaintEvent *event);

        QPoint calculatePosition(AbstractSocket* a, AbstractSocket* b, QWidget* parent);
        QSize calculateSize(AbstractSocket* a, AbstractSocket* b);
        QVector<QLine> calculateConnectionLines();
        void updateTriggerRects(QVector<QLine> lines);

        void onEnter();
        void onMouseMove(QMouseEvent *event);
        void onLeave();
        void beforeMousePress(QMouseEvent *event);
        void onMousePress(QMouseEvent *event) {Q_UNUSED(event)}
        void onMouseRelease(QMouseEvent *event) {Q_UNUSED(event)}

        void initEvents();

    private slots:
        void changeProperty(QString property, QString value);
        void catchSocketDestroyed();
};

#endif // SOCKETCONNECTION_H
