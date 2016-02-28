/*
 * sourceblock.h: Outputs High/Low
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

#ifndef SOURCEBLOCK_H
#define SOURCEBLOCK_H

#include <QPainter>

#include "Components/Blocks/abstractinstantrespondingblock.h"

class SourceBlock : public AbstractInstantRespondingBlock
{
    Q_OBJECT

    public:
        static SourceBlock* getVirtualInstance() { return new SourceBlock(); }
        AbstractBlock* createNewInstance(ComponentArea *parent, BlockModel blockModel) { return new SourceBlock(parent, blockModel); }
        AbstractBlock* createNewInstance(ComponentArea* parent) { return new SourceBlock(parent); }

        void drawBlockOnGivenPainter(QPainter *painter, bool active, bool isSelected);
        QSize defaultSize() { return QSize(40,20); }
        BlockType blockType() { return SOURCE; }

    protected:
        SourceBlock();
        SourceBlock(ComponentArea *parent, QPoint location = QPoint(0,0), QColor color = Qt::black, bool positionLocked = false);
        SourceBlock(ComponentArea *parent, BlockModel blockModel);

        void produceOutputValues();
        void afterMousePressed(QMouseEvent *event) {Q_UNUSED(event); }
        void afterMouseReleased(QMouseEvent* event) { Q_UNUSED(event); }
        QString getParameters();

        const QString property_source_outputHigh = "source.outputHigh";

    private slots:
        void changeProperty(QString property, QString value);
        void requestSetOutputHigh(bool value);
        void setOutputHigh(bool value);

    private:
        void initContextMenu();
        void paintEvent(QPaintEvent *event);

        QAction* outputHighAction = 0;
        AbstractSocket::State output;

        static BlockModel getNewBlockModel(ComponentArea *parent, QPoint location = QPoint(0,0), QColor color = Qt::black, bool positionLocked = false);
};

#endif // SOURCEBLOCK_H
