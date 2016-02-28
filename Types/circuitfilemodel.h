/*
 *  circuitfilemodel.h: Object which facilitates the translation of the ComponentArea's content from and to XML-files.
 * It holds every information from which a ComponentArea's content can be recreated.
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

#ifndef CIRCUITFILEMODEL_H
#define CIRCUITFILEMODEL_H

#include "Types/blockmodel.h"
class BlockModel;
class ComponentArea;
#include "Types/socketconnectionmodel.h"

class CircuitFileModel
{
    public:
        CircuitFileModel();
        void relativizeLocations();
        void reassignSocketIds(ComponentArea* socketIdProvider);

        QList<BlockModel> blockModels;
        QList<SocketConnectionModel> socketConnectionModels;
        int gridSpacing = 40;
        bool showGrid = true;
        bool moveComponentsOnGrid = false;

};

#endif // CIRCUITFILEMODEL_H
