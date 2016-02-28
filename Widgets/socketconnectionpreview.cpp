/*
 *  socketconnectionpreview.cpp:Implementation of socketconnectionpreview.h
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

#include "socketconnectionpreview.h"

#include <QPainter>
#include <QMouseEvent>

SocketConnectionPreview::SocketConnectionPreview(QWidget *parent) : QWidget(parent)
{
    QColor palcl = QColor(Qt::transparent);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Base, palcl);
    palette.setColor(QPalette::Window, palcl);
    palette.setColor(QPalette::AlternateBase, palcl);
    setPalette(palette);

    setAttribute(Qt::WA_TransparentForMouseEvents, true);
    connect(this, SIGNAL(requestRepaint()), this, SLOT(repaint()));
}

void SocketConnectionPreview::update(QPoint pos1_global, QPoint pos2_global)
{
    setFixedSize(1,1);
    move(10,10);
    this->pos1_global = pos1_global;
    this->pos2_global = pos2_global;

    emit requestRepaint();
}

void SocketConnectionPreview::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    //Determine Position
    QPoint pos_global;
    if(pos1_global.x() <= pos2_global.x())      pos_global.setX(pos1_global.x());
    else                                                                pos_global.setX(pos2_global.x());

    if(pos1_global.y() <= pos2_global.y())      pos_global.setY(pos1_global.y());
    else                                                                pos_global.setY(pos2_global.y());

    move(parentWidget()->mapFromGlobal(pos_global));

    //Determine Size
    QSize size;
    size.setWidth( (int)fmax((double)pos1_global.x(), (double) pos2_global.x()) - (int)fmin((double)pos1_global.x(), (double) pos2_global.x()));
    size.setHeight( (int)fmax((double)pos1_global.y(), (double) pos2_global.y()) - (int)fmin( (double)pos1_global.y(), (double) pos2_global.y())  );
    setFixedSize(size);

    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap));
    painter.drawLine(mapFromGlobal(pos1_global), mapFromGlobal(pos2_global));
}
