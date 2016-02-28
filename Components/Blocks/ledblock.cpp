/*
 * ledblock.cpp: Implementation of ledblock.h
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

#include "ledblock.h"

LedBlock::LedBlock(ComponentArea *parent, QPoint location, QColor componentColor, QColor illuminationColor, bool positionLocked) :
    LedBlock(parent, getNewBlockModel(parent, location, componentColor, positionLocked))
{
    this->setIllumintaionColor(illuminationColor);
}

LedBlock::LedBlock(ComponentArea *parent, BlockModel blockModel) :
    AbstractInstantRespondingBlock(parent, blockModel.location, defaultSize(), blockModel.color, blockModel.positionLocked)
{
    initSockets(blockModel);
    initContextMenu();
    initEvents();
    connect(this, SIGNAL(incomingProperyChange(QString,QString)), this, SLOT(changeProperty(QString,QString)));
    this->setIllumintaionColor(QColor(blockModel.parameters));
}

LedBlock::LedBlock()
{
}

LedBlock* LedBlock::getVirtualInstance()
{
    return new LedBlock();
}

void LedBlock::drawBlockOnGivenPainter(QPainter *painter, bool paintHoverOutlines, bool selected)
{
    drawBlockOnGivenPainter(painter, paintHoverOutlines, selected, false, Qt::red);
}

void LedBlock::drawBlockOnGivenPainter(QPainter *painter, bool paintHoverOutlines, bool selected, bool paintLight, QColor illuminationColor)
{
    painter->eraseRect(QRect(QPoint(0,0), QPoint(defaultSize().width(), defaultSize().height())));
    painter->setBrush(QBrush(Qt::white,Qt::SolidPattern));
    painter->drawEllipse(QRect(9, 1, 18, 18));
    if(selected) painter->setPen(QPen(Qt::gray, 3, Qt::SolidLine, Qt::FlatCap)); //Selection is prioritized
    else if(paintHoverOutlines) painter->setPen(QPen(Qt::lightGray, 3, Qt::SolidLine, Qt::FlatCap));
    else painter->setPen(QPen(Qt::transparent, 0, Qt::SolidLine, Qt::FlatCap));

    painter->drawEllipse(QRect(9, 1, 19, 19));
    painter->drawLine(12, 4, 25, 17);
    painter->drawLine(12, 17, 25, 4);

    if(paintLight)
    {
        painter->setBrush(QBrush(illuminationColor,Qt::SolidPattern));
        painter->drawEllipse(QRect(9, 1, 18, 18));
    }
    painter->setPen(QPen(this->getColor(), 1, Qt::SolidLine, Qt::FlatCap));
    painter->drawEllipse(QRect(9, 1, 18, 18));
    painter->drawLine(12, 4, 25, 17);
    painter->drawLine(12, 17, 25, 4);
}

QSize LedBlock::defaultSize()
{
    return QSize(30, 20);
}

void LedBlock::produceOutputValues()
{
    emit requestRepaint();
}

QString LedBlock::getParameters()
{
    return this->illuminationColor.name();
}

void LedBlock::changeProperty(QString property, QString value)
{
    if(property == property_led_illuminationColor) setIllumintaionColor(QColor(value));
    this->produceOutputValues();
}

void LedBlock::contextMenu_illuminationColorTriggered_red()
{
    emit requestPropertyChange(property_led_illuminationColor, QColor(Qt::red).name());
}

void LedBlock::contextMenu_illuminationColorTriggered_green()
{
    emit requestPropertyChange(property_led_illuminationColor, QColor(Qt::green).name());
}

void LedBlock::contextMenu_illuminationColorTriggered_blue()
{
    emit requestPropertyChange(property_led_illuminationColor, QColor(Qt::cyan).name());
}

void LedBlock::contextMenu_illuminationColorTriggered_yellow()
{
    emit requestPropertyChange(property_led_illuminationColor, QColor(Qt::yellow).name());
}

void LedBlock::initContextMenu()
{
    QList<QAction*> actions;
    {
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/Resources/ColorContextMenuIcons/red.png"), QSize(), QIcon::Normal, QIcon::Off);

        QAction* newAction = new QAction(icon, tr("Illumination: Red"), 0);
        newAction->setIconVisibleInMenu(true);
        connect(newAction, SIGNAL(triggered()), this, SLOT(contextMenu_illuminationColorTriggered_red()));
        actions.append(newAction);
    }
    {
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/Resources/ColorContextMenuIcons/green.png"), QSize(), QIcon::Normal, QIcon::Off);

        QAction* newAction = new QAction(icon, tr("Illumination: Green"), 0);
        newAction->setIconVisibleInMenu(true);
        connect(newAction, SIGNAL(triggered()), this, SLOT(contextMenu_illuminationColorTriggered_green()));
        actions.append(newAction);
    }
    {
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/Resources/ColorContextMenuIcons/yellow.png"), QSize(), QIcon::Normal, QIcon::Off);

        QAction* newAction = new QAction(icon, tr("Illumination: Yellow"), 0);
        newAction->setIconVisibleInMenu(true);
        connect(newAction, SIGNAL(triggered()), this, SLOT(contextMenu_illuminationColorTriggered_yellow()));
        actions.append(newAction);
    }
    {
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/Resources/ColorContextMenuIcons/cyan.png"), QSize(), QIcon::Normal, QIcon::Off);

        QAction* newAction = new QAction(icon, tr("Illumination: Blue"), 0);
        newAction->setIconVisibleInMenu(true);
        connect(newAction, SIGNAL(triggered()), this, SLOT(contextMenu_illuminationColorTriggered_blue()));
        actions.append(newAction);
    }
    contextMenu.addActions(actions);
}

void LedBlock::initEvents()
{
    connect(this, SIGNAL(requestRepaint()), this, SLOT(repaintRequested()));
}

void LedBlock::setIllumintaionColor(QColor color)
{
    this->illuminationColor = color;
    this->repaint();
}

void LedBlock::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter* painter = new QPainter(this);
    drawBlockOnGivenPainter(
        painter,
        this->active,
        this->isSelected,
        getInputSockets().at(0)->getState() == AbstractSocket::HIGH,
        this->illuminationColor
    );
}

BlockModel LedBlock::getNewBlockModel(ComponentArea *parent, QPoint location, QColor color, bool positionLocked)
{
    BlockModel blockModel = BlockModel();
    blockModel.blockType = AbstractBlock::LED;
    blockModel.location = location;
    blockModel.color = color;
    blockModel.positionLocked = positionLocked;
    blockModel.inputSocketIds.append(parent->getNextSocketId());
    return blockModel;
}
