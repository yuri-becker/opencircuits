/*
 *  catalogblock.cpp: Implementation of catalogblock.h
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

#include "catalogblock.h"
#include "Ui/componentinfodialog.h"
#include "componentinfovalues.h"
#include "Utils/widgetutil.h"
#include <QDrag>
#include <QMimeData>
#include "Components/abstractblock.h"

CatalogBlock::CatalogBlock(int targetBlockType, QObject* targetComponentAreasParent , QWidget *parent) : QWidget(parent)
{
    this->targetBlockType = targetBlockType;
    this->targetComponentAreasParent = targetComponentAreasParent;

    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::transparent);
    setPalette(palette);

    setToolTip(ComponentInfoValues::getComponentInfo(targetBlockType).blockName);
    raise();

    setContextMenuPolicy(Qt::CustomContextMenu);
    initContextMenu();
    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));

    //Size must not be 0 for the paintEvent, in which the actual size is determined, to be called
    this->setFixedSize(5,5);

    //The object may be referenced outside of the UI-thread, so the repaint has to be
    //executed via Signal/Slot.
    connect(this, SIGNAL(requestRepaint()), this, SLOT(repaintRequested()));
    //emit requestRepaint();
}

void CatalogBlock::showContextMenu(const QPoint &position)
{
    contextMenu.exec(this->mapToGlobal(position), 0);
}

void CatalogBlock::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        dragBeginPos = event->pos();
        QDrag* drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData();
        mimeData->setText(QString::number(this->targetBlockType));
        drag->setMimeData(mimeData);

        drag->exec(Qt::CopyAction);
    }
}

void CatalogBlock::mouseMoveEvent(QMouseEvent *event)
{
    if((event->button() == Qt::LeftButton) )
    {
        QDrag* drag = new QDrag(this);
        QMimeData* mimeData = new QMimeData();
        mimeData->setText(QString::number(this->targetBlockType));
        drag->setMimeData(mimeData);

        drag->exec(Qt::CopyAction);
    }
}

void CatalogBlock::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter* painter = new QPainter(this);

    AbstractBlock* virtualTargetBlock = AbstractBlock::getVirtualInstance(targetBlockType);
    setFixedSize(virtualTargetBlock ->defaultSize());
    virtualTargetBlock ->drawBlockOnGivenPainter(painter, false, false);
}

void CatalogBlock::initContextMenu()
{
    QList<QAction*> actions;
    {
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/Resources/GenericIcons/info-48.png"), QSize(), QIcon::Normal, QIcon::Off);

        QAction* newAction = new QAction(icon, tr("What's this?"), 0);
        newAction->setIconVisibleInMenu(true);
        connect(newAction, SIGNAL(triggered()), this, SLOT(pass_contextMenu_whatIsThis_triggered()));
        actions.append(newAction);
    }
    contextMenu.addActions(actions);
    contextMenu.addSeparator();
}

void CatalogBlock::repaintRequested()
{
    repaint();
}
