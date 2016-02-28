/*
 * labelblock.h: Displays text
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

#ifndef LABELBLOCK_H
#define LABELBLOCK_H

#include "Components/Blocks/abstractinstantrespondingblock.h"

class LabelBlock : public AbstractInstantRespondingBlock
{
    Q_OBJECT

    public:
        static LabelBlock* getVirtualInstance();
        AbstractBlock* createNewInstance(ComponentArea *parent, BlockModel blockModel) { return new LabelBlock(parent, blockModel); }
        AbstractBlock* createNewInstance(ComponentArea* parent) { return new LabelBlock(parent); }

        void drawBlockOnGivenPainter(QPainter *painter, bool active, bool isSelected);
        void drawBlockOnGivenPainter(QPainter *painter, bool active, bool isSelected, QString text);
        QSize defaultSize();
        BlockType blockType() { return LABEL; }

    protected:
        LabelBlock();
        LabelBlock(ComponentArea *parent, QPoint location = QPoint(0,0), QColor color = Qt::black, bool positionLocked = false);
        LabelBlock(ComponentArea *parent, BlockModel blockModel);

        void produceOutputValues();
        QString getParameters();
        void afterMousePressed(QMouseEvent *event) {Q_UNUSED(event); }
        void afterMouseReleased(QMouseEvent* event) { Q_UNUSED(event); }

        const QString property_label_text = "label.text";

    protected slots:
        void changeProperty(QString property, QString value);

    private slots:
        void contextMenu_changeTextTriggered();

    private:
        void initContextMenu();
        static BlockModel getNewBlockModel(QPoint location = QPoint(0,0), QColor color = Qt::black, bool positionLocked = false);

        void paintEvent(QPaintEvent *event);
        void setText(QString text);

        QString text = "Text";
};

#endif // LABELBLOCK_H
