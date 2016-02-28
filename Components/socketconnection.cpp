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

#include "socketconnection.h"

#include "Components/Sockets/outputsocket.h"
#include "Components/Sockets/inputsocket.h"
#include "Components/abstractblock.h"
#include "Utils/geometryutil.h"
#include <cmath>

#define BLOCK_SPACING 10
#define TRIGGERPOLYGON_RADIUS 10

SocketConnection::SocketConnection(ComponentArea *parent, OutputSocket *outputSocket, InputSocket *inputSocket, QColor color) :
    ComponentWithColorContextMenu(parent, calculatePosition(outputSocket, inputSocket, parent), calculateSize(outputSocket, inputSocket), color )
{
    this->parent = parent;
    initContextMenu();
    this->outputSocket = outputSocket;
    outputSocket->parentWidget()->raise();
    this->inputSocket = inputSocket;
    inputSocket->parentWidget()->raise();
    outputSocket->establishAdditionalConnection(inputSocket);
    setColor(color);
    initEvents();
    connect(this, SIGNAL(incomingProperyChange(QString,QString)), this, SLOT(changeProperty(QString,QString)));
}

void SocketConnection::initEvents()
{
    connect(inputSocket, SIGNAL(destroyed(QObject*)), this, SLOT(catchSocketDestroyed()));
    connect(outputSocket, SIGNAL(destroyed(QObject*)), this, SLOT(catchSocketDestroyed()));
    connect(parent, SIGNAL(simStarted()), this, SLOT(disableContextMenu()));
    connect(parent, SIGNAL(simStopped()), this, SLOT(enableContextMenu()));
    connect(this, SIGNAL(selected(SocketConnection*)), parent, SLOT(childSocketConnection_selected(SocketConnection*)));
    connect(this, SIGNAL(unselected(SocketConnection*)), parent, SLOT(childSocketConnection_unselected(SocketConnection*)));
    connect(this, SIGNAL(requestPropertyChange(QString,QString)), parent, SLOT(passPropertyChangeToSelection(QString,QString)));
}

SocketConnection* SocketConnection::fromUnspecifiedSockets(ComponentArea *parent, AbstractSocket *unspecifiedA, AbstractSocket *unspecifiedB, QColor color)
{
    OutputSocket* a_outputCast = qobject_cast<OutputSocket*>(unspecifiedA);
    InputSocket* a_InputCast = qobject_cast<InputSocket*>(unspecifiedA);
    OutputSocket* b_outputCast = qobject_cast<OutputSocket*>(unspecifiedB);
    InputSocket* b_inputCast = qobject_cast<InputSocket*>(unspecifiedB);
    if(a_outputCast != 0 && b_inputCast != 0)
    {
        return new SocketConnection(parent, a_outputCast, b_inputCast, color);
    }
    else
    {
        //If there was a NullPointer here, the method is called incorrectly, since the user cannot cause to sockets of the same type.
        //So an additional check is unnecessary
        return new SocketConnection(parent, b_outputCast, a_InputCast, color);
    }
}

OutputSocket* SocketConnection::getOutputSocket()
{
    return outputSocket;
}

InputSocket* SocketConnection::getInputSocket()
{
    return inputSocket;
}

void SocketConnection::refresh()
{
    move(calculatePosition(outputSocket, inputSocket, parent));
    setFixedSize(calculateSize(outputSocket, inputSocket));
    repaint();
}

bool SocketConnection::isInTriggerRects(QPoint globalPos)
{
    return GeometryUtil::rectsContain(triggerRects, mapFromGlobal(globalPos));
}

SocketConnectionModel SocketConnection::toSocketConnectionModel()
{
    SocketConnectionModel socketConnectionModel = SocketConnectionModel();
    socketConnectionModel.socketAId = inputSocket->getSocketId();
    socketConnectionModel.socketBId = outputSocket->getSocketId();
    socketConnectionModel.color = getColor();
    return socketConnectionModel;
}

void SocketConnection::remove()
{
    unselect();
    Component::invalidate();
    inputSocket->removeConnection(outputSocket);
    //The sender destroys itself with its block, so changing the inputSocket's value is not needed
    //and only may cause multithreading-issues at DelayedRespondingBlocks.
    parent->acceptSocketConnectionRemoval();
    this->deleteLater();
}

void SocketConnection::select()
{
    isSelected = true;
    emit selected(this);
    emit requestRepaint();
}

