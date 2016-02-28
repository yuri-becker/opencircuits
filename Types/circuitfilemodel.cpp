/*
 *  circuitfilemodel.cpp: Implementation of circuitfilemodel.h
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

#include "circuitfilemodel.h"
#include "Widgets/componentarea.h"
#include "Utils/stringutil.h"

CircuitFileModel::CircuitFileModel()
{

}

void CircuitFileModel::relativizeLocations()
{
    int maxInt = std::numeric_limits<int>::max();
    QPoint minLoc = QPoint(maxInt, maxInt);

    Q_FOREACH(BlockModel blockModel, blockModels)
    {
        if(blockModel.location.x() < minLoc.x() && blockModel.location.y() < minLoc.y()) minLoc = blockModel.location;
    }

    for(int i = 0; i < blockModels.size(); i++)
    {
        BlockModel newBlockModel = blockModels.at(i);
        newBlockModel.location -= minLoc;
        blockModels.replace(i, newBlockModel);
    }

}

void CircuitFileModel::reassignSocketIds(ComponentArea *socketIdProvider)
{
    QHash<QString, QString> socketIdReassignments;
    for(int i = 0; i < blockModels.size(); i++)
    {
        //Generate new socketIds
        Q_FOREACH(QString socketId, blockModels.at(i).inputSocketIds)
            socketIdReassignments.insert(socketId, socketIdProvider->getNextSocketId());
        Q_FOREACH(QString socketId, blockModels.at(i).outputSocketIds)
            socketIdReassignments.insert(socketId, socketIdProvider->getNextSocketId());
        Q_FOREACH(QString socketId, blockModels.at(i).additionalInputSocketIds)
            socketIdReassignments.insert(socketId, socketIdProvider->getNextSocketId());

        //Update BlockModel with new ids
        BlockModel updatedBlockModel = blockModels.at(i);
        for(int i = 0; i < updatedBlockModel.inputSocketIds.size(); i++)
            updatedBlockModel.inputSocketIds.replace(i, StringUtil::maybeReplaceStringWithValueFromHash(updatedBlockModel.inputSocketIds.at(i), socketIdReassignments));
        for(int i = 0; i < updatedBlockModel.outputSocketIds.size(); i++)
            updatedBlockModel.outputSocketIds.replace(i, StringUtil::maybeReplaceStringWithValueFromHash(updatedBlockModel.outputSocketIds.at(i), socketIdReassignments));
        for(int i = 0; i  < updatedBlockModel.additionalInputSocketIds.size(); i++)
            updatedBlockModel.additionalInputSocketIds.replace(i, StringUtil::maybeReplaceStringWithValueFromHash(updatedBlockModel.additionalInputSocketIds.at(i), socketIdReassignments));
        blockModels.replace(i, updatedBlockModel);
    }

    for(int i = 0; i < socketConnectionModels.size(); i++)
    {
        SocketConnectionModel updatedSocketConnectionModel = socketConnectionModels.at(i);
        updatedSocketConnectionModel.socketAId = StringUtil::maybeReplaceStringWithValueFromHash(updatedSocketConnectionModel.socketAId, socketIdReassignments);
        updatedSocketConnectionModel.socketBId = StringUtil::maybeReplaceStringWithValueFromHash(updatedSocketConnectionModel.socketBId, socketIdReassignments);
        socketConnectionModels.replace(i, updatedSocketConnectionModel);
    }
}
