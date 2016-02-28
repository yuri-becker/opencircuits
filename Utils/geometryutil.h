/*
 *  geometryutil.h: Maybe helpful methods for working with QPoints, QRects, QPolygons and stuff.
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

#ifndef QPOINTUTIL_H
#define QPOINTUTIL_H

#include <QVector>
#include <QPoint>
#include <QPolygon>

class GeometryUtil
{
    public:
        static QVector<QPoint> pointPairsFromSinglePoints(QVector<QPoint> singlePoints);
        static bool rectsContain(QVector<QRect> rects, QPoint point);
        static bool rectsContain(QVector<QRect> rects, int x, int y);
};

#endif // QPOINTUTIL_H