void SocketConnection::unselect()
{
    isSelected = false;
    emit unselected(this);
    emit requestRepaint();
}

void SocketConnection::changeProperty(QString property, QString value)
{
    if(property == property_component_removal) this->remove();
}

QPoint SocketConnection::calculatePosition(AbstractSocket *a, AbstractSocket *b, QWidget *parent)
{
    QPoint point;
    QPoint aPos_global = a->parentWidget()->mapToGlobal(a->pos());
    QPoint bPos_global = b->parentWidget()->mapToGlobal(b->pos());

    if(aPos_global.x() <= bPos_global.x())    point.setX(aPos_global.x() - BLOCK_SPACING);
    else                        point.setX(bPos_global.x() - BLOCK_SPACING);

    if(aPos_global.y() <= bPos_global.y())    point.setY(aPos_global.y() - BLOCK_SPACING);
    else                        point.setY(bPos_global.y() - BLOCK_SPACING);

    return parent->mapFromGlobal(point);
}

QSize SocketConnection::calculateSize(AbstractSocket *a, AbstractSocket *b)
{
    QPoint aPos_global = a->parentWidget()->mapToGlobal(a->pos());
    QPoint bPos_global = b->parentWidget()->mapToGlobal(b->pos());

    int socketsDeltaX = abs(aPos_global.x() - bPos_global.x());
    int socketsDeltaY = abs(aPos_global.y() - bPos_global.y());

    QSize size;
    size.setWidth(socketsDeltaX + BLOCK_SPACING *2);
    size.setHeight(socketsDeltaY + BLOCK_SPACING *2);

    return size;
}

QVector<QLine> SocketConnection::calculateConnectionLines()
{
            //Map socket-positions
            QPoint outputPos = this->mapFromGlobal(outputSocket->mapToGlobal(outputSocket->socketConnectionJoint()));

            QPoint inputPos = this->mapFromGlobal(inputSocket->mapToGlobal(inputSocket->socketConnectionJoint()));


            //Determine line
            int horizontalCenter =  this->width() /2;

            QVector<QLine> lines;
            if(outputPos.x() < inputPos.x()) // OutputSocket is left and InputSocket is right (default case)
            {
                lines.append(QLine(
                                 outputPos.x(), outputPos.y(),
                                 horizontalCenter, outputPos.y()
                                 ));
                lines.append(QLine(
                                 horizontalCenter, outputPos.y(),
                                 horizontalCenter, inputPos.y()
                                 ));
                lines.append(QLine(
                                 horizontalCenter, inputPos.y(),
                                 inputPos.x(), inputPos.y())
                             );
            }
            else // Line needs to be drawn "around" blocks
            {
                int outputYWithSpacing;
                int inputYWithSpacing;
                if(outputPos.y() < inputPos.y())
                {
                    outputYWithSpacing = outputPos.y() + (outputSocket->getParent()->height() - outputSocket->y()) - outputSocket->height() + BLOCK_SPACING;
                    inputYWithSpacing = inputPos.y() - inputSocket->y() - BLOCK_SPACING;
                }
                else
                {
                    outputYWithSpacing = outputPos.y() - outputSocket->y() - BLOCK_SPACING;
                    inputYWithSpacing =  inputPos.y() + (inputSocket->getParent()->height() - inputSocket->y()) - inputSocket->height() + BLOCK_SPACING;
                }

                lines.append(QLine(
                                 outputPos.x(), outputPos.y(),
                                 outputPos.x(), outputYWithSpacing
                                 ));
                lines.append(QLine(
                                 outputPos.x(), outputYWithSpacing,
                                 horizontalCenter, outputYWithSpacing
                                 ));
                lines.append(QLine(
                                 horizontalCenter, outputYWithSpacing,
                                 horizontalCenter, inputYWithSpacing
                                 ));
                lines.append(QLine(
                                 horizontalCenter, inputYWithSpacing,
                                 inputPos.x(), inputYWithSpacing
                                 ));
                lines.append(QLine(
                                 inputPos.x(), inputYWithSpacing,
                                 inputPos.x(), inputPos.y()
                                 ));
            }

            return lines;
}

