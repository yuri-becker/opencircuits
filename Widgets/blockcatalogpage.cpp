/*
 *  blockcatalog.cpp: Implementation of blockcatalogpage.h
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

#include "blockcatalogpage.h"

#include <QPainter>

BlockCatalogPage::BlockCatalogPage(QWidget *parent) : QWidget(parent)
{

}

void BlockCatalogPage::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter* painter = new QPainter(this);
    painter->eraseRect(0,0, width(), height());
    painter->fillRect(0,0,width(), height(), Qt::white);
}

