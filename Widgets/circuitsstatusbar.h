/*
 *  circuitsstatusbar.h: Statusbar for displaying information received from the ComponentArea.
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

#ifndef CIRCUITSSTATUSBAR_H
#define  CIRCUITSSTATUSBAR_H

#include <QStatusBar>
#include <QLabel>

class CircuitsStatusBar : public QStatusBar
{
    Q_OBJECT
    public:
        CircuitsStatusBar(QWidget* parent);

    public slots:
        void showMessageAndChangeColor(QString message, QColor color = Qt::black, int timeout = 0);
        void updateBlocksCount(int blocksCount);
        void updateSocketConnectionsCount(int socketConnectionsCount);

    private:
        QLabel* blocksCountLabel;
        QLabel* socketConnectionsCountLabel;

        void initUi();
};

#endif //  CIRCUITSSTATUSBAR_H