void SocketConnection::updateTriggerRects(QVector<QLine> lines)
{
    QVector<QRect> triggerRects;
    Q_FOREACH(QLine line, lines)
    {
        QRect rekt;
        rekt.setTopLeft(QPoint(
                    std::min<int>(line.x1(), line.x2()) - TRIGGERPOLYGON_RADIUS,
                    std::min<int>(line.y1(),line.y2()) - TRIGGERPOLYGON_RADIUS
                    ));
        rekt.setBottomRight(QPoint(
                    std::max<int>(line.x1(), line.x2()) + TRIGGERPOLYGON_RADIUS,
                    std::max<int>(line.y1(), line.y2()) + TRIGGERPOLYGON_RADIUS
                    ));
        triggerRects.append(rekt);
    }
    this->triggerRects = triggerRects;
}

void SocketConnection::onEnter()
{
    //active gets set in onMouseMove
}

void SocketConnection::onMouseMove(QMouseEvent *event)
{
    if(GeometryUtil::rectsContain(triggerRects, event->pos()))
    {
        active = true;
        repaint();
    }
    else
    {
        active = false;
        repaint();
    }
}

void SocketConnection::onLeave()
{
    active = false;
    repaint();
}

void SocketConnection::beforeMousePress(QMouseEvent *event)
{
    bool ctrlPressed = event->modifiers() & Qt::ControlModifier;

    if(!isSelected && ctrlPressed)
    {
        select(); //Block should be added to current seleciton
    }
    else if(isSelected && ctrlPressed)
    {
        unselect(); //Block should be removed from current selection
    }
    else if(!isSelected && !ctrlPressed)
    {
        //User has not pressed CTRL, so the current selection should be discarded and only this block should be selected
        parent-> discardCurrentSelection();
        select();
    }
}

void SocketConnection::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    if(!socketDestroyed)
    {
        QPainter* painter = new QPainter(this);
        painter->eraseRect(QRect(QPoint(0,0), QPoint(this->size().width(), this->size().height())));

        QVector<QLine> lines = calculateConnectionLines();

        //Determine TriggerPolygon
        updateTriggerRects(lines);

        //Draw
        if(isSelected)
        {
            painter->setPen(QPen(Qt::gray, 4, Qt::SolidLine, Qt::SquareCap));
            painter->drawLines(lines);
        }
        else if(active)
        {
            painter->setPen(QPen(Qt::lightGray, 4, Qt::SolidLine, Qt::SquareCap));
            painter->drawLines(lines);
        }

        painter->setPen(QPen(getColor(), 1, Qt::SolidLine, Qt::SquareCap));
        painter->drawLines(lines);
    }

}

void SocketConnection::initContextMenu()
{
    QList<QAction*> removeActions;
    {
        QIcon icon;
        icon.addFile(":/images/Resources/GenericIcons/delete-48.png", QSize(), QIcon::Normal, QIcon::Off);

        QAction* newAction = new QAction(icon, tr("Remove"), 0);
        newAction->setIconVisibleInMenu(true);
        connect(newAction, SIGNAL(triggered()), this, SLOT(requestRemoval()));
        removeActions.append(newAction);
    }
    contextMenu.insertActions(contextMenu.actions().at(0), removeActions);
    contextMenu.insertSeparator(contextMenu.actions().at(removeActions.count()));

    QList<QAction*> cutCopyActions;
    {
        QIcon icon;
        icon.addFile(":/images/Resources/GenericIcons/Cut-52.png", QSize(), QIcon::Normal, QIcon::Off);

        QAction* newAction = new QAction(icon, tr("Cut"), 0);
        newAction->setIconVisibleInMenu(true);
        connect(newAction, SIGNAL(triggered()), parent, SLOT(cutSelectionToClipboard()));
        cutCopyActions.append(newAction);
    }
    {
        QIcon icon;
        icon.addFile(":/images/Resources/GenericIcons/copy-48.png", QSize(), QIcon::Normal, QIcon::Off);

        QAction* newAction = new QAction(icon, tr("Copy"), 0);
        newAction->setIconVisibleInMenu(true);
        connect(newAction, SIGNAL(triggered()), parent, SLOT(copySelectionToClipboard()));
        cutCopyActions.append(newAction);
    }
    contextMenu.insertActions(contextMenu.actions().at(0), cutCopyActions);
    contextMenu.insertSeparator(contextMenu.actions().at(cutCopyActions.count()));


}

void SocketConnection::catchSocketDestroyed()
{
    socketDestroyed = true;
}
