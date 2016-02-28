/*
 *  inputtextdialog.cpp: Implementation of inputtextdialog.h
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

#include "inputtextdialog.h"
#include "ui_inputtextdialog.h"

QString InputTextDialog::result = "";

QString InputTextDialog::getTextInput(QWidget* parent, QString caption, QString textHint, QString preEnteredText, QIcon windowIcon)
{
    InputTextDialog* textDialog = new InputTextDialog(parent);
    textDialog->setWindowTitle(caption);
    textDialog->ui->label->setText(textHint);
    textDialog->ui->lineEdit->setText(preEnteredText);
    textDialog->setWindowIcon(windowIcon);
    textDialog->exec();
    return result;
}

InputTextDialog::InputTextDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputTextDialog)
{
    result = "";
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accepted()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(rejected()));
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(inputChanged(QString)));
    setWindowFlags(Qt::Dialog);
    setWindowFlags(this->windowFlags() ^ Qt::WindowContextHelpButtonHint);
}

void InputTextDialog::accepted()
{
    this->result = ui->lineEdit->text();
    this->close();
}

void InputTextDialog::rejected()
{
    this->result = "";
    this->close();
}

void InputTextDialog::inputChanged(QString input)
{
    if(input == "")
    {
        ui->buttonBox->setEnabled(false);
        result = input;
    }
    else
    {
        ui->buttonBox->setEnabled(true);
        result = input;
    }
}

