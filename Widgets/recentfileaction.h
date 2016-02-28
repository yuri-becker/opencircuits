/*
 *  recentfileaction.h: Action the the recent files submenu.
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

#ifndef RECENTFILEACTION_H
#define RECENTFILEACTION_H

#include <QAction>

class RecentFileAction : public QAction
{
    Q_OBJECT
    public:
        RecentFileAction(QString file, QWidget *parent = 0);

    signals:
        void triggered(QString file);

    private:
        QString file;

    private slots:
        void fireTriggered();
};

#endif // RECENTFILEACTION_H
