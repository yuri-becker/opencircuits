/*
 *  componentinfovalues.h: Collection of Values for ComponentInfo.
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

#ifndef COMPONENTINFOVALUES_H
#define COMPONENTINFOVALUES_H

#include <QObject>

#include "Types/componentinfo.h"

class ComponentInfoValues : public QObject
{
    Q_OBJECT //for tr()

    public:
        static ComponentInfo getComponentInfo(int blockType);

        static ComponentInfo ledInfo();
        static ComponentInfo sourceInfo();
        static ComponentInfo andgateInfo();
        static ComponentInfo orgateInfo();
        static ComponentInfo notgateInfo();
        static ComponentInfo nandgateInfo();
        static ComponentInfo norgateInfo();
        static ComponentInfo xorgateInfo();
        static ComponentInfo xnorgateInfo();
        static ComponentInfo labelInfo();
        static ComponentInfo splitterInfo();
        static ComponentInfo squareFunctionGeneratorInfo();
        static ComponentInfo pushButtonInfo();
        static ComponentInfo switchInfo();
        static ComponentInfo srNorLatchInfo();
        static ComponentInfo tFlipFlopInfo();
        static ComponentInfo jkFlipFlopInfo();
        static ComponentInfo multiplexerInfo();
        static ComponentInfo demultiplexerInfo();
        static ComponentInfo gatedSrNorLatchInfo();
        static ComponentInfo gatedJkFlipFlopInfo();

    private:
        ComponentInfoValues();


};

#endif // COMPONENTINFOVALUES_H
