/*
 *  catalogblock.h:
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

#ifndef CATALOGBLOCK_H
#define CATALOGBLOCK_H

#include <QWidget>
#include <QMenu>

class CatalogBlock : public QWidget
{
    Q_OBJECT

    public:
        CatalogBlock(int targetBlockType, QObject* targetComponentAreasParent, QWidget *parent = 0);
        int targetBlockType;
        QObject* targetComponentAreasParent;

    private slots:
        void showContextMenu(const QPoint& postition);

    protected:
        QMenu contextMenu;

    signals:
       void requestRepaint();
       void contextMenu_whatIsThis_triggered(int targetBlockType);

    private slots:
        void repaintRequested();
        void pass_contextMenu_whatIsThis_triggered() { emit contextMenu_whatIsThis_triggered(targetBlockType); }

    private:
        QPoint dragBeginPos;

        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void paintEvent(QPaintEvent *event);

        void initContextMenu();

};

#endif // CATALOGBLOCK_H
