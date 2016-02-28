/*
 *  componentarea.h: The area where the user places blocks, moves them around, connects
 *  sockets and stuff. Holds Components.
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

#ifndef COMPONENTAREA_H
#define COMPONENTAREA_H

#include <QWidget>

#include <QMouseEvent>
#include <QColor>
#include <QPainter>
#include <QTimer>
#include <QRubberBand>
class QMenu;

#include "Types/circuitfilemodel.h"
class AbstractSocket;
class SocketConnection;
class AbstractBlock;
class SocketConnectionPreview;
class Component;

class ComponentArea : public QWidget
{
    Q_OBJECT

    public:
        ComponentArea(QWidget* parent = 0);

        QString getNextSocketId();
        CircuitFileModel toCircuitFileModel();
        int getGridSpacing();
        bool getMoveComponentsOnGrid();
        bool simIsRunning();
        bool isPartOfSelection(Component* component);

    signals:
        void changed();
        void saved();
        void blockMoved(QWidget* sender, QPoint mousePosition_sender);
        void simStarted();
        void simStopped();

        void displayMessageOnStatusbar(QString message, QColor color, int timeout = 0);
        void blocksCountChanged(int blocksCount);
        void socketConnectionsCountChanged(int socketConnectionsCount);
        void middleMouseDragged(int dx, int dy);

    public slots:
        //Save/Load
        void loadArea(CircuitFileModel circuitFileModel);
        void insert(CircuitFileModel circuitFileModel, QPoint at, bool selectAddition);
        void saveArea(QString fileDir);
        void clear();
        void playPauseSimulation(bool play);

        //Block and Socket management
        SocketConnection* connectSockets(AbstractSocket* a, AbstractSocket* b, QColor connectionColor);
        bool removeSocketConnection(AbstractSocket* a, AbstractSocket* b);
        void registerSocketId(QString id);
        void acceptBlockRemoval();
        void acceptSocketConnectionRemoval();
        void discardCurrentSelection();
        void passPropertyChangeToSelection(QString property, QString value);
        void copySelectionToClipboard();
        void cutSelectionToClipboard();

        //Grid
        void setShowGrid(bool showGrid);
        void setGridSpacing(int gridSpacing);
        void setMoveComponentsOnGrid(bool moveComponentsOnGrid);

        //childEvents
        void childSocket_mousePressEvent(AbstractSocket* sender, QMouseEvent* event);
        void childSocket_mouseReleaseEvent(AbstractSocket* sender, QMouseEvent* event);
        void childBlock_dragged(AbstractBlock *sender, QMouseEvent* event, QPoint deltaPos);
        void childBlock_dragEnded(AbstractBlock* sender);
        void childBlock_selected(AbstractBlock* sender);
        void childBlock_unselected(AbstractBlock* sender);
        void childSocketConnection_selected(SocketConnection* sender);
        void childSocketConnection_unselected(SocketConnection* sender);


    private:
        //"Stats"
        int blocksCount = 0;
        int socketConnectionsCount = 0;

        //Mechanics
        QPoint lastMouseMovePos;
        int latestSocketIdNum = 0;
        QSet<Component*> componentsUnderMouse;
        QSet<Component*> mousePressedTriggeredComponents;
        bool middleMouseDragging = false;
        QClipboard* clipboard = 0;

        //ContextMenu
        const QString clipboardCircuitExtension = ".clipboardCircuit";
        QString tmpDir;
        QMenu *contextMenu = 0;
        QMenu* pasteHistoryMenu = 0;
        QAction* pasteAction = 0;
        QPoint localContextMenuPos = QPoint();

        //Selections
        bool selecting = false;
        QSharedPointer<QRubberBand> selectionRubberBand = QSharedPointer<QRubberBand>();
        QPoint selectionOrigin;
        QSet<AbstractBlock*> selectedBlocks;
        QSet<SocketConnection*> selectedSocketConnections;

        //Simulation
        QTimer* simulationTimer = new QTimer();
        const int simulationTimer_Interval = 25;
        bool simulationRunning = false;

        //Grid
        bool showGrid = true;
        bool moveComponentsOnGrid = false;
        int gridSpacing = 40;

        //SocketConnecting
        AbstractSocket* pressedSocket_first = 0;
        AbstractSocket* pressedSocket_second = 0;
        QSharedPointer<SocketConnectionPreview> connectionPreview = QSharedPointer<SocketConnectionPreview>();
        void refreshSocketConnectionsOfBlock(AbstractBlock* block);

        AbstractBlock* addBlock(AbstractBlock* block);
        AbstractBlock* addBlockAndEmitChanged(AbstractBlock* block);
        AbstractSocket* findSocketById(QString id);
        QSet<Component*> triggerComponentMouseMovementEvents(QMouseEvent* originalMoveEvent);
        QSet<Component*> triggerComponentMousePressEvents(QMouseEvent* originalMoveEvent);
        QSet<Component*> getComponentsForTriggeringMouseReleaseEvent(QMouseEvent* originalMoveEvent);
        void triggerComponentMouseReleaseEvents(QMouseEvent* originalMoveEvent, QSet<Component*> componentsForTrigger);

        void initContextMenu();
        void initShortcuts();

        void mouseMoveEvent(QMouseEvent *event);
        void mousePressEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);

        void dragEnterEvent(QDragEnterEvent *event);
        void dropEvent(QDropEvent *event);
        void paintEvent(QPaintEvent *event);

    private slots:
        void removeComponentFromMouseEventLists(Component* component);
        void updateEveryBlock();
        void startSim();
        void stopSim();
        void showContextMenu(QPoint pos);
        void updatePasteContextMenuFromClipboardChange();

        void beginRectangularSelection(QPoint pos);
        void expandRectangularSelection(QPoint pos);
        void endRectangularSelection(QPoint pos);
        void refreshSocketConnectionSelections();
        CircuitFileModel selectionToCircuitFileModel();
        void removeComponentsInSelection();
        void pasteFromTriggeredHistoryAction();
        void pasteFromClipboardAtContextMenuPos();
        void pasteFromClipboardAtMousePos();
        void pasteFromClipboard(QPoint at);
        void pasteFrom(QPoint at, QString file);
};

#endif // COMPONENTAREA_H
