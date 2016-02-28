/*
 *  componentarea.cpp: Implementation of componentarea.h
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

#include "componentarea.h"

#include "Operators/circuitfileoperator.h"
#include "Utils/widgetutil.h"
#include <QMimeData>
#include <QSharedPointer>
#include <QStandardPaths>
#include <QDateTime>
#include <QClipboard>
#include <QMenu>
#include <QShortcut>

#include "Components/abstractsocket.h"
#include "Components/socketconnection.h"
#include "Components/abstractblock.h"
#include "Widgets/socketconnectionpreview.h"
#include "Components/component.h"

#include "Components/Sockets/inputsocket.h"
#include "Components/Sockets/outputsocket.h"
#include "Widgets/scrollareawithedgescrollingandexpanding.h"


ComponentArea::ComponentArea(QWidget* parent) : QWidget(parent)
{
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::white);
    setPalette(palette);
    tmpDir = QStandardPaths::writableLocation(QStandardPaths::TempLocation);

    simulationTimer->setSingleShot(false);
    simulationTimer->setInterval(simulationTimer_Interval);
    connect(simulationTimer, SIGNAL(timeout()), this, SLOT(updateEveryBlock()));

    clipboard = QApplication::clipboard();
    connect(clipboard, SIGNAL(dataChanged()), this, SLOT(updatePasteContextMenuFromClipboardChange()));

    setMouseTracking(true);
    setAcceptDrops(true);
    initContextMenu();
    initShortcuts();
}

SocketConnection *ComponentArea::connectSockets(AbstractSocket *a, AbstractSocket *b, QColor connectionColor = Qt::black)
{
    AbstractSocket::CanConnectWithResult canConnectWithResultA = a->canConnectWith(b);
    AbstractSocket::CanConnectWithResult canConnectWithResultB= b->canConnectWith(a);
    QString statusBarMessage = "";

    SocketConnection* createdSocketConnection = 0;

    if(canConnectWithResultA == AbstractSocket::CONNECTION_EXISTING || canConnectWithResultB == AbstractSocket::CONNECTION_EXISTING)
    {
        statusBarMessage = tr("The connection does already exist.");
    }
    else if(canConnectWithResultA == AbstractSocket::SOCKETTYPE_EQUIVALENT)
    {
        statusBarMessage = tr("Sockets of the same type cannot be connected.");
    }
    else if(canConnectWithResultA == AbstractSocket::INPUT_OCCUPIED || canConnectWithResultB == AbstractSocket::INPUT_OCCUPIED)
    {
        statusBarMessage = tr("Inputs cannot have more than one connection.");
    }
    else
    {
        createdSocketConnection = SocketConnection::fromUnspecifiedSockets(this, a, b, connectionColor);
        createdSocketConnection->show();
        emit changed();
        emit socketConnectionsCountChanged(++socketConnectionsCount);
    }
    emit displayMessageOnStatusbar(statusBarMessage, Qt::red, 4000);
    return createdSocketConnection;
}

bool ComponentArea::removeSocketConnection(AbstractSocket *a, AbstractSocket *b)
{
    Q_FOREACH(SocketConnection* socketConnection, findChildren<SocketConnection*>())
    {
        if(     (socketConnection->getOutputSocket() == qobject_cast<OutputSocket*>(a) && socketConnection->getInputSocket() == qobject_cast<InputSocket*>(b))  ||
                (socketConnection->getOutputSocket() == qobject_cast<OutputSocket*>(b) && socketConnection->getInputSocket() == qobject_cast<InputSocket*>(a))     )
        {
            socketConnection->remove();
            return true;
        }
    }
    return false;
}

void ComponentArea::childSocket_mousePressEvent(AbstractSocket *sender, QMouseEvent *event)
{
    if(!simIsRunning() && event->button() == Qt::LeftButton)
    {
        if(pressedSocket_first == 0)
        {
            this->pressedSocket_first = sender;
            connectionPreview = QSharedPointer<SocketConnectionPreview>(new SocketConnectionPreview(this));
            connectionPreview->show();
            connectionPreview->raise();
        }
        else if (pressedSocket_second == 0)
        {
            this->pressedSocket_second = sender;
        }
    }
}

void ComponentArea::childSocket_mouseReleaseEvent(AbstractSocket *sender, QMouseEvent *event)
{
    if(!simIsRunning() && event->button() == Qt::LeftButton)
    {
        if(sender != 0 && pressedSocket_first != 0 && pressedSocket_second != 0)
        {
            connectSockets(pressedSocket_first, pressedSocket_second, Qt::black);
            if(!connectionPreview.isNull()) connectionPreview->close();
            pressedSocket_first = 0;
            pressedSocket_second = 0;
            connectionPreview = QSharedPointer<SocketConnectionPreview>();
        }
    }
}

void ComponentArea::childBlock_dragged(AbstractBlock *sender, QMouseEvent* event, QPoint deltaPos)
{
    refreshSocketConnectionsOfBlock(sender);

    if(!selectedBlocks.isEmpty())
    {
        Q_FOREACH(AbstractBlock* selectedBlock, selectedBlocks)
        {
            if(selectedBlock != sender)
            {
                selectedBlock->move(selectedBlock->pos() + deltaPos);
                refreshSocketConnectionsOfBlock(selectedBlock);
            }
        }
    }

    emit blockMoved(this, mapFromGlobal(sender->mapToGlobal(event->pos())));
}

void ComponentArea::childBlock_dragEnded(AbstractBlock *sender)
{
    if((sender->pos().x() < 0 - sender->size().width() + 12) || (sender->pos().y() < 0 - sender->size().height() + 12))
    {
        sender->remove();
    }
    emit changed();
}

void ComponentArea::childBlock_selected(AbstractBlock *sender)
{
    selectedBlocks.insert(sender);
    refreshSocketConnectionSelections();
}

void ComponentArea::childBlock_unselected(AbstractBlock *sender)
{
    selectedBlocks.remove(sender);
    refreshSocketConnectionSelections();
}

void ComponentArea::childSocketConnection_selected(SocketConnection *sender)
{
    selectedSocketConnections.insert(sender);
}

void ComponentArea::childSocketConnection_unselected(SocketConnection *sender)
{
    selectedSocketConnections.remove(sender);
}

void ComponentArea::refreshSocketConnectionsOfBlock(AbstractBlock *block)
{
    Q_FOREACH(SocketConnection* socketConnection, findChildren<SocketConnection*>())
    {
        bool blockIsParentOfLeftSocket = (socketConnection->getOutputSocket()->getParent() == block);
        bool blockIsParentOfRightSocket = (socketConnection->getInputSocket()->getParent() == block);
        if(blockIsParentOfLeftSocket || blockIsParentOfRightSocket)
        {
            socketConnection->refresh();
        }
    }
}

QString ComponentArea::getNextSocketId()
{
    this->latestSocketIdNum++;
    return QString("Socket_").append(QString::number(latestSocketIdNum));
}

void ComponentArea::registerSocketId(QString id)
{
    int idNum = id.replace("Socket_", "").toInt();
    if(idNum > latestSocketIdNum)
    {
        latestSocketIdNum = idNum;
    }
}

void ComponentArea::acceptBlockRemoval()
{
    emit blocksCountChanged(--blocksCount);
    emit changed();
}

void ComponentArea::acceptSocketConnectionRemoval()
{
    emit changed();
    emit socketConnectionsCountChanged(--socketConnectionsCount);
}

void ComponentArea::mouseMoveEvent(QMouseEvent *event)
{
    if(pressedSocket_first != 0)
    {
        QPoint mousePos_global;
        mousePos_global = event->globalPos();
        QPoint socketPos = QPoint(pressedSocket_first->width() /2, pressedSocket_first->height() /2);
        connectionPreview->update(pressedSocket_first->mapToGlobal(socketPos), mousePos_global);
    }
    if(middleMouseDragging)
    {
        emit middleMouseDragged(
                    (lastMouseMovePos.x() -event->x()),
                    (lastMouseMovePos.y() -event->y())
                    );
    }
    triggerComponentMouseMovementEvents(event);
    expandRectangularSelection(event->pos());

    lastMouseMovePos = event->pos();
}

void ComponentArea::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MiddleButton)
    {
        middleMouseDragging = true;
    }
    bool componentWasTriggered = !triggerComponentMousePressEvents(event).isEmpty();

    if(event->button() == Qt::LeftButton && !componentWasTriggered)
    {
        beginRectangularSelection(event->pos());
    }

    if(event->button() == Qt::RightButton && !componentWasTriggered)
    {
        showContextMenu(event->pos());
    }
}

void ComponentArea::insert(CircuitFileModel circuitFileModel, QPoint at, bool selectAddition)
{
    circuitFileModel.reassignSocketIds(this);
    Q_FOREACH(BlockModel blockModel, circuitFileModel.blockModels)
    {
        BlockModel adjustedBlockModel = blockModel;
        adjustedBlockModel.location += at;
        AbstractBlock* addedBlock = addBlock(AbstractBlock::getNewInstanceFromParams(this, adjustedBlockModel));
        if(selectAddition) addedBlock->select();

        //Adjust Size of ComponentArea
        int neededWidth =0, neededHeight = 0;
        Q_FOREACH(Component* component, findChildren<Component*>())
        {
            //See ComponentArea::toCircuitFileModel()
            AbstractBlock* block = qobject_cast<AbstractBlock*>(component);
            if(block != 0)
            {
                int x = block->pos().x() + block->width();
                int y = block->pos().y() + block->height();
                if(x > neededWidth) neededWidth = x;
                if(y > neededHeight) neededHeight = y;
            }
        }
        setMinimumSize(neededWidth, neededHeight);
    }

    Q_FOREACH(SocketConnectionModel socketConnectionModel, circuitFileModel.socketConnectionModels)
    {
        AbstractSocket* socketA = findSocketById(socketConnectionModel.socketAId);
        AbstractSocket* socketB = findSocketById(socketConnectionModel.socketBId);
        if(socketA != 0 && socketB != 0)
        {
            SocketConnection* addedSocketConnection = connectSockets(socketA, socketB, socketConnectionModel.color);
            if(addedSocketConnection && selectAddition) addedSocketConnection->select();
        }
    }
}

void ComponentArea::loadArea(CircuitFileModel circuitFileModel)
{
    this->clear();
    insert(circuitFileModel, QPoint(0,0), false);
    setGridSpacing(circuitFileModel.gridSpacing);
    setShowGrid(circuitFileModel.showGrid);
    setMoveComponentsOnGrid(circuitFileModel.moveComponentsOnGrid);
    emit saved();
    emit displayMessageOnStatusbar(tr("Circuit opened successfully."), Qt::black, 4000);

}

void ComponentArea::saveArea(QString fileDir)
{
    CircuitFileOperator* fileOp = new CircuitFileOperator();
    fileOp->save(this->toCircuitFileModel(), fileDir);
    emit saved();
    emit displayMessageOnStatusbar(tr("Circuit saved successfully."), Qt::black, 4000);
}

void ComponentArea::setShowGrid(bool showGrid)
{
    this->showGrid = showGrid;
    this->repaint();
    emit changed();
}

void ComponentArea::setGridSpacing(int gridSpacing)
{
    this->gridSpacing = gridSpacing;
    this->repaint();
    emit changed();
}

void ComponentArea::mouseReleaseEvent(QMouseEvent *event)
{
    QSet<Component*> componentsForTrigger = getComponentsForTriggeringMouseReleaseEvent(event);
    QSet<AbstractBlock*> triggeredBlocks;
    QSet<SocketConnection*> triggeredSocketConnections;

    Q_FOREACH(Component* component, componentsForTrigger)
    {
        AbstractBlock* castedBlock = qobject_cast<AbstractBlock*>(component);
        if(castedBlock != 0) triggeredBlocks.insert(castedBlock);

        SocketConnection* castedConnection = qobject_cast<SocketConnection*>(component);
        if(castedConnection != 0) triggeredSocketConnections.insert(castedConnection);
    }

    bool selectionExists = !selectedBlocks.isEmpty() || !selectedSocketConnections.isEmpty();
    bool triggeredSomething = !componentsForTrigger.isEmpty();
    bool triggeredSomethingFromCurrentSelection = !QSet<AbstractBlock*>(triggeredBlocks).intersect(selectedBlocks).isEmpty() ||
            !QSet<SocketConnection*>(triggeredSocketConnections).intersect(selectedSocketConnections).isEmpty();

    if(!triggeredSomething)
    {
        if(!(event->modifiers() & Qt::ControlModifier)) discardCurrentSelection();
        if(pressedSocket_first != 0 && pressedSocket_second == 0 && event->button() == Qt::LeftButton)
        {
            //Connection is canceled via a click on an empty spot
            if(!connectionPreview.isNull()) connectionPreview->close();
            connectionPreview = QSharedPointer<SocketConnectionPreview>();
            pressedSocket_first = 0;
            this->repaint();
        }
        else if(pressedSocket_first != 0 && pressedSocket_second != 0 && event->button() == Qt::LeftButton)
        {
            //I dont even know which situation this case is for
            if(!connectionPreview.isNull()) connectionPreview->close();
            connectionPreview = QSharedPointer<SocketConnectionPreview>();
            pressedSocket_second = 0;
            this->repaint();
        }
    }

    if(event->button() == Qt::RightButton && selectionExists && !triggeredSomethingFromCurrentSelection)
    {
        if(!(event->modifiers() & Qt::ControlModifier)) discardCurrentSelection();
        Q_FOREACH(AbstractBlock* triggeredBlock, triggeredBlocks) { triggeredBlock->select(); }
        Q_FOREACH(SocketConnection* triggeredSocketConnection, triggeredSocketConnections) { triggeredSocketConnection->select(); }
     }

    if(event->button() == Qt::MiddleButton)
    {
        middleMouseDragging = false;
    }

    if(event->button() == Qt::LeftButton && selecting)
    {
        endRectangularSelection(event->pos());
    }
    triggerComponentMouseReleaseEvents(event, componentsForTrigger);
}

void ComponentArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.eraseRect(QRect(QPoint(0,0), QPoint(this->size().width(), this->size().height())));

    if(showGrid)
    {
        painter.setPen(QPen(Qt::gray, 1, Qt::SolidLine, Qt::SquareCap));

        for(int x = 0; x <= this->size().width(); x += gridSpacing)
        {
            for(int y = 0; y <= this->size().height(); y += gridSpacing)
            {
                painter.drawLine(x - 2, y, x + 2, y);
                painter.drawLine(x, y - 2, x, y + 2);
            }
        }
    }
}

void ComponentArea::removeComponentFromMouseEventLists(Component *component)
{
    componentsUnderMouse.remove(component);
    mousePressedTriggeredComponents.remove(component);
}

void ComponentArea::updateEveryBlock()
{
    Q_FOREACH(AbstractBlock* block, WidgetUtil::findChildrenSafe<AbstractBlock>(this))
    {
        block->updateOutputs();
    }
}

void ComponentArea::startSim()
{
    simulationRunning = true;
    simulationTimer->start();
    emit simStarted();
}

void ComponentArea::stopSim()
{
    simulationRunning = false;
    simulationTimer->stop();
    emit simStopped();
}

void ComponentArea::showContextMenu(QPoint pos)
{
    if(!simIsRunning())
    {
        localContextMenuPos = pos;
        contextMenu->exec(this->mapToGlobal(localContextMenuPos), 0);
    }
}

void ComponentArea::updatePasteContextMenuFromClipboardChange()
{
    QString fullClipboardCircuitDir = clipboard->text();
    if(fullClipboardCircuitDir.endsWith(clipboardCircuitExtension))
    {
        pasteAction->setEnabled(true);

        QString clipboardCircuitFileTitle = clipboard->text().remove(tmpDir).remove(clipboardCircuitExtension).remove("/");
        QDateTime timestamp;
        timestamp.setTime_t(clipboardCircuitFileTitle.toUInt());

        QAction* historyAction = new QAction(0);
        historyAction->setData(QVariant(clipboard->text()));
        historyAction->setText(timestamp.time().toString());
        connect(historyAction, SIGNAL(triggered(bool)), this, SLOT(pasteFromTriggeredHistoryAction()));
        pasteHistoryMenu->insertAction(0, historyAction);
    }
    else
    {
        pasteAction->setEnabled(false);
    }
}

void ComponentArea::beginRectangularSelection(QPoint pos)
{
    if(!selecting)
    {
        selecting = true;
        selectionOrigin = pos;
        selectionRubberBand = QSharedPointer<QRubberBand>(new QRubberBand(QRubberBand::Rectangle, this));
        selectionRubberBand.data()->setGeometry(QRect(selectionOrigin, QSize()));
        selectionRubberBand.data()->show();
    }
}

void ComponentArea::expandRectangularSelection(QPoint pos)
{
    if(selecting && !selectionRubberBand.isNull())
    {
        selectionRubberBand.data()->setGeometry(QRect(selectionOrigin, pos).normalized());
    }
}

void ComponentArea::endRectangularSelection(QPoint pos)
{
    if(selecting)
    {
        QRect selectionRect = QRect(selectionOrigin, pos).normalized();
        Q_FOREACH(AbstractBlock* block, WidgetUtil::findChildrenSafe<AbstractBlock>(this))
        {
            if(selectionRect.intersects( QRect(block->pos(), block->size()) ))
            {
                block->select();
            }
        }

        if(!selectionRubberBand.isNull()) selectionRubberBand.data()->close();
        selectionRubberBand = QSharedPointer<QRubberBand>();
        selecting = false;
    }
}

void ComponentArea::discardCurrentSelection()
{
    Q_FOREACH(AbstractBlock* selectedBlock, selectedBlocks)
    {
        selectedBlock->unselect();
        //selectedBlocks.removeFirst(); //Should get removed via slot childBlock_unselected
    }
    Q_FOREACH(SocketConnection* selectedSocketConnection, selectedSocketConnections)
    {
        selectedSocketConnection->unselect();
        //selectedSocketConnections.removeFirst(); //Same here
    }
}

void ComponentArea::passPropertyChangeToSelection(QString property, QString value)
{
    Q_FOREACH(AbstractBlock* block, selectedBlocks)
    {
        block->acceptPropertyChange(property, value);
    }
    Q_FOREACH(SocketConnection* connection, selectedSocketConnections)
    {
        connection->acceptPropertyChange(property, value);
    }
}

void ComponentArea::copySelectionToClipboard()
{
    if(!simIsRunning())
    {
        //Clipboard gets saved in temporary location with the timestamp as title
        QString timestamp = QString::number(QDateTime::currentDateTime().toTime_t());
        QString fullDir = tmpDir + "/" + timestamp + clipboardCircuitExtension;

        CircuitFileModel cfm = selectionToCircuitFileModel();
        cfm.relativizeLocations();

        CircuitFileOperator().save(cfm, fullDir);

        clipboard->setText(fullDir);
    }
}

void ComponentArea::cutSelectionToClipboard()
{
    if(!simIsRunning())
    {
        copySelectionToClipboard();
        removeComponentsInSelection();
    }
}

void ComponentArea::refreshSocketConnectionSelections()
{
    Q_FOREACH(SocketConnection* socketConnection, WidgetUtil::findChildrenSafe<SocketConnection>(this))
    {
        if(selectedBlocks.contains(socketConnection->getInputSocket()->getParent()) && selectedBlocks.contains(socketConnection->getOutputSocket()->getParent()))
        {
            socketConnection->select();
        }
    }
}

CircuitFileModel ComponentArea::selectionToCircuitFileModel()
{
    CircuitFileModel circuitFileModel = CircuitFileModel();
    Q_FOREACH(AbstractBlock* block, selectedBlocks)
    {
        circuitFileModel.blockModels.append(block->toBlockModel());
    }
    Q_FOREACH(SocketConnection* socketConnection, selectedSocketConnections)
    {
        circuitFileModel.socketConnectionModels.append(socketConnection->toSocketConnectionModel());
    }
    return circuitFileModel;
}

void ComponentArea::removeComponentsInSelection()
{
    if(!simIsRunning())
    {
        Q_FOREACH(AbstractBlock* block, selectedBlocks)
        {
            block->remove();
        }
        Q_FOREACH(SocketConnection* socketConnection, selectedSocketConnections)
        {
            socketConnection->remove();
        }
    }
}

void ComponentArea::pasteFromTriggeredHistoryAction()
{
    QAction* triggeredAction = qobject_cast<QAction*>(QObject::sender());
    if(triggeredAction != 0)
    {
        pasteFrom(localContextMenuPos, triggeredAction->data().toString());
    }

}

void ComponentArea::pasteFromClipboardAtContextMenuPos()
{
    pasteFromClipboard(localContextMenuPos);
}

void ComponentArea::pasteFromClipboardAtMousePos()
{
    pasteFromClipboard(lastMouseMovePos);
}

void ComponentArea::pasteFromClipboard(QPoint at)
{
    pasteFrom(at, clipboard->text());
}

void ComponentArea::pasteFrom(QPoint at, QString file)
{
    if(!simIsRunning())
    {
        discardCurrentSelection();
        if(clipboard->text().endsWith(clipboardCircuitExtension))
        {
            LoadResult loadResult = CircuitFileOperator().load(file);
            if(loadResult.first) //Loading was successful
            {
                insert(loadResult.second, at, true);
            }
        }
    }
}

CircuitFileModel ComponentArea::toCircuitFileModel()
{
    CircuitFileModel circuitFileModel = CircuitFileModel();
    Q_FOREACH(Component* component, this->findChildren<Component*>())
    {
        //findChildren<AbstractBlock*>() works theoretically, but seems to be unreliable
        //concerning the delivered types. So a dynamic cast is used for checking if the
        //Component is an AbstractBlock, instead of retrieving the Blocks directly.

        AbstractBlock* block = qobject_cast<AbstractBlock*>(component);
        if(block != 0) { circuitFileModel.blockModels.append(block->toBlockModel()); }

        //Same for SocketConnections
        SocketConnection* socketConnection = qobject_cast<SocketConnection*>(component);
        if(socketConnection != 0) { circuitFileModel.socketConnectionModels.append(socketConnection->toSocketConnectionModel()); }
    }
    circuitFileModel.gridSpacing = this->gridSpacing;
    circuitFileModel.showGrid = this->showGrid;
    circuitFileModel.moveComponentsOnGrid = this->moveComponentsOnGrid;

    return circuitFileModel;
}

AbstractSocket* ComponentArea::findSocketById(QString id)
{
    Q_FOREACH(AbstractBlock* block, this->findChildren<AbstractBlock*>())
    {
        Q_FOREACH(AbstractSocket* socket, block->findChildren<AbstractSocket*>())
        {
            if(socket->getSocketId() == id)
            {
                return socket;
            }
        }
    }
    return 0;
}

QSet<Component*> ComponentArea::triggerComponentMouseMovementEvents(QMouseEvent *originalMoveEvent)
{
    QSet<Component*> triggeredComponents;
    QSet<Component*> newComponentsUnderMouse;

    Q_FOREACH(Component* component, WidgetUtil::findChildrenSafe<Component>(this))
    {
        if(mousePressedTriggeredComponents.contains(component) || WidgetUtil::widgetIsOnPoint(mapToGlobal(originalMoveEvent->pos()), component))
        {
            newComponentsUnderMouse.insert(component);
            connect(component, SIGNAL(invalidated(Component*)), this, SLOT(removeComponentFromMouseEventLists(Component*)));
            if(!componentsUnderMouse.contains(component))
            {
                component->triggerEnterEvent();             
            }
            component->triggerMouseMoveEvent(WidgetUtil::mapMouseEvent(this, component, originalMoveEvent));
            triggeredComponents.insert(component);
        }
        else if(componentsUnderMouse.contains(component))
        {
            component->triggerLeaveEvent();
            triggeredComponents.insert(component);
        }
    }

    componentsUnderMouse = newComponentsUnderMouse;
    return triggeredComponents;
}

QSet<Component*> ComponentArea::triggerComponentMousePressEvents(QMouseEvent *originalMoveEvent)
{
    QSet<Component*> triggeredComponents;
    Q_FOREACH(Component* component, WidgetUtil::findChildrenSafe<Component>(this))
    {
        if(WidgetUtil::widgetIsOnPoint(mapToGlobal(originalMoveEvent->pos()), component))
        {
            if(component != 0)
            {
                //Dont trigger when it is a SokcetConnection and is not in the TriggerRect
                SocketConnection* castedSocketConnection = qobject_cast<SocketConnection*>(component);
                if(castedSocketConnection == 0 || castedSocketConnection->isInTriggerRects(originalMoveEvent->globalPos()))
                {
                    component->triggerMousePressEvent(WidgetUtil::mapMouseEvent(this, component, originalMoveEvent));
                    triggeredComponents.insert(component);
                    mousePressedTriggeredComponents.insert(component);
                    connect(component, SIGNAL(invalidated(Component*)), this, SLOT(removeComponentFromMouseEventLists(Component*)));
                }
            }
        }
    }
    return triggeredComponents;
}

QSet<Component *> ComponentArea::getComponentsForTriggeringMouseReleaseEvent(QMouseEvent *originalMoveEvent)
{
    QSet<Component*> triggerableComponents;
    Q_FOREACH(Component* component, mousePressedTriggeredComponents)
    {
        triggerableComponents.insert(component);
    }
    return triggerableComponents;
}

void ComponentArea::triggerComponentMouseReleaseEvents(QMouseEvent *originalMoveEvent, QSet<Component *> componentsForTrigger)
{
    Q_FOREACH(Component* component, componentsForTrigger)
    {
        if(component->isValid())
        component->triggerMouseReleaseEvent(WidgetUtil::mapMouseEvent(this, component, originalMoveEvent));
    }
    mousePressedTriggeredComponents.clear();
}

void ComponentArea::initContextMenu()
{
    contextMenu = new QMenu();
    QList<QAction*> pasteActions;
    {
        QIcon icon;
        icon.addFile(":/images/Resources/GenericIcons/paste-48.png", QSize(), QIcon::Normal, QIcon::Off);

        pasteAction = new QAction(icon, tr("Paste"), 0);
        pasteAction->setIconVisibleInMenu(true);
        connect(pasteAction, SIGNAL(triggered(bool)), this, SLOT(pasteFromClipboardAtContextMenuPos()));
        pasteAction->setEnabled(false);
        pasteActions.append(pasteAction);
    }
    contextMenu->addActions(pasteActions);

    {
        QIcon icon;
        icon.addFile(":/images/Resources/GenericIcons/Past-52.png", QSize(), QIcon::Normal, QIcon::Off);

        pasteHistoryMenu = new QMenu(tr("Paste from History"));
        pasteHistoryMenu->setIcon(icon);
        contextMenu->addMenu(pasteHistoryMenu);
    }
}

void ComponentArea::initShortcuts()
{
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_X), this, SLOT(cutSelectionToClipboard()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_C), this, SLOT(copySelectionToClipboard()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_V), this, SLOT(pasteFromClipboardAtMousePos()));
    new QShortcut(QKeySequence(Qt::Key_Delete), this, SLOT(removeComponentsInSelection()));
}

void ComponentArea::clear()
{
    stopSim();
    discardCurrentSelection();
    Q_FOREACH(QObject* object, findChildren<QObject*>())
    {
        AbstractSocket* socket = qobject_cast<AbstractSocket*>(object);
        if(socket != 0)
        {
            socket->invalidate();
        }

        Component* component = qobject_cast<Component*>(object);
        if(component != 0) component->deleteLater();
    }
    blocksCount = 0;
    latestSocketIdNum = 0;
    emit blocksCountChanged(blocksCount);
    socketConnectionsCount = 0;
    emit socketConnectionsCountChanged(socketConnectionsCount);
}

void ComponentArea::playPauseSimulation(bool play)
{
    if(play)
    {
        startSim();
    }
    else
    {
        stopSim();
    }
}

void ComponentArea::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void ComponentArea::dropEvent(QDropEvent *event)
{
    event->acceptProposedAction();

    QPoint pos = event->pos();
    int targetBlockType = event->mimeData()->text().toInt();

    AbstractBlock* block = addBlockAndEmitChanged(AbstractBlock::getNewInstanceFromParams(this, targetBlockType));
    block->move(pos);
}

int ComponentArea::getGridSpacing()
{
    return this->gridSpacing;
}

bool ComponentArea::getMoveComponentsOnGrid()
{
    return this->moveComponentsOnGrid;
}

bool ComponentArea::simIsRunning()
{
    return simulationRunning;
}

bool ComponentArea::isPartOfSelection(Component *component)
{
    Q_FOREACH(AbstractBlock* block, selectedBlocks)
    {
        if(block == component) return true;
    }
    Q_FOREACH(SocketConnection* connection, selectedSocketConnections)
    {
        if(connection == component) return true;
    }
    return false;
}

void ComponentArea::setMoveComponentsOnGrid(bool moveComponentsOnGrid)
{
    this->moveComponentsOnGrid = moveComponentsOnGrid;
    emit changed();
}

AbstractBlock* ComponentArea::addBlock(AbstractBlock *block)
{
    emit blocksCountChanged(++blocksCount);
    block->show();
    return block;
}

AbstractBlock* ComponentArea::addBlockAndEmitChanged(AbstractBlock *block)
{
   AbstractBlock* addedBlock = addBlock(block);
   emit changed();
   return addedBlock;
}
