/*
 *  componentinfodialog.h: Deprecated dialog for displaying a ComponentInfo.
 * An instance of the non-modal ComponentInfoDisplay is in the MainWindow.
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

#ifndef COMPONENTINFODIALOG_H
#define COMPONENTINFODIALOG_H

#include <QDialog>

#include "Widgets/showcaseblock.h"

namespace Ui {
class ComponentInfoDialog;
}

class ComponentInfoDialog : public QDialog
{
    Q_OBJECT

    public:
        ComponentInfoDialog(int targetBlockType, QWidget *parent = 0);

    private:
        Ui::ComponentInfoDialog *ui;
        int targetBlockType;
};

#endif // COMPONENTINFODIALOG_H
