/*
 *  componentinfodisplay.cpp: Implementation of componentinfodisplay.h (deprecated)
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

#include "componentinfodisplay.h"

#include "Types/componentinfo.h"
#include "componentinfovalues.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolButton>
#include"Widgets/showcaseblock.h"

ComponentInfoDisplay::ComponentInfoDisplay(QWidget *parent) : QFrame(parent)
{
    initWidget();
}

void ComponentInfoDisplay::showComponentInfo(int targetBlockType)
{
    showComponentInfo(ComponentInfoValues::getComponentInfo(targetBlockType));
}

void ComponentInfoDisplay::showComponentInfo(ComponentInfo componentInfo)
{
    label->setText(componentInfo.wikiUrl);

    Q_FOREACH(ShowcaseBlock* block, showcaseBlockContainer->findChildren<ShowcaseBlock*>())
    {
        block->hide();
        block->deleteLater();
    }
    showcaseBlockContainerLayout->addWidget(new ShowcaseBlock(componentInfo.targetBlockType), 0, 0, Qt::AlignHCenter | Qt::AlignTop);
}

void ComponentInfoDisplay::initWidget()
{

    QHBoxLayout *layout = new QHBoxLayout();

    label = new QLabel();
    label->setMargin(3);
    label->setWordWrap(true);
    label->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
    layout->addWidget(label);

    QVBoxLayout *leftLayout = new QVBoxLayout();
    QToolButton* closeButton = new QToolButton();
    QIcon closeButtonIcon;
    closeButtonIcon.addFile(QStringLiteral(":/images/Resources/GenericIcons/cancel_26px.png"), QSize(), QIcon::Normal, QIcon::Off);
    closeButton->setIcon(closeButtonIcon);
    closeButton->setText("");
    closeButton->setAutoRaise(true);
    connect(closeButton, SIGNAL(clicked(bool)), this, SLOT(requestHide()));
    leftLayout->addWidget(closeButton);

    showcaseBlockContainer = new QWidget();
    showcaseBlockContainer->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    showcaseBlockContainerLayout = new QGridLayout();
    showcaseBlockContainer->setLayout(showcaseBlockContainerLayout);
    leftLayout->addWidget(showcaseBlockContainer);
    layout->addLayout(leftLayout);
    leftLayout->setAlignment(closeButton, Qt::AlignRight | Qt::AlignTop);
    leftLayout->setMargin(0);

    layout->setSpacing(0);
    layout->setMargin(0);

    setLayout(layout);
}
