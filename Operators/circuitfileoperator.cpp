/*
 *  circuitfileoperator.cpp: Implementation of circuitfileoperator.h
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

#include "circuitfileoperator.h"

#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>
#include <QMessageBox>

#include "Utils/tofromstringutil.h"

CircuitFileOperator::CircuitFileOperator()
{

}

LoadResult CircuitFileOperator::load()
{
    CircuitFileModel result = CircuitFileModel();

    QFile file(this->filepath);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        showLoadErrorMessage();
        return LoadResult(false, CircuitFileModel());
    }

    QXmlStreamReader xmlReader(&file);
    xmlReader.readNext();

    while(!xmlReader.atEnd())
    {
        xmlReader.readNext();
        if(xmlReader.isStartElement())
        {
            if(xmlReader.name().toString() == "circuit")
            {
                Q_FOREACH(QXmlStreamAttribute attribute, xmlReader.attributes())
                {
                    if(attribute.name().toString() == "gridSpacing") result.gridSpacing = attribute.value().toString().toInt();
                    else if(attribute.name().toString() == "showGrid") result.showGrid = attribute.value().toString().toInt();
                    else if(attribute.name().toString() == "moveComponentsOnGrid") result.moveComponentsOnGrid = attribute.value().toString().toInt();
                }
            }
            else if(xmlReader.name().toString() == "block")
            {
                BlockModel blockModel = BlockModel();
                Q_FOREACH(QXmlStreamAttribute attribute, xmlReader.attributes())
                {
                    if(attribute.name().toString() == "blockType") blockModel.blockType = attribute.value().toInt();
                    else if (attribute.name().toString() == "location") blockModel.location = ToFromStringUtil::pointFromString(attribute.value().toString());
                    else if (attribute.name().toString() == "color") blockModel.color = QColor(attribute.value().toString());
                    else if (attribute.name().toString() == "inputSocketIds") blockModel.inputSocketIds = ToFromStringUtil::listOfStringsFromString(attribute.value().toString());
                    else if (attribute.name().toString() == "outputSocketIds") blockModel.outputSocketIds = ToFromStringUtil::listOfStringsFromString(attribute.value().toString());
                    else if (attribute.name().toString() == "additionalInputSocketIds") blockModel.additionalInputSocketIds = ToFromStringUtil::listOfStringsFromString(attribute.value().toString());
                    else if (attribute.name().toString() == "parameters") blockModel.parameters = attribute.value().toString();
                    else if (attribute.name().toString() == "positionLocked") blockModel.positionLocked = attribute.value().toString().toInt();
                }
                result.blockModels.append(blockModel);
            }
            else if (xmlReader.name().toString() == "socketConnection")
            {
                SocketConnectionModel socketConnectionModel = SocketConnectionModel();
                Q_FOREACH(QXmlStreamAttribute attribute, xmlReader.attributes())
                {
                    if(attribute.name().toString() == "socketAId") socketConnectionModel.socketAId = attribute.value().toString();
                    else if(attribute.name().toString() == "socketBId") socketConnectionModel.socketBId = attribute.value().toString();
                    else if(attribute.name().toString() == "color") socketConnectionModel.color = QColor(attribute.value().toString());
                }
                result.socketConnectionModels.append(socketConnectionModel);
            }
            else
            {
                //Empty
            }
        }
    }

    file.close();

    if(xmlReader.hasError())
    {
        showXmlErrorMessage();
        return LoadResult(false, CircuitFileModel());
    }
    return LoadResult(true, result);
}

LoadResult CircuitFileOperator::load(QString filepath)
{
    this->filepath = filepath;
    return this->load();
}

bool CircuitFileOperator::save(CircuitFileModel circuitFileModel)
{
    QFile file(this->filepath);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        showSaveErrorMessage();
        return false;
    }

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);

    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("circuit");
    xmlWriter.writeAttribute("gridSpacing", QString::number(circuitFileModel.gridSpacing));
    xmlWriter.writeAttribute("showGrid", QString::number(circuitFileModel.showGrid));
    xmlWriter.writeAttribute("moveComponentsOnGrid", QString::number(circuitFileModel.moveComponentsOnGrid));

    Q_FOREACH(BlockModel blockModel, circuitFileModel.blockModels)
    {
        xmlWriter.writeStartElement("block");
        xmlWriter.writeAttribute("blockType", QString::number(blockModel.blockType));
        xmlWriter.writeAttribute("location", ToFromStringUtil::pointToString(blockModel.location));
        xmlWriter.writeAttribute("color", blockModel.color.name());
        xmlWriter.writeAttribute("inputSocketIds", ToFromStringUtil::listOfStringsToString(blockModel.inputSocketIds));
        xmlWriter.writeAttribute("outputSocketIds", ToFromStringUtil::listOfStringsToString(blockModel.outputSocketIds));
        xmlWriter.writeAttribute("additionalInputSocketIds", ToFromStringUtil::listOfStringsToString(blockModel.additionalInputSocketIds));
        xmlWriter.writeAttribute("parameters", blockModel.parameters);
        xmlWriter.writeAttribute("positionLocked", QString::number(blockModel.positionLocked));
        xmlWriter.writeEndElement();
    }

    Q_FOREACH(SocketConnectionModel socketConnectionModel, circuitFileModel.socketConnectionModels)
    {
        xmlWriter.writeStartElement("socketConnection");
        xmlWriter.writeAttribute("socketAId", socketConnectionModel.socketAId);
        xmlWriter.writeAttribute("socketBId", socketConnectionModel.socketBId);
        xmlWriter.writeAttribute("color", socketConnectionModel.color.name());
        xmlWriter.writeEndElement();
    }

    xmlWriter.writeEndElement();

    xmlWriter.writeEndDocument();

    file.close();

    if (file.error())
    {
        showSaveErrorMessage();
        return false;
    }

    return true;

}

bool CircuitFileOperator::save(CircuitFileModel circuitFileModel, QString filepath)
{
    this->filepath = filepath;
    return this->save(circuitFileModel);
}

void CircuitFileOperator::showSaveErrorMessage()
{
    QMessageBox::warning(0, tr("Saving Failed"),
                         tr("The Circuit could not be saved.\n"
                            "Please make sure the file is not used by another application and you have permissions to write in that directory."),
                         QMessageBox::Ok, QMessageBox::Ok);
}

void CircuitFileOperator::showLoadErrorMessage()
{
    QMessageBox::warning(0, tr("Loading Failed"),
                         tr("The Circuit could not be loaded.\n"
                            "Please make sure the file exists, it is not used by another application and you have permissions to read in that directory."),
                         QMessageBox::Ok, QMessageBox::Ok);
}

void CircuitFileOperator::showXmlErrorMessage()
{
    QMessageBox::critical(0, tr("Opening Failed:"), tr("The Circuit seems to be corrupted and will not be opened."),
                          QMessageBox::Ok, QMessageBox::Ok);
}
