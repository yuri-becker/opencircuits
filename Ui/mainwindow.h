/*
 *  mainwindow.h: The Main Window
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include <QMessageBox>

#include "Components/abstractsocket.h"
#include "Widgets/componentarea.h"
#include "Ui/aboutdialog.h"
#include "Operators/recentfilesoperator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        explicit MainWindow(QStringList arguments, QWidget* parent = 0);
        ~MainWindow();

    private:
        void initEvents();
        void setupFromArguments(QStringList arguments);
        void closeEvent(QCloseEvent* event);

        QString currentCircuitDir = "";
        bool fileChanged = false;

        Ui::MainWindow *ui;
        RecentFilesOperator* recentFilesOperator;

    private slots:
        void openComponentInfo(int blockType);
        void openWiki();
        //Actions
        void openAboutDialog();
        bool saveComponentArea();
        bool saveAsComponentArea();
        void openOpenFileDialog();
        void openConfigureGridDialog();
        void newFileTriggered();
        //ComponentArea
        void clearComponentAreaAndClose();
        void resetComponentArea();
        void simulationStarted();
        void simulationStopped();
        //Files
        void loadFile(QString file);
        void changeFilenameInCaption(QString filename);
        void markChangesInFile();
        void unmarkChangesInFile();
        //RecentFiles
        void refreshRecentFiles();
        //Messages
        QMessageBox::StandardButton unsavedChanges();
};

#endif // MAINWINDOW_H
