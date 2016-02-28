/*
 *  componentinfodisplay: Displays a ComponentInfo - Deprecated since ComponentInfos are now shown
 *  in the wiki.
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

#ifndef COMPONENTINFODISPLAY_H
#define COMPONENTINFODISPLAY_H

#include <QFrame>
#include "Types/componentinfo.h"
#include <QLabel>
#include <QGridLayout>

class ComponentInfoDisplay : public QFrame
{
    Q_OBJECT
    public:
        ComponentInfoDisplay(QWidget* parent = 0);

    signals:
        void hideRequested();

    public slots:
        void showComponentInfo(int targetBlockType);
        void showComponentInfo(ComponentInfo componentInfo);

    private:
        QLabel* label;
        QWidget* showcaseBlockContainer;
        QGridLayout* showcaseBlockContainerLayout;

        void initWidget();

    private slots:
        void requestHide() { emit hideRequested(); }


};

#endif // COMPONENTINFODISPLAY_H
