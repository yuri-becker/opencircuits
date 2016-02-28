/*
 *  inputnumberdialog.h: Generic dialog for getting an integer value from the user.
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

#ifndef INPUTNUMBERDIALOG_H
#define INPUTNUMBERDIALOG_H

#include <QDialog>

namespace Ui {
class inputnumberdialog;
}

class InputNumberDialog : public QDialog
{
    Q_OBJECT

    public:
        static int getNumberInput(QWidget* parent, QString caption, QString textHint, QIcon windowIcon, int preEnteredNum, int min, int max, int delta = 1, QString suffix = "");

    private slots:
        void accepted();
        void rejected();
        void inputChanged(int input);

    private:
        InputNumberDialog(QWidget *parent = 0);

        Ui::inputnumberdialog *ui;

    private:
        static int result;
};

#endif // INPUTNUMBERDIALOG_H
