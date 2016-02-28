/*
 *  aboutdialog.cpp: Implementation of aboutdialog.h
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

#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include "applicationproperties.h"
#include <QGraphicsPixmapItem>

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    setWindowTitle(tr("About ") + ApplicationProperties::name);
    ui->nameLabel->setText(ApplicationProperties::name);
    ui->verLabel->setText(tr("Version ").append(ApplicationProperties::version));
    ui->usedLibrariesLabel->setText(tr("OpenCircuits uses").append(" <a href=\"").append(ApplicationProperties::link_qt).append("\">Qt</a> and <a href=\"").append(ApplicationProperties::link_icons8).append("\">Graphics by Icons8</a>."));
    ui->copyrightLabel->setText(ui->copyrightLabel->text().replace("<year>", ApplicationProperties::copyrightYear));
    ui->gitHubRepoLabel->setText(QString("<a href=\"").append(ApplicationProperties::link_githubRepo).append("\">").append(tr("Download Source from GitHub")).append("</a>"));

    setWindowFlags(Qt::Dialog);
    setWindowFlags(this->windowFlags() ^ Qt::WindowContextHelpButtonHint);

    adjustSize();
    setFixedSize(size());
    ui->lgplInfoContainer->adjustSize();
    ui->lgplInfoLabel->adjustSize();
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
