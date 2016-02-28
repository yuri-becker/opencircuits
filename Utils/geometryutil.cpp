/*
 *  geometryutil.cpp: Implementation of geometryutil.h
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

#include "geometryutil.h"

QVector<QPoint> GeometryUtil::pointPairsFromSinglePoints(QVector<QPoint> singlePoints)
{
    QVector<QPoint> pointPairs;
    pointPairs.append(singlePoints.at(0));
    for(int i = 1; i < singlePoints.size() -1; i++)
    {
        pointPairs.append(singlePoints.at(i));
        pointPairs.append(singlePoints.at(i));
    }
    pointPairs.append(singlePoints.at(singlePoints.size() -1));
    return pointPairs;
}

bool GeometryUtil::rectsContain(QVector<QRect> rects, QPoint point)
{
    bool contains = false;
    Q_FOREACH(QRect rect, rects)
    {
        if(rect.contains(point)) contains = true;
    }
    return contains;
}

bool GeometryUtil::rectsContain(QVector<QRect> rects, int x, int y)
{
    return rectsContain(rects, QPoint(x,y));
}
