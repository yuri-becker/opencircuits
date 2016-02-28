/*
 * squarefunctiongeneratorblock.cpp: Implementation of squarefunctiongeneratorblock.h
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

#include "squarefunctiongeneratorblock.h"

#include "Ui/inputnumberdialog.h"
#include <QFuture>
#include <QtConcurrent/QtConcurrent>

#ifdef Q_OS_WIN
#include <windows.h> // for Sleep
#endif

SquareFunctionGeneratorBlock::SquareFunctionGeneratorBlock(ComponentArea *parent, QPoint location, QColor color, bool positionLocked) :
    SquareFunctionGeneratorBlock(parent, getNewBlockModel(parent, location, color, positionLocked))
{
}

SquareFunctionGeneratorBlock::SquareFunctionGeneratorBlock(ComponentArea *parent, BlockModel blockModel) :
    AbstractInstantRespondingBlock(parent, blockModel.location, defaultSize(), blockModel.color, blockModel.positionLocked)
{
    initSockets(blockModel);
    this->highDuration_ms = blockModel.parameters.split(";").at(0).toInt();
    this->lowDuration_ms = blockModel.parameters.split(";").at(1).toInt();

    //Catch destroyed Objects
    connect(getOutputSockets().at(0), SIGNAL(destroyed(QObject*)), this, SLOT(catchSomethingDestroyed()));
    connect(this, SIGNAL(destroyed(QObject*)), this, SLOT(catchSomethingDestroyed()));
    connect(this, SIGNAL(incomingProperyChange(QString,QString)), this, SLOT(changeProperty(QString,QString)));

    //Output
    connect(this, SIGNAL(outputHigh()), getOutputSockets().at(0), SLOT(changeToHigh()));
    connect(this, SIGNAL(outputLow()), getOutputSockets().at(0), SLOT(changeToLow()));
    connect(parent, SIGNAL(simStarted()), this, SLOT(initTimer()));

    initContextMenu();
}

SquareFunctionGeneratorBlock::SquareFunctionGeneratorBlock()
{
}

SquareFunctionGeneratorBlock* SquareFunctionGeneratorBlock::getVirtualInstance()
{
    return new SquareFunctionGeneratorBlock();
}

void SquareFunctionGeneratorBlock::drawBlockOnGivenPainter(QPainter *painter, bool paintHoverOutlines, bool selected)
{
    painter->eraseRect(QRect(QPoint(0,0), QPoint(defaultSize().width(), defaultSize().height())));
    painter->fillRect(1, 1, 30, 18, Qt::white);

    if(selected) painter->setPen(QPen(Qt::gray, 3, Qt::SolidLine, Qt::SquareCap));
    else if(paintHoverOutlines) painter->setPen(QPen(Qt::lightGray, 3, Qt::SolidLine, Qt::SquareCap));
    else painter->setPen(QPen(Qt::transparent, 0, Qt::SolidLine, Qt::SquareCap));

    painter->drawRect(1, 1, 31, 18);

    painter->setPen(QPen(this->getColor(), 1, Qt::SolidLine, Qt::SquareCap));
    painter->drawRect(1, 1, 31, 18);

    painter->drawLine (1, 5,  1, 15);
    painter->drawLine (1,15, 5 , 15);
    painter->drawLine (5,15, 5 , 5);
    painter->drawLine (5,5, 10 , 5);
    painter->drawLine (10,5, 10 ,15);
    painter->drawLine (10,15, 15 ,15);
    painter->drawLine (15,15, 15 ,5);
    painter->drawLine (15,5, 20 ,5);
    painter->drawLine (20,5, 20 ,15);
    painter->drawLine (20,15, 25 ,15);
    painter->drawLine (25,15, 25 ,5);
    painter->drawLine (25,5, 30 ,5);
}

QSize SquareFunctionGeneratorBlock::defaultSize()
{
    return QSize(40,20);
}

void SquareFunctionGeneratorBlock::produceOutputValues()
{
}

QString SquareFunctionGeneratorBlock::getParameters()
{
    return QString::number(highDuration_ms) + ";" + QString::number(lowDuration_ms);
}

void SquareFunctionGeneratorBlock::initTimer()
{
    timer = new QTimer();
    timer->setInterval(highDuration_ms + lowDuration_ms);
    timer->setTimerType(Qt::PreciseTimer);
    timer->setSingleShot(false);

    connect(timer, SIGNAL(timeout()), this, SLOT(timerTick()));
    connect(parent, SIGNAL(simStopped()), timer, SLOT(stop()));;
    connect(parent, SIGNAL(simStopped()), timer, SLOT(deleteLater()));

    timer->start();
}

void SquareFunctionGeneratorBlock::timerTick()
{
    QFuture<void> future = QtConcurrent::run(this, &SquareFunctionGeneratorBlock::doTimerTick);
}

void SquareFunctionGeneratorBlock::changeProperty(QString property, QString value)
{
    if(property == property_squareFunctionGenerator_highDuration) setHighDuration(value.toInt());
    else if(property == property_squareFunctionGenerator_lowDuration) setLowDuration(value.toInt());
}

void SquareFunctionGeneratorBlock::doTimerTick()
{
    if(!somethingDestroyed)
    {
        emit outputLow();
    }

    {
    #ifdef Q_OS_WIN
        Sleep(uint(this->lowDuration_ms));
    #else
        struct timespec ts = { lowDuration_ms / 1000, (lowDuration_ms % 1000) * 1000 * 1000 };
        nanosleep(&ts, NULL);
    #endif
    }

    if(!somethingDestroyed)
    {
        emit outputHigh();
    }

    {
    #ifdef Q_OS_WIN
        Sleep(uint(this->highDuration_ms));
    #else
        struct timespec ts = { highDuration_ms / 1000, (highDuration_ms % 1000) * 1000 * 1000 };
        nanosleep(&ts, NULL);
    #endif
    }
}

void SquareFunctionGeneratorBlock::contextMenu_highDurationTriggered()
{
    int input = InputNumberDialog::getNumberInput(
                this,
                tr("Change HIGH-Duration"),
                tr("Duration: "),
                QIcon(":/images/Resources/BlockSpecificIcons/SquareFunctioGenerator_High_48.png"),
                this->highDuration_ms,
                20, 10000, 250,
                " ms"
                );
    if(input != -1)
    {
        emit requestPropertyChange(property_squareFunctionGenerator_highDuration, QString::number(input));
    }
}

void SquareFunctionGeneratorBlock::contextMenu_lowDurationTriggered()
{
    int input = InputNumberDialog::getNumberInput(
                this,
                tr("Change LOW-Duration"),
                tr("Duration: "),
                QIcon(":/images/Resources/BlockSpecificIcons/SquareFunctionGenerator_Low_48.png"),
                this->lowDuration_ms,
                20, 10000, 250,
                " ms"
                );
    if(input != -1)
    {
        emit requestPropertyChange(property_squareFunctionGenerator_lowDuration, QString::number(input));
    }
}

void SquareFunctionGeneratorBlock::setHighDuration(int ms)
{
    this->highDuration_ms = ms;
}

void SquareFunctionGeneratorBlock::setLowDuration(int ms)
{
    this->lowDuration_ms = ms;
}

void SquareFunctionGeneratorBlock::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter* painter = new QPainter(this);
    drawBlockOnGivenPainter(painter, this->active, this->isSelected);
}

void SquareFunctionGeneratorBlock::initContextMenu()
{
    QList<QAction*> actions;
    {
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/Resources/BlockSpecificIcons/SquareFunctionGenerator_High_48.png"));

        QAction* newAction = new QAction(icon, tr("Change HIGH-Duration..."), 0);
        newAction->setIconVisibleInMenu(true);
        connect(newAction, SIGNAL(triggered()), this, SLOT(contextMenu_highDurationTriggered()));
        actions.append(newAction);
    }
    {
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/Resources/BlockSpecificIcons/SquareFunctionGenerator_Low_48.png"));

        QAction* newAction = new QAction(icon, tr("Change LOW-Duration..."), 0);
        newAction->setIconVisibleInMenu(true);
        connect(newAction, SIGNAL(triggered()), this, SLOT(contextMenu_lowDurationTriggered()));
        actions.append(newAction);
    }
    contextMenu.addActions(actions);
}

BlockModel SquareFunctionGeneratorBlock::getNewBlockModel(ComponentArea *parent, QPoint location, QColor color, bool positionLocked)
{
    BlockModel blockModel = BlockModel();
    blockModel.blockType = AbstractBlock::SQUAREFUNCTIONGENERATOR;
    blockModel.location = location;
    blockModel.color = color;
    blockModel.positionLocked = positionLocked;
    blockModel.outputSocketIds.append(parent->getNextSocketId());
    blockModel.parameters = "50;50";
    return blockModel;
}

void SquareFunctionGeneratorBlock::catchSomethingDestroyed()
{
    somethingDestroyed = true;
    disconnect(this, 0, 0, 0);
    disconnect(0, 0, this, 0);
}
