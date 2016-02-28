/*
 *  inputnumberdialog.cpp: Implementation of inputnumberdialog.h
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

#include "inputnumberdialog.h"
#include "ui_inputnumberdialog.h"

int InputNumberDialog::result = -1;

int InputNumberDialog::getNumberInput(QWidget* parent, QString caption, QString textHint, QIcon windowIcon, int preEnteredNum, int min, int max, int singleStep, QString suffix)
{
    InputNumberDialog* numberDialog = new InputNumberDialog(parent);
    numberDialog->setWindowTitle(caption);
    numberDialog->ui->spinBox->setMinimum(min);
    numberDialog->ui->spinBox->setMaximum(max);
    numberDialog->ui->spinBox->setSingleStep(singleStep);
    numberDialog->ui->spinBox->setSuffix(suffix);
    numberDialog->ui->spinBox->setValue(preEnteredNum);
    numberDialog->ui->label->setText(textHint);
    numberDialog->setWindowIcon(windowIcon);
    numberDialog->exec();
    return result;
}

InputNumberDialog::InputNumberDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inputnumberdialog)
{
    result = -1;
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accepted()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(rejected()));
    connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(inputChanged(int)));
    setWindowFlags(Qt::Dialog);
    setWindowFlags(this->windowFlags() ^ Qt::WindowContextHelpButtonHint);
}

void InputNumberDialog::accepted()
{
    this->result = ui->spinBox->value();
    this->close();
}

void InputNumberDialog::rejected()
{
    this->result = -1;
    this->close();
}

void InputNumberDialog::inputChanged(int input)
{
    if(input == -1)
    {
        ui->buttonBox->setEnabled(false);
        result = -1;
    }
    else
    {
        ui->buttonBox->setEnabled(true);
        result = input;
    }
}
