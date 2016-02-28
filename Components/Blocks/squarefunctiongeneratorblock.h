/*
 * squarefunctiongeneratorblock.h: Switches output from HIGH to LOW and vice versa
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

#ifndef SQUAREFUNCTIONGENERATORBLOCK_H
#define SQUAREFUNCTIONGENERATORBLOCK_H

#include "Components/Blocks/abstractinstantrespondingblock.h"

class SquareFunctionGeneratorBlock : public AbstractInstantRespondingBlock
{
    Q_OBJECT

    public:
        static SquareFunctionGeneratorBlock* getVirtualInstance();
        AbstractBlock* createNewInstance(ComponentArea *parent, BlockModel blockModel) { return new SquareFunctionGeneratorBlock(parent, blockModel); }
        AbstractBlock* createNewInstance(ComponentArea* parent) { return new SquareFunctionGeneratorBlock(parent); }

        void drawBlockOnGivenPainter(QPainter *painter, bool active, bool isSelected);
        QSize defaultSize();
        BlockType blockType() { return SQUAREFUNCTIONGENERATOR; }

    protected:
        SquareFunctionGeneratorBlock();
        SquareFunctionGeneratorBlock(ComponentArea* parent, QPoint location = QPoint(0,0), QColor color = Qt::black, bool positionLocked = false);
        SquareFunctionGeneratorBlock(ComponentArea* parent, BlockModel blockModel);

        void produceOutputValues();
        QString getParameters();
        void doTimerTick();
        void afterMousePressed(QMouseEvent *event) {Q_UNUSED(event); }
        void afterMouseReleased(QMouseEvent* event) { Q_UNUSED(event); }

        const QString property_squareFunctionGenerator_lowDuration = "squareFunctionGenerator.lowDuration";
        const QString property_squareFunctionGenerator_highDuration = "squareFunctionGenerator.highDuration";

    signals:
        void outputLow();
        void outputHigh();

    protected slots:
        void timerTick();

    private slots:
        void changeProperty(QString property, QString value);
        void contextMenu_highDurationTriggered();
        void contextMenu_lowDurationTriggered();    
        void setHighDuration(int ms);
        void setLowDuration(int ms);
        void catchSomethingDestroyed();
        void initTimer();

    private:
        QTimer* timer = 0;
        bool somethingDestroyed = false;
        int highDuration_ms = 50;
        int lowDuration_ms = 50;

        void initContextMenu();
        void paintEvent(QPaintEvent *event);

        static BlockModel getNewBlockModel(ComponentArea* parent, QPoint location = QPoint(0,0), QColor color = Qt::black, bool positionLocked = false);


};

#endif // SQUAREFUNCTIONGENERATORBLOCK_H
