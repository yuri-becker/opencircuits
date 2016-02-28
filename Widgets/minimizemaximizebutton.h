/*
 *  minimizemaximizebutton.h: Button which handles minimizing and maximizing of a non-modal widget. Actually works nice!
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

#ifndef MINIMIZEMAXIMIZEBUTTON_H
#define MINIMIZEMAXIMIZEBUTTON_H

#include <QToolButton>

class MinimizeMaximizeButton : public QToolButton
{
    Q_OBJECT
    public:
        MinimizeMaximizeButton(QWidget* parent = 0);

    public slots:
        void triggerMaximize();
        void triggerMinimize();

    signals:
        void maximizeTriggered();
        void minimizeTriggered();

    private:
        bool maximized = false;
        void initWidget();

        QIcon minimizeIcon;
        QIcon maximizeIcon;

    private slots:
        void minimizeMaximize();
};

#endif // MINIMIZEMAXIMIZEBUTTON_H
