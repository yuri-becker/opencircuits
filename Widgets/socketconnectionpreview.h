/*
 *  socketconnectionpreview.h: Basically a line which connnects two given points.
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

#ifndef SOCKETCONNECTIONPREVIEW_H
#define SOCKETCONNECTIONPREVIEW_H

#include <QWidget>

class SocketConnectionPreview : public QWidget
{
    Q_OBJECT
    public:
        SocketConnectionPreview(QWidget *parent = 0);

    signals:
        void requestRepaint();

    public slots:
        void update(QPoint pos1_global, QPoint pos2_global);

    private:
        QPoint pos1_global = QPoint(0,0);
        QPoint pos2_global = QPoint(0,0);

        void paintEvent(QPaintEvent *event);
};

#endif // SOCKETCONNECTIONPREVIEW_H
