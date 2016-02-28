/*
 *  componentinfodialog.cpp: Implementation of deprecated componentinfodialog.h
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

#include "componentinfodialog.h"
#include "ui_componentinfodialog.h"
#include "Widgets/showcaseblock.h"
#include "componentinfovalues.h"

ComponentInfoDialog::ComponentInfoDialog(int targetBlockType, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::ComponentInfoDialog)
{
    ui->setupUi(this);
    this->targetBlockType = targetBlockType;

    ComponentInfo componentInfo = ComponentInfoValues::getComponentInfo(targetBlockType);
    setWindowTitle(componentInfo.blockName);
    ui->textLabel->setText(componentInfo.text);

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(new ShowcaseBlock(componentInfo.targetBlockType), 0, 0, Qt::AlignHCenter | Qt::AlignTop);
    ui->showcaseBlockContainer->setLayout(layout);

    this->setWindowFlags(Qt::Dialog);
    setWindowFlags(this->windowFlags() ^ Qt::WindowContextHelpButtonHint);
    setFixedSize(this->size());
}
