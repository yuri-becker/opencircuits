/*
 *  circuitsstatusbar.cpp: Implementation of circuitsstatusbar.h
 * to create them.
 *
 * Copyright (C) 2015 Yuri Becker <hi@yuri.li>
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

#include "circuitsstatusbar.h"

#include <QHBoxLayout>

CircuitsStatusBar::CircuitsStatusBar(QWidget *parent) :
    QStatusBar(parent)
{
    initUi();
}

void CircuitsStatusBar::showMessageAndChangeColor(QString message, QColor color, int timeout)
{
    QPalette pal = palette();
    pal.setColor(QPalette::WindowText, color);
    setPalette(pal);

    showMessage(message, timeout);
}

void CircuitsStatusBar::updateBlocksCount(int blocksCount)
{
    blocksCountLabel->setText(tr("Components: ").append(QString::number(blocksCount)));
}

void CircuitsStatusBar::updateSocketConnectionsCount(int socketConnectionsCount)
{
    socketConnectionsCountLabel->setText(tr("Connections: ").append(QString::number(socketConnectionsCount)));
}

void CircuitsStatusBar::initUi()
{
    QPalette permanentWidgetPalette = palette();
    permanentWidgetPalette.setColor(QPalette::WindowText, Qt::black);

    blocksCountLabel = new QLabel();
    addPermanentWidget(blocksCountLabel);
    blocksCountLabel->setPalette(permanentWidgetPalette);
    updateBlocksCount(0);
    blocksCountLabel->show();

    socketConnectionsCountLabel = new QLabel();
    addPermanentWidget(socketConnectionsCountLabel);
    socketConnectionsCountLabel->setPalette(permanentWidgetPalette);
    updateSocketConnectionsCount(0);
    socketConnectionsCountLabel->show();
}
