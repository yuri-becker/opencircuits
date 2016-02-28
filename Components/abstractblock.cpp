/*
 *  abstractblock.cpp: Implementation of abstractblock.h
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

#include <Components/abstractblock.h>

#include "Components/abstractsocket.h"

#include "Components/Blocks/andgateblock.h"
#include "Components/Blocks/ledblock.h"
#include "Components/Blocks/nandgateblock.h"
#include "Components/Blocks/norgateblock.h"
#include "Components/Blocks/notgateblock.h"
#include "Components/Blocks/orgateblock.h"
#include "Components/Blocks/sourceblock.h"
#include "Components/Blocks/xnorgateblock.h"
#include "Components/Blocks/xorgateblock.h"
#include "Components/Blocks/labelblock.h"
#include "Components/Blocks/splitterblock.h"
#include "Components/Blocks/squarefunctiongeneratorblock.h"
#include "Components/Blocks/pushbuttonblock.h"
#include "Components/Blocks/switchblock.h"
#include "Components/Blocks/errorblock.h"
#include "Components/Blocks/srnorlatchblock.h"
#include "Components/Blocks/tflipflopblock.h"
#include "Components/Blocks/jkflipflopblock.h"
#include "Components/Blocks/multiplexerblock.h"
#include "Components/Blocks/demultiplexerblock.h"
#include "Components/Blocks/gatedsrnorlatchblock.h"
#include "Components/Blocks/gatedjkflipflopblock.h"

AbstractBlock::~AbstractBlock()
{
}

AbstractBlock::AbstractBlock(ComponentArea *parent, QPoint location, QSize size, QColor color, bool positionLocked) :
    ComponentWithColorContextMenu(parent, location, size, color)
{
    this->parent = parent;
    this->postionLocked = positionLocked;
    if(this->parent != 0) initContextMenu(); //Else it is a virtual instance
    initEvents();
    connect(this, SIGNAL(incomingProperyChange(QString,QString)), this, SLOT(changeProperty(QString,QString)));
}

AbstractBlock* AbstractBlock::getVirtualInstance(int blockType)
{
    if(blockType == ANDGATE) return AndGateBlock::getVirtualInstance();
    else if(blockType == LED) return LedBlock::getVirtualInstance();
    else if(blockType == NANDGATE) return NandGateBlock::getVirtualInstance();
    else if(blockType == NORGATE) return NorGateBlock::getVirtualInstance();
    else if(blockType == NOTGATE) return NotGateBlock::getVirtualInstance();
    else if(blockType == ORGATE) return OrGateBlock::getVirtualInstance();
    else if(blockType == SOURCE) return SourceBlock::getVirtualInstance();
    else if(blockType == XNORGATE) return XnorGateBlock::getVirtualInstance();
    else if(blockType == XORGATE) return XorGateBlock::getVirtualInstance();
    else if(blockType == LABEL) return LabelBlock::getVirtualInstance();
    else if(blockType == SPLITTER) return SplitterBlock::getVirtualInstance();
    else if(blockType == SQUAREFUNCTIONGENERATOR) return SquareFunctionGeneratorBlock::getVirtualInstance();
    else if(blockType == PUSHBUTTON) return PushButtonBlock::getVirtualInstance();
    else if(blockType == SWITCH) return SwitchBlock::getVirtualInstance();
    else if(blockType == ERRORDISPLAY) return ErrorBlock::getVirtualInstance();
    else if(blockType == SRNORLATCH) return SrNorLatchBlock::getVirtualInstance();
    else if(blockType == TFLIPFLOP) return TFlipFlopBlock::getVirtualInstance();
    else if(blockType == JKFLIPFLOP) return JKFlipFlopBlock::getVirtualInstance();
    else if(blockType == MULTIPLEXER) return MultiplexerBlock::getVirtualInstance();
    else if(blockType == DEMULTIPLEXER) return DemultiplexerBlock::getVirtualInstance();
    else if(blockType == GATEDSRNORLATCH) return GatedSrNorLatchBlock::getVirtualInstance();
    else if(blockType == GATEDJKFLIPFLOP) return GatedJKFlipFlopBlock::getVirtualInstance();
    else return ErrorBlock::getVirtualInstance();
}

AbstractBlock* AbstractBlock::getNewInstanceFromParams(ComponentArea *parent, BlockModel blockModel)
{
    return getVirtualInstance(blockModel.blockType)->createNewInstance(parent, blockModel);
}

AbstractBlock* AbstractBlock::getNewInstanceFromParams(ComponentArea *parent, int blockType)
{
    return getVirtualInstance(blockType)->createNewInstance(parent);
}

BlockModel AbstractBlock::toBlockModel()
{
    BlockModel blockModel = BlockModel();
    blockModel.blockType = blockType();
    blockModel.location = this->pos();
    blockModel.color = this->getColor();
    blockModel.positionLocked = this->postionLocked;

    Q_FOREACH(AbstractSocket* socket, this->findChildren<AbstractSocket*>())
    {
        if(qobject_cast<AdditionalInputSocket*>(socket) != 0)
        {
            blockModel.additionalInputSocketIds.append(socket->getSocketId());
        }
        else if(qobject_cast<InputSocket*>(socket) != 0)
        {
            blockModel.inputSocketIds.append(socket->getSocketId());
        }
        else if (qobject_cast<OutputSocket*>(socket) != 0)
        {
            blockModel.outputSocketIds.append(socket->getSocketId());
        }
    }
    blockModel.parameters = getParameters();

    return blockModel;
}

ComponentArea* AbstractBlock::getParentComponentArea()
{
    return parent;
}

void AbstractBlock::addSocketAndFixPosition(AbstractSocket *socket)
{
    //Adds socket to the ui, connects it and positions it properly.
    //Is called in every sockets's constructor


    InputSocket* inputSocket_cast = qobject_cast<InputSocket*>(socket);
    AdditionalInputSocket* additionalInputSocket_cast = qobject_cast<AdditionalInputSocket*>(socket);
    OutputSocket* outputSocket_cast = qobject_cast<OutputSocket*>(socket);

    if (additionalInputSocket_cast != 0)
    {
        this->additionalInputSockets.append(additionalInputSocket_cast);

        for(int i = 0; i < additionalInputSockets.size(); i++)
        {
            //AdditionalInputSockets are horizontally aligned
            int socketX = (int)((this->size().width() / (additionalInputSockets.size() +1) * (i+1)) - (additionalInputSockets.at(i)->size().width() /2));
            int socketY = this->size().height() -socket->size().height();
            additionalInputSockets.at(i)->move(socketX, socketY);
        }
    }
    else if(inputSocket_cast != 0)
    {
        this->inputSockets.append(inputSocket_cast);

        //Every socket has to be replaced in order to align them correctly
        for(int i = 0; i < inputSockets.size(); i++)
        {
            int socketY = (int)((this->size().height() / (inputSockets.size() +1) * (i+1)) - (inputSockets.at(i)->size().height() / 2) );
            inputSockets.at(i)->move(0, socketY);
        }
    }
    else if(outputSocket_cast != 0)
    {
        this->outputSockets.append(outputSocket_cast);

        //Every socket has to be replaced in order to align them correctly
        for(int i = 0; i < outputSockets.size(); i++)
        {
            int socketX = this->size().width() - socket->size().width();
            int socketY = (int)((this->size().height() / (outputSockets.size() +1) * (i+1)) - (outputSockets.at(i)->size().height() / 2));
            outputSockets.at(i)->move(socketX, socketY);
        }
    }

    connect(socket, SIGNAL(mousePressed(AbstractSocket*,QMouseEvent*)),
            parent, SLOT(childSocket_mousePressEvent(AbstractSocket*,QMouseEvent*)));
    connect(socket, SIGNAL(mouseReleased(AbstractSocket*,QMouseEvent*)),
            parent, SLOT(childSocket_mouseReleaseEvent(AbstractSocket*,QMouseEvent*)));

}

QList<InputSocket*> AbstractBlock::getInputSockets()
{
    return inputSockets;
}

QList<OutputSocket *> AbstractBlock::getOutputSockets()
{
    return outputSockets;
}

QList<AdditionalInputSocket*> AbstractBlock::getAdditionalInputSockets()
{
    return additionalInputSockets;
}

void AbstractBlock::remove()
{

    unselect();
    Q_FOREACH(AbstractSocket* socket, getInputSockets())
    {
        socket->remove();
    }

    Q_FOREACH(AbstractSocket* socket, getOutputSockets())
    {
        socket->remove();
    }

    Q_FOREACH(AbstractSocket* socket, getAdditionalInputSockets())
    {
        socket->remove();
    }

    Component::invalidate();
    this->parent->acceptBlockRemoval();
    this->close();
    this->deleteLater();
}

void AbstractBlock::select()
{
    isSelected = true;
    emit selected(this);
    emit requestRepaint();
}

void AbstractBlock::unselect()
{
    isSelected = false;
    emit unselected(this);
    emit requestRepaint();
}

void AbstractBlock::onMousePress(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        offset = event->pos();
        originalPos = this->pos();
        dragging = true;
    }
    afterMousePressed(event);
}

void AbstractBlock::initContextMenu()
{
    QList<QAction*> positioningActions;
    {
        QIcon icon;
        icon.addFile(":/images/Resources/GenericIcons/up-48.png", QSize(), QIcon::Normal, QIcon::Off);

        QAction* newAction = new QAction(icon, tr("Bring to Front"), 0);
        newAction->setIconVisibleInMenu(true);
        connect(newAction, SIGNAL(triggered()), this, SLOT(requestRise()));
        positioningActions.append(newAction);
    }
    {
        QIcon icon;
        icon.addFile(":/images/Resources/GenericIcons/lock-48.png", QSize(), QIcon::Normal, QIcon::Off);

        positionLockAction = new QAction(icon, tr("Lock Position"), 0);
        positionLockAction->setIconVisibleInMenu(true);
        positionLockAction->setCheckable(true);
        positionLockAction->setChecked(postionLocked);
        connect(positionLockAction, SIGNAL(triggered(bool)), this, SLOT(requestSetPositionLocked(bool)));
        positioningActions.append(positionLockAction);
    }
    contextMenu.insertActions(contextMenu.actions().at(0), positioningActions);
    contextMenu.insertSeparator(contextMenu.actions().at(positioningActions.count()));


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

void AbstractBlock::onMouseMove(QMouseEvent *event)
{
    if(!parent->simIsRunning() && !postionLocked && dragging)
    {
        QPoint oldPos = pos();
        QPoint newPos = QPoint();
        if(!parent->getMoveComponentsOnGrid())
        {
            newPos = mapToParent(event->pos() - offset);
        }
        else
        {
            int gridSpacing = parent->getGridSpacing();
            newPos = QPoint(gridSpacing * (int)round((mapToParent(event->pos() - offset).x() + gridSpacing /2) / gridSpacing) - size().width() /2,
                            gridSpacing * (int)round((mapToParent(event->pos() - offset).y() + gridSpacing /2) / gridSpacing) - size().height() /2) ;
        }
        move(newPos);
        emit dragged(this, event, newPos - oldPos);
    }
}

void AbstractBlock::onLeave()
{
    active = false;
    repaint();
}

void AbstractBlock::beforeMousePress(QMouseEvent *event)
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
        parent->discardCurrentSelection();
        select();
    }
}

void AbstractBlock::onMouseRelease(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        dragging = false;
        emit dragEnded(this);
    }
    afterMouseReleased(event);
}

void AbstractBlock::initSockets(BlockModel blockModel)
{
    //Only creates socket.
    //Socket calls AbstractBlock::addSocket() afterwards

    Q_FOREACH(QString inputSocketId, blockModel.inputSocketIds)
    {
        InputSocket* inputSocket = new InputSocket(this, inputSocketId);
        Q_UNUSED(inputSocket);
    }
    Q_FOREACH(QString outputSocketId, blockModel.outputSocketIds)
    {
        OutputSocket* outputSocket = new OutputSocket(this, outputSocketId);
        Q_UNUSED(outputSocket);
    }
    Q_FOREACH(QString additionalInputSocketId, blockModel.additionalInputSocketIds)
    {
        AdditionalInputSocket* additionInputSocket = new AdditionalInputSocket(this, additionalInputSocketId);
        Q_UNUSED(additionInputSocket);
    }
}

void AbstractBlock::resetOutputs()
{
    Q_FOREACH(OutputSocket* output, getOutputSockets())
    {
        output->changeState(AbstractSocket::NONE);
    }
}

void AbstractBlock::changeProperty(QString property, QString value)
{
    if(property == property_component_removal) this->remove();
    else if(property == property_block_positionLocked) setPositionLocked(value.toInt());
    else if(property == property_block_rise) this->raise();
}

void AbstractBlock::initEvents()
{
    if(parent != 0)
    {
        connect(this, SIGNAL(dragged(AbstractBlock*,QMouseEvent*,QPoint)), parent, SLOT(childBlock_dragged(AbstractBlock*,QMouseEvent*,QPoint)));
        connect(this, SIGNAL(dragEnded(AbstractBlock*)), parent, SLOT(childBlock_dragEnded(AbstractBlock*)));
        connect(this, SIGNAL(selected(AbstractBlock*)), parent, SLOT(childBlock_selected(AbstractBlock*)));
        connect(this, SIGNAL(unselected(AbstractBlock*)), parent, SLOT(childBlock_unselected(AbstractBlock*)));
        connect(parent, SIGNAL(simStarted()), this, SLOT(disableContextMenu()));
        connect(parent, SIGNAL(simStopped()), this, SLOT(enableContextMenu()));
        connect(parent, SIGNAL(simStarted()), this, SLOT(resetOutputs()));
        connect(parent, SIGNAL(simStarted()), this, SLOT(triggerSimStartedSignal()));
        connect(parent, SIGNAL(simStopped()), this, SLOT(triggerSimStoppedSignal()));
        connect(this, SIGNAL(requestPropertyChange(QString,QString)), parent, SLOT(passPropertyChangeToSelection(QString,QString)));

    }
}

void AbstractBlock::triggerSimStartedSignal()
{
    emit simStarted();
}

void AbstractBlock::triggerSimStoppedSignal()
{
    emit simStopped();
}

void AbstractBlock::onEnter()
{
    active = true;
    repaint();
}

void AbstractBlock::requestSetPositionLocked(bool positionLocked)
{
    emit requestPropertyChange(property_block_positionLocked, QString::number(positionLocked));
}

void AbstractBlock::requestRise()
{
    emit requestPropertyChange(property_block_rise, "1");
}

void AbstractBlock::setPositionLocked(bool positionLocked)
{
    this->postionLocked = positionLocked;
    positionLockAction->setChecked(positionLocked);
}
