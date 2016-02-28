/*
 *  blockcatalog.cpp: Implementation of blockcatalog.h
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

#include "blockcatalog.h"
#include <QGridLayout>
#include <QTabBar>
#include <QFrame>
#include "Components/catalogblock.h"
#include "Components/abstractblock.h"
#include "Widgets/blockcatalogpage.h"

BlockCatalog::BlockCatalog(QWidget *parent) : QTabWidget(parent)
{
    initWidget();
    initPages();
}

void BlockCatalog::initWidget()
{
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    this->setTabPosition(TabPosition::West);
    this->setTabShape(TabShape::Rounded);
    this->raise();
}

void BlockCatalog::initPages()
{
    QPalette pagePal = QPalette(Qt::white);
    pagePal.setColor(QPalette::Window, Qt::white);

    {
        BlockCatalogPage *basicComponents = new BlockCatalogPage();
        QGridLayout *layout = new QGridLayout();

        layout->addWidget(new CatalogBlock(AbstractBlock::SOURCE, parent(),  this), 0, 0);
        layout->addWidget(new CatalogBlock(AbstractBlock::PUSHBUTTON, parent(), this), 0, 1);
        layout->addWidget(new CatalogBlock(AbstractBlock::SQUAREFUNCTIONGENERATOR, parent(), this), 1, 0);
        layout->addWidget(new CatalogBlock(AbstractBlock::SWITCH, parent(), this), 1, 1);
        layout->addWidget(new CatalogBlock(AbstractBlock::LED, parent(), this), 2, 0);

        layout->addItem(new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding), 3, 0, Qt::AlignTop);
        basicComponents->setLayout(layout);

        basicComponents->setPalette(pagePal);
        addTab(basicComponents, tr("Basics"));
    }
    {
        BlockCatalogPage *logics = new BlockCatalogPage();
        QGridLayout *layout = new QGridLayout();

        layout->addWidget(new CatalogBlock(AbstractBlock::ANDGATE, parent(), this),  0, 0, Qt::AlignTop);
        layout->addWidget(new CatalogBlock(AbstractBlock::ORGATE, parent(), this),   0, 1, Qt::AlignTop);
        layout->addWidget(new CatalogBlock(AbstractBlock::NOTGATE, parent(), this),  1, 0, Qt::AlignTop);
        layout->addWidget(new CatalogBlock(AbstractBlock::NANDGATE, parent(), this), 1, 1, Qt::AlignTop);
        layout->addWidget(new CatalogBlock(AbstractBlock::NORGATE, parent(), this),  2, 0, Qt::AlignTop);
        layout->addWidget(new CatalogBlock(AbstractBlock::XORGATE, parent(), this),  2, 1, Qt::AlignTop);
        layout->addWidget(new CatalogBlock(AbstractBlock::XNORGATE, parent(), this), 3, 0, Qt::AlignTop);

        layout->addItem(new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding), 4, 0, Qt::AlignTop);
        logics->setLayout(layout);

        logics->setPalette(pagePal);
        addTab(logics, tr("Logic Gates"));
    }
    {
        BlockCatalogPage* flipFlops = new BlockCatalogPage();
        QGridLayout *layout = new QGridLayout();

        layout->addWidget(new CatalogBlock(AbstractBlock::SRNORLATCH, parent(), this), 0, 0, Qt::AlignTop);
        layout->addWidget(new CatalogBlock(AbstractBlock::GATEDSRNORLATCH, parent(), this), 0, 1, Qt::AlignTop);
        layout->addWidget(new CatalogBlock(AbstractBlock::JKFLIPFLOP, parent(), this), 1, 0, Qt::AlignTop);
        layout->addWidget(new CatalogBlock(AbstractBlock::GATEDJKFLIPFLOP, parent(), this), 1, 1, Qt::AlignTop);
        layout->addWidget(new CatalogBlock(AbstractBlock::TFLIPFLOP, parent(), this), 2, 0, Qt::AlignTop);

        layout->addItem(new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding), 4, 0, Qt::AlignTop);
        flipFlops->setLayout(layout);

        flipFlops->setPalette(pagePal);
        addTab(flipFlops, tr("Flip-Flops"));
    }
    {
        BlockCatalogPage *multiplexingComponents = new BlockCatalogPage();
        QGridLayout *layout = new QGridLayout();

        layout->addWidget(new CatalogBlock(AbstractBlock::MULTIPLEXER, parent(), this), 0, 0);
        layout->addWidget(new CatalogBlock(AbstractBlock::DEMULTIPLEXER, parent(), this), 0, 1);

        layout->addItem(new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding), 3, 0, Qt::AlignTop);
        multiplexingComponents->setLayout(layout);

        multiplexingComponents->setPalette(pagePal);
        addTab(multiplexingComponents, tr("Multiplexing"));
    }
    {
        BlockCatalogPage *extras = new BlockCatalogPage();
        QGridLayout *layout = new QGridLayout();

        layout->addWidget(new CatalogBlock(AbstractBlock::LABEL, parent(), this), 0, 0, Qt::AlignTop);

        layout->addItem(new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding), 4, 0, Qt::AlignTop);
        extras->setLayout(layout);

        extras->setPalette(pagePal);
        addTab(extras, tr("Utils"));
    }

    //Connect WhatIsThisTriggers
    Q_FOREACH(CatalogBlock* catalogBlock, findChildren<CatalogBlock*>())
    {
        connect(catalogBlock, SIGNAL(contextMenu_whatIsThis_triggered(int)), this, SLOT(pass_catalogBlock_whatIsThisTriggered(int)));
    }
}
