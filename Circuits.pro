#-------------------------------------------------
# Circuits.pro: Qt-Profile
#
# Copyright (C) 2015-2016 Yuri Becker <hi@yuri.li>
#
# This file is part of OpenCircuits.
#
# OpenCircuits is free software: you can redistribute it and/or modify it under the terms
# of the GNU Lesser General Public License as published by the Free Software Foundation,
# either version 3 of the License, or (at your option) any later version.
#
# OpenCircuits is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
# without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
# PURPOSE.  See the GNU  Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License along with
# OpenCircuits. If not, see <http://www.gnu.org/licenses/>.
 #-------------------------------------------------
#
# Project created by QtCreator 2015-03-02T11:31:03
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenCircuits
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
    Components/component.cpp \
    Ui/mainwindow.cpp \
    Components/componentwithcolorcontextmenu.cpp \
    Widgets/componentarea.cpp \
    Components/socketconnection.cpp \
    Components/Blocks/sourceblock.cpp \
    Components/Blocks/ledblock.cpp \
    Types/circuitfilemodel.cpp \
    Types/blockmodel.cpp \
    Types/socketconnectionmodel.cpp \
    Ui/aboutdialog.cpp \
    applicationproperties.cpp \
    Operators/circuitfileoperator.cpp \
    Utils/tofromstringutil.cpp \
    Components/Blocks/andgateblock.cpp \
    Components/Blocks/orgateblock.cpp \
    Components/Blocks/notgateblock.cpp \
    Components/Blocks/nandgateblock.cpp \
    Components/Blocks/norgateblock.cpp \
    Components/Blocks/xorgateblock.cpp \
    Components/Blocks/xnorgateblock.cpp \
    Widgets/blockcatalog.cpp \
    Components/catalogblock.cpp \
    Components/Blocks/labelblock.cpp \
    Ui/inputtextdialog.cpp \
    Ui/inputnumberdialog.cpp \
    Components/Blocks/splitterblock.cpp \
    Components/Blocks/squarefunctiongeneratorblock.cpp \
    Widgets/showcaseblock.cpp \
    Types/componentinfo.cpp \
    componentinfovalues.cpp \
    Utils/widgetutil.cpp \
    Components/Blocks/abstractinteractiveblock.cpp \
    Components/abstractblock.cpp \
    Components/Blocks/abstractinstantrespondingblock.cpp \
    Components/Blocks/pushbuttonblock.cpp \
    Components/Blocks/switchblock.cpp \
    Components/Blocks/errorblock.cpp \
    Widgets/scrollareawithedgescrollingandexpanding.cpp \
    Components/Sockets/outputsocket.cpp \
    Components/abstractsocket.cpp \
    Components/Sockets/inputsocket.cpp \
    Widgets/socketconnectionpreview.cpp \
    Widgets/circuitsstatusbar.cpp \
    Widgets/componentinfodisplay.cpp \
    Widgets/minimizemaximizebutton.cpp \
    Operators/recentfilesoperator.cpp \
    Widgets/recentfileaction.cpp \
    Widgets/blockcatalogpage.cpp \
    Utils/geometryutil.cpp \
    Components/Blocks/srnorlatchblock.cpp \
    Components/Blocks/tflipflopblock.cpp \
    Components/Blocks/jkflipflopblock.cpp \
    Utils/stringutil.cpp \
    Components/Blocks/multiplexerblock.cpp \
    Components/Sockets/additionalinputsocket.cpp \
    Components/Blocks/demultiplexerblock.cpp \
    Components/Blocks/gatedsrnorlatchblock.cpp \
    Components/Blocks/gatedjkflipflopblock.cpp

HEADERS  += \
    Components/component.h \
    Ui/mainwindow.h \
    Components/componentwithcolorcontextmenu.h \
    Widgets/componentarea.h \
    Components/socketconnection.h \
    Components/Blocks/sourceblock.h \
    Components/Blocks/ledblock.h \
    Types/circuitfilemodel.h \
    Types/blockmodel.h \
    Types/socketconnectionmodel.h \
    Ui/aboutdialog.h \
    applicationproperties.h \
    Operators/circuitfileoperator.h \
    Utils/tofromstringutil.h \
    Components/Blocks/andgateblock.h \
    Components/Blocks/orgateblock.h \
    Components/Blocks/notgateblock.h \
    Components/Blocks/nandgateblock.h \
    Components/Blocks/norgateblock.h \
    Components/Blocks/xorgateblock.h \
    Components/Blocks/xnorgateblock.h \
    Widgets/blockcatalog.h \
    Components/catalogblock.h \
    Components/Blocks/labelblock.h \
    Ui/inputtextdialog.h \
    Ui/inputnumberdialog.h \
    Components/Blocks/splitterblock.h \
    Components/Blocks/squarefunctiongeneratorblock.h \
    Widgets/showcaseblock.h \
    Types/componentinfo.h \
    componentinfovalues.h \
    Utils/widgetutil.h \
    Components/Blocks/abstractinteractiveblock.h \
    Components/abstractblock.h \
    Components/Blocks/abstractinstantrespondingblock.h \
    Components/Blocks/pushbuttonblock.h \
    Components/Blocks/switchblock.h \
    Components/Blocks/errorblock.h \
    Widgets/scrollareawithedgescrollingandexpanding.h \
    Components/Sockets/outputsocket.h \
    Components/abstractsocket.h \
    Components/Sockets/inputsocket.h \
    Widgets/socketconnectionpreview.h \
    Widgets/circuitsstatusbar.h \
    Widgets/componentinfodisplay.h \
    Widgets/minimizemaximizebutton.h \
    Operators/recentfilesoperator.h \
    Widgets/recentfileaction.h \
    Widgets/blockcatalogpage.h \
    Utils/geometryutil.h \
    Components/Blocks/srnorlatchblock.h \
    Components/Blocks/tflipflopblock.h \
    Components/Blocks/jkflipflopblock.h \
    Utils/stringutil.h \
    Components/Blocks/multiplexerblock.h \
    Components/Sockets/additionalinputsocket.h \
    Components/Blocks/demultiplexerblock.h \
    Components/Blocks/gatedsrnorlatchblock.h \
    Components/Blocks/gatedjkflipflopblock.h

FORMS    += \
    Ui/mainwindow.ui \
    Ui/aboutdialog.ui \
    Ui/inputtextdialog.ui \
    Ui/inputnumberdialog.ui \
    Ui/componentinfodialog.ui

RESOURCES += \
    resources.qrc

DISTFILES += \
    Bugs.txt \
    NewBlockGuideline.txt

RC_FILE = Circuits.rc
