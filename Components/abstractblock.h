/*
 *  abstractblock.h: Provides general functionality like dragging, adding sockets, etc. for Blocks.
 * Also manages its subclasses via BlockType and getVirtualInstance().
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

#ifndef BLOCK_H
#define BLOCK_H

#include <QString>
#include <QList>
#include <QWidget>
#include <QColor>
#include <QMouseEvent>
#include <QApplication>

#include "Components/Sockets/inputsocket.h"
#include "Components/Sockets/outputsocket.h"
#include "Components/Sockets/additionalinputsocket.h"

#include "Components/componentwithcolorcontextmenu.h"
#include "Widgets/componentarea.h"


class AbstractBlock : public ComponentWithColorContextMenu
{

    Q_OBJECT

    public:
        enum BlockType {
            LED,
            SOURCE,
            ANDGATE,
            ORGATE,
            NOTGATE,
            NANDGATE,
            NORGATE,
            XORGATE,
            XNORGATE,
            LABEL,
            SPLITTER,
            SQUAREFUNCTIONGENERATOR,
            PUSHBUTTON,
            SWITCH,
            ERRORDISPLAY,
            SRNORLATCH,
            TFLIPFLOP,
            JKFLIPFLOP,
            MULTIPLEXER,
            DEMULTIPLEXER,
            GATEDSRNORLATCH,
            GATEDJKFLIPFLOP
        };

        ~AbstractBlock();

        static AbstractBlock* getVirtualInstance(int blockType);
        static AbstractBlock* getNewInstanceFromParams(ComponentArea* parent, BlockModel blockModel);
        static AbstractBlock* getNewInstanceFromParams(ComponentArea* parent, int blockType);

        virtual AbstractBlock* createNewInstance(ComponentArea *parent, BlockModel blockModel) = 0;
        virtual AbstractBlock* createNewInstance(ComponentArea *parent) = 0;

        virtual void drawBlockOnGivenPainter(QPainter* painter, bool active, bool isSelected) = 0;
        virtual QSize defaultSize() = 0;
        virtual BlockType blockType() = 0;

        BlockModel toBlockModel();
        ComponentArea* getParentComponentArea();
        void addSocketAndFixPosition(AbstractSocket* socket);
        QList<InputSocket*> getInputSockets();
        QList<OutputSocket*> getOutputSockets();
        QList<AdditionalInputSocket*> getAdditionalInputSockets();

    public slots:
        virtual void updateOutputs() = 0;
        void remove();
        void select();
        void unselect();

    signals:
        void dragged(AbstractBlock* sender, QMouseEvent* event, QPoint deltaPos);
        void dragEnded(AbstractBlock* sender);
        void simStarted();
        void simStopped();
        void selected(AbstractBlock* sender);
        void unselected(AbstractBlock* sender);

    protected:
        AbstractBlock(ComponentArea *parent = 0, QPoint location = QPoint(0,0), QSize size = QSize(0,0), QColor color = Qt::black, bool positionLocked = false);

        bool isSelected = false;
        ComponentArea* parent = 0;
        void initSockets(BlockModel blockModel);
        virtual QString getParameters() = 0;
        virtual void produceOutputValues() = 0;
        virtual void afterMousePressed(QMouseEvent* event) = 0;
        virtual void afterMouseReleased(QMouseEvent* event) = 0;

        const QString property_block_positionLocked = "block.positionLocked";
        const QString property_block_rise = "block.rise";

    protected slots:
        void resetOutputs();

    private:
        QList<InputSocket*> inputSockets;
        QList<OutputSocket*> outputSockets;
        QList<AdditionalInputSocket*> additionalInputSockets;

        bool postionLocked;
        bool dragging = false;
        QPoint originalPos;
        QPoint offset;

        QAction* positionLockAction = 0;

        void initContextMenu();
        void initEvents();

        void onEnter();
        void onMouseMove(QMouseEvent *event);
        void onLeave();
        void beforeMousePress(QMouseEvent* event);
        void onMousePress(QMouseEvent *event);
        void onMouseRelease(QMouseEvent *event);

    private slots:
        void triggerSimStartedSignal();
        void triggerSimStoppedSignal();

        void changeProperty(QString property, QString value);
        void requestSetPositionLocked(bool positionLocked);
        void requestRise();
        void setPositionLocked(bool positionLocked);

};

#endif // BLOCK_H
