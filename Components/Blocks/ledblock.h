/*
 * ledblock.h: LED
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

#ifndef LEDBLOCK_H
#define LEDBLOCK_H

#include <QPainter>
#include <QString>

#include "Components/Blocks/abstractinstantrespondingblock.h"

class LedBlock : public AbstractInstantRespondingBlock
{
    Q_OBJECT

    public:
        static LedBlock* getVirtualInstance();
        AbstractBlock* createNewInstance(ComponentArea *parent, BlockModel blockModel) { return new LedBlock(parent, blockModel); }
        AbstractBlock* createNewInstance(ComponentArea* parent) { return new LedBlock(parent); }

        void drawBlockOnGivenPainter(QPainter* painter, bool active, bool isSelected);
        void drawBlockOnGivenPainter(QPainter *painter, bool active, bool isSelected, bool paintLight, QColor illuminationColor);
        QSize defaultSize();
        BlockType blockType() { return LED; }

    protected:
        LedBlock();
        LedBlock(ComponentArea *parent, QPoint location = QPoint(0,0), QColor componentColor = Qt::black, QColor illuminationColor = Qt::red, bool positionLocked = false);
        LedBlock(ComponentArea *parent, BlockModel blockModel);

        void produceOutputValues();
        QString getParameters();
        void afterMousePressed(QMouseEvent *event) {Q_UNUSED(event); }
        void afterMouseReleased(QMouseEvent* event) { Q_UNUSED(event); }

        const QString property_led_illuminationColor = "led.illuminationColor";

    private slots:
        void changeProperty(QString property, QString value);
        void contextMenu_illuminationColorTriggered_red();
        void contextMenu_illuminationColorTriggered_green();
        void contextMenu_illuminationColorTriggered_yellow();
        void contextMenu_illuminationColorTriggered_blue();

    private:
        QColor illuminationColor;

        void initContextMenu();
        void initEvents();

        void setIllumintaionColor(QColor color);
        void paintEvent(QPaintEvent *event);

        static BlockModel getNewBlockModel(ComponentArea *parent, QPoint location = QPoint(0,0), QColor color = Qt::black, bool positionLocked = false);

};

#endif // LEDBLOCK_H
