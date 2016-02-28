/*
 *  showcaseblock.h: Draws a block which does nothing.
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

#ifndef SHOWCASEBLOCK_H
#define SHOWCASEBLOCK_H

#include <QWidget>

#include "Components/Blocks/andgateblock.h"
#include "Components/Blocks/ledblock.h"
#include "Components/Blocks/nandgateblock.h"
#include "Components/Blocks/norgateblock.h"
#include "Components/Blocks/notgateblock.h"
#include "Components/Blocks/orgateblock.h"
#include "Components/Blocks/sourceblock.h"
#include "Components/Blocks/xnorgateblock.h"
#include "Components/Blocks/xorgateblock.h"
#include "Components/Blocks/labelblock.h"
#include "Components/Blocks/splitterblock.h"
#include "Components/Blocks/squarefunctiongeneratorblock.h"
#include "Components/Blocks/pushbuttonblock.h"

class ShowcaseBlock : public QWidget
{
    Q_OBJECT

    public:
        ShowcaseBlock(int targetBlockType, QWidget *parent = 0);
        int targetBlockType;

    signals:
        void requestRepaint();

    private slots:
        void repaintRequested();

    private:
        void paintEvent(QPaintEvent* event);

};

#endif // SHOWCASEBLOCK_H
