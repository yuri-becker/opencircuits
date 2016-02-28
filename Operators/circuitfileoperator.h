/*
 *  circuitfileoperator.h: Saves and loads .circuit-files
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

#ifndef CIRCUITFILEOPERATOR_H
#define CIRCUITFILEOPERATOR_H

#include <QObject>
#include "Types/circuitfilemodel.h"

typedef QPair<bool, CircuitFileModel> LoadResult;

class CircuitFileOperator : public QObject
{
    Q_OBJECT
    public:

        CircuitFileOperator();

        QString filepath = "";

        LoadResult load();
        LoadResult load(QString filepath);
        bool save(CircuitFileModel circuitFileModel);
        bool save(CircuitFileModel circuitFileModel, QString filepath);

    private:
        void showSaveErrorMessage();
        void showLoadErrorMessage();
        void showXmlErrorMessage();
};

#endif // CIRCUITFILEOPERATOR_H
