/*
 *  mainwindow.cpp: Implementation of mainwindow.h
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

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Operators/circuitfileoperator.h"
#include "applicationproperties.h"

#include <QFileDialog>
#include <QDesktopServices>
#include "Ui/inputnumberdialog.h"
#include "Widgets/recentfileaction.h"
#include "componentinfovalues.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),  ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resetComponentArea();
    recentFilesOperator = new RecentFilesOperator();
    initEvents();

    refreshRecentFiles();
}

MainWindow::MainWindow(QStringList arguments, QWidget *parent) :
    MainWindow(parent)
{
    setupFromArguments(arguments);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initEvents()
{
    //Actions
    connect(ui->action_close, SIGNAL(triggered()),
            this, SLOT(close()));
    connect(ui->action_about, SIGNAL(triggered()),
            this, SLOT(openAboutDialog()));
    connect(ui->action_save, SIGNAL(triggered()),
            this, SLOT(saveComponentArea()));
    connect(ui->action_saveAs, SIGNAL(triggered()),
            this, SLOT(saveAsComponentArea()));
    connect(ui->action_open, SIGNAL(triggered()),
            this, SLOT(openOpenFileDialog()));
    connect(ui->action_newFile, SIGNAL(triggered()),
            this, SLOT(newFileTriggered()));
    connect(ui->action_showGrid, SIGNAL(triggered(bool)),
            ui->componentArea, SLOT(setShowGrid(bool)));
    connect(ui->action_adjustGrid, SIGNAL(triggered()),
            this, SLOT(openConfigureGridDialog()));
    connect(ui->action_moveComponentsOnGrid, SIGNAL(toggled(bool)),
            ui->componentArea, SLOT(setMoveComponentsOnGrid(bool)));
    connect(recentFilesOperator, SIGNAL(recentFilesChanged()),
            this, SLOT(refreshRecentFiles()));
    connect(ui->action_playpauseSim, SIGNAL(triggered(bool)),
            ui->componentArea, SLOT(playPauseSimulation(bool)));
    connect(ui->action_openWiki, SIGNAL(triggered(bool)),
            this, SLOT(openWiki()));

    //ComponentArea
    connect(ui->componentArea, SIGNAL(changed()),
            this, SLOT(markChangesInFile()));
    connect(ui->componentArea, SIGNAL(saved()),
            this, SLOT(unmarkChangesInFile()));
    connect(ui->componentArea, SIGNAL(blockMoved(QWidget*,QPoint)),
            ui->scrollArea, SLOT(checkForEdgeScroll(QWidget*,QPoint)));
    connect(ui->componentArea, SIGNAL(middleMouseDragged(int,int)),
            ui->scrollArea, SLOT(scrollContent(int,int)));
    connect(ui->componentArea, SIGNAL(simStarted()),
            ui->catalogAndInfoDisplay, SLOT(hide()));
    connect(ui->componentArea, SIGNAL(simStopped()),
            ui->catalogAndInfoDisplay, SLOT(show()));
    connect(ui->componentArea, SIGNAL(simStopped()),
            this, SLOT(simulationStopped()));
    connect(ui->componentArea, SIGNAL(simStarted()),
            this, SLOT(simulationStarted()));

    //StatusBar
    connect(ui->componentArea, SIGNAL(displayMessageOnStatusbar(QString,QColor, int)),
            ui->statusbar, SLOT(showMessageAndChangeColor(QString,QColor, int)));
    connect(ui->componentArea, SIGNAL(blocksCountChanged(int)),
            ui->statusbar, SLOT(updateBlocksCount(int)));
    connect(ui->componentArea, SIGNAL(socketConnectionsCountChanged(int)),
            ui->statusbar, SLOT(updateSocketConnectionsCount(int)));

    connect(ui->blockCatalog, SIGNAL(catalogBlock_whatIsThisTriggered(int)),
            this, SLOT(openComponentInfo(int)));
}

void MainWindow::setupFromArguments(QStringList arguments)
{
    if(arguments.count() > 1)
    {
        QString file = arguments.at(1);

        if(QFile(file).exists())
        {
            loadFile(file);
        }
        else
        {
            QMessageBox::warning(this, tr("Could not open Circuit"), file.append(tr(" does not exist.")), QMessageBox::Ok);
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(fileChanged)
    {
        QMessageBox::StandardButton res = unsavedChanges();

        if(res == QMessageBox::Yes)
        {
            if(saveComponentArea())
            {
                event->accept();
            }
            else
            {
                event->ignore();
            }
        }
        else if (res == QMessageBox::No)
        {
            event->accept();
        }
        else if (res == QMessageBox::Cancel)
        {
            event->ignore();
        }

    }
}

void MainWindow::openComponentInfo(int blockType)
{
    QDesktopServices::openUrl(ComponentInfoValues::getComponentInfo(blockType).wikiUrl);
}

void MainWindow::openWiki()
{
    QDesktopServices::openUrl(ApplicationProperties::link_wikiHome);
}

void MainWindow::openAboutDialog()
{
    (new AboutDialog(this))->exec();
}

bool MainWindow::saveComponentArea()
{
    if(currentCircuitDir == "")
    {
        return saveAsComponentArea();
    }
    else
    {
        this->ui->componentArea->saveArea(currentCircuitDir);
        return true;
    }
    recentFilesOperator->addAndSave(currentCircuitDir);
}

bool MainWindow::saveAsComponentArea()
{
    QString file = QFileDialog::getSaveFileName(
                this,
                tr("Save Circuit"),
                QDir::homePath(),
                "Circuits (*.circuit);",
                0 );

    if(!file.isNull())
    {
        this->ui->componentArea->saveArea(file);
        changeFilenameInCaption(file);
        currentCircuitDir = file;
        recentFilesOperator->addAndSave(currentCircuitDir);
        return true;
    }
    else
    {
        return false;
    }
}

void MainWindow::newFileTriggered()
{
    if(fileChanged)
    {
        QMessageBox::StandardButton res = unsavedChanges();

        if(res == QMessageBox::Yes)
        {
            if(saveComponentArea())
            {
                resetComponentArea();
            }
            else
            {
                //Do Nothing (save failed or dialog was closed)
            }
        }
        else if(res == QMessageBox::No)
        {
            resetComponentArea();
        }
        else
        {
            //Do nothing
        }
    }
    else
    {
        resetComponentArea();
    }
}

void MainWindow::resetComponentArea()
{
    currentCircuitDir = "";
    changeFilenameInCaption(tr("New Circuit"));
    ui->componentArea->loadArea(CircuitFileModel());
}

void MainWindow::simulationStarted()
{
    ui->action_playpauseSim->setChecked(true);
}

void MainWindow::simulationStopped()
{
    ui->action_playpauseSim->setChecked(false);
}

void MainWindow::openOpenFileDialog()
{
    QString file = QFileDialog::getOpenFileName(
                this,
                tr("Open Circuit"),
                QDir::homePath(),
                "Circuits (*.circuit)",
                0 );
    if(!file.isNull())
    {
        loadFile(file);
    }
}

void MainWindow::openConfigureGridDialog()
{
    int input = InputNumberDialog::getNumberInput(
                this,
                tr("Configure Grid"),
                tr("Spacing: "),
                QIcon(":/images/Resources/GenericIcons/grid-48.png"),
                ui->componentArea->getGridSpacing(),
                5,
                500,
                5,
                " px");

    if(input != -1)
    {
        ui->componentArea->setGridSpacing(input);
    }
}

void MainWindow::changeFilenameInCaption(QString filename)
{
    this->setWindowTitle(filename + " - " + ApplicationProperties::name);
}

void MainWindow::clearComponentAreaAndClose()
{
    this->ui->componentArea->clear();
    this->close();
}

void MainWindow::markChangesInFile()
{
    fileChanged = true;
    if(!this->windowTitle().contains("*"))
    {
        this->setWindowTitle(QString("*" + this->windowTitle()));
    }
}

void MainWindow::unmarkChangesInFile()
{
    fileChanged = false;
    this->setWindowTitle(this->windowTitle().replace("*", ""));
}

void MainWindow::refreshRecentFiles()
{
    QMenu *recentFilesSubMenu = new QMenu();
    Q_FOREACH(QString recentFile, recentFilesOperator->getRecentFiles())
    {
        RecentFileAction* recentFileAction = new RecentFileAction(recentFile);
        recentFileAction->setIconVisibleInMenu(false);
        connect(recentFileAction, SIGNAL(triggered(QString)), this, SLOT(loadFile(QString)));
        recentFilesSubMenu->addAction(recentFileAction);
    }
    recentFilesSubMenu->addSeparator();
    {
        QIcon icon;
        icon.addFile(":/images/Resources/GenericIcons/delete_sign_48px.png");

        QAction* clearAction = new QAction(icon, tr("Clear"), 0);
        clearAction->setIconVisibleInMenu(true);
        connect(clearAction, SIGNAL(triggered(bool)), recentFilesOperator, SLOT(clear()));
        recentFilesSubMenu->addAction(clearAction);
    }

    ui->action_recentFiles->setMenu(recentFilesSubMenu);
}

QMessageBox::StandardButton MainWindow::unsavedChanges()
{
    return QMessageBox::warning(this, ApplicationProperties::name,
        tr("Save changes? Your changes will be lost if you don't save them."),
        QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
        QMessageBox::Yes);
}

void MainWindow::loadFile(QString file)
{
    if(fileChanged)
    {
        QMessageBox::StandardButton res = unsavedChanges();

        if(res == QMessageBox::Yes)
        {
            saveComponentArea();
        }
        else if(res == QMessageBox::No)
        {
            //Do nothing
        }
        else if(res == QMessageBox::Cancel)
        {
            return;
        }
    }
    CircuitFileOperator* circuitFileOperator = new CircuitFileOperator();
    LoadResult loadResult = circuitFileOperator->load(file);
    if(loadResult.first) //Load was successful
    {
        CircuitFileModel circuitFileModel = loadResult.second;
        ui->componentArea->loadArea(circuitFileModel);
        changeFilenameInCaption(file);
        currentCircuitDir = file;
        recentFilesOperator->addAndSave(currentCircuitDir);
    }

}
