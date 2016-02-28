/*
 *  inputtextdialog.h: Generic dialog for getting a string from the user.
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

#ifndef INPUTTEXTDIALOG_H
#define INPUTTEXTDIALOG_H

#include <QDialog>

namespace Ui {
class InputTextDialog;
}

class InputTextDialog : public QDialog
{
    Q_OBJECT

    public:
        static QString getTextInput(QWidget *parent,QString caption, QString textHint, QString preEnteredText, QIcon windowIcon);

    private slots:
        void accepted();
        void rejected();
        void inputChanged(QString input);

    private:
        InputTextDialog(QWidget *parent = 0);

        Ui::InputTextDialog *ui;
        static QString result;
};

#endif // INPUTTEXTDIALOG_H
