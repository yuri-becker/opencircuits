/*
 * labelblock.cpp: Implementation of labelblock.h
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

#include "labelblock.h"

#include "Ui/inputtextdialog.h"

LabelBlock::LabelBlock(ComponentArea *parent, QPoint location, QColor color, bool positionLocked) :
    LabelBlock(parent, getNewBlockModel(location, color, positionLocked))
{

}

LabelBlock::LabelBlock(ComponentArea *parent, BlockModel blockModel) :
    AbstractInstantRespondingBlock(parent, blockModel.location, defaultSize(), blockModel.color, blockModel.positionLocked )
{
    this->text = blockModel.parameters;
    initContextMenu();
    connect(this, SIGNAL(incomingProperyChange(QString,QString)), this, SLOT(changeProperty(QString,QString)));
    this->repaint();
}

LabelBlock::LabelBlock()
{
}

LabelBlock* LabelBlock::getVirtualInstance()
{
    return new LabelBlock();
}

void LabelBlock::drawBlockOnGivenPainter(QPainter *painter, bool paintHoverOutlines, bool selected)
{
    drawBlockOnGivenPainter(painter, paintHoverOutlines, selected, "Text");
}

void LabelBlock::drawBlockOnGivenPainter(QPainter *painter, bool paintHoverOutlines, bool selected, QString text)
{
    painter->eraseRect(QRect(QPoint(0,0), QPoint(defaultSize().width(), defaultSize().height())));

    if(selected)  painter->setPen(QPen(Qt::gray, 3, Qt::SolidLine, Qt::SquareCap));
    else if(paintHoverOutlines) painter->setPen(QPen(Qt::lightGray, 3, Qt::SolidLine, Qt::SquareCap));
    else  painter->setPen(QPen(Qt::transparent, 0, Qt::SolidLine, Qt::SquareCap));

    painter->drawText(-1, -1, 9 * QString(text).count(), 16, Qt::AlignLeft | Qt::AlignTop, text);

    painter->setPen(QPen(this->getColor(), 2, Qt::SolidLine, Qt::SquareCap));
    painter->drawText(0, 0, 9 * QString(text).count(), 13, Qt::AlignLeft | Qt::AlignTop, text);
}

QSize LabelBlock::defaultSize()
{
     return QSize(9 * 4,13);
}

void LabelBlock::setText(QString text)
{
    this->text = text;
    this->repaint();
}


void LabelBlock::produceOutputValues()
{

}

QString LabelBlock::getParameters()
{
    return text;
}

void LabelBlock::changeProperty(QString property, QString value)
{
    if(property == property_label_text) setText(value);
}

void LabelBlock::contextMenu_changeTextTriggered()
{
    QString textInput = InputTextDialog::getTextInput(this, tr("Change text..."), tr("Text:"), this->text, QIcon(":/images/Resources/GenericIcons/pencil-48.png"));
    if(textInput != "")
    {
        emit requestPropertyChange(property_label_text, textInput);
    }
}

void LabelBlock::initContextMenu()
{
    QList<QAction*> actions;
    {
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/Resources/GenericIcons/pencil-48.png"));

        QAction* newAction = new QAction(icon, tr("Change Text"), 0);
        newAction->setIconVisibleInMenu(true);
        connect(newAction, SIGNAL(triggered()), this, SLOT(contextMenu_changeTextTriggered()));
        actions.append(newAction);
    }
    contextMenu.addActions(actions);
}

void LabelBlock::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)

    this->setFixedSize(9 * QString(this->text).count(), this->height());
    QPainter* painter = new QPainter(this);
    drawBlockOnGivenPainter(painter, this->active, this->isSelected, this->text);
}

BlockModel LabelBlock::getNewBlockModel(QPoint location, QColor color, bool positionLocked)
{
    BlockModel blockModel = BlockModel();
    blockModel.blockType = AbstractBlock::LABEL;
    blockModel.location = location;
    blockModel.color = color;
    blockModel.parameters = "Text";
    blockModel.positionLocked = positionLocked;
    return blockModel;
}
