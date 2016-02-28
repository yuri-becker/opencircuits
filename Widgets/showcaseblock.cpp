/*
 *  showcaseblock.cpp: Implementation of showcaseblock.h
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

#include "showcaseblock.h"

ShowcaseBlock::ShowcaseBlock(int targetBlockType, QWidget *parent)
    : QWidget(parent)
{
    this->targetBlockType = targetBlockType;

    QColor palcl = QColor(Qt::transparent);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Base, palcl);
    palette.setColor(QPalette::Window, palcl);
    palette.setColor(QPalette::AlternateBase, palcl);
    setPalette(palette);

    raise();

    setFixedSize(5,5);

    connect(this, SIGNAL(requestRepaint()), this, SLOT(repaintRequested()));
    emit requestRepaint();
}

void ShowcaseBlock::repaintRequested()
{
    this->repaint();
}

void ShowcaseBlock::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter* painter = new QPainter(this);

    AbstractBlock* targetBlockSample = AbstractBlock::getVirtualInstance(targetBlockType);
    setFixedSize(targetBlockSample->defaultSize());
    targetBlockSample->drawBlockOnGivenPainter(painter, false, false);
}

