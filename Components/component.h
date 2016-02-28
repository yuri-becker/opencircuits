/*
 *  component.h: QWidget that can be displayed in the ComponentArea.
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

#ifndef COMPONENT_H
#define COMPONENT_H

#include <QWidget>
#include <QColor>
#include <QMenu>

class Component : public QWidget
{
    Q_OBJECT

    public:
        Component(QWidget *parent, QPoint location, QSize size, QColor color = Qt::black);

        void setColor(QColor color);
        QColor getColor();

        bool isValid();

        void triggerEnterEvent();
        void triggerMouseMoveEvent(QMouseEvent* event);
        void triggerLeaveEvent();
        void triggerMousePressEvent(QMouseEvent* event);
        void triggerMouseReleaseEvent(QMouseEvent* event);

    public slots:
        void acceptPropertyChange(QString property, QString value);

    protected:
        //Subclass needs to take care of this flag itself, usually via implementing onEnter() and onLeave(), since components should declare their "active areas" themselfs (e.g. SocketConnection, triggerRects)
        bool active = false;

        QMenu contextMenu;

        virtual void onEnter() = 0;
        virtual void onMouseMove(QMouseEvent *event) = 0;
        virtual void onLeave() = 0;
        virtual void beforeMousePress(QMouseEvent* event) = 0;
        virtual void onMousePress(QMouseEvent* event) = 0;
        virtual void onMouseRelease(QMouseEvent* event) = 0;

        const QString property_component_color = "component.color";
        const QString property_component_removal = "component.removal"; //Has to be implemented in subclass's changeProperty()

    signals:
       void requestRepaint();
       void invalidated(Component* component);
       void colorChanged(Component* sender, QColor color);
       void requestPropertyChange(QString property, QString value);
       void incomingProperyChange(QString property, QString value); //Connect this signal with a changePropery-like slot in subclass

    protected slots:
       void invalidate();
       void enableContextMenu();
       void disableContextMenu();
       void requestRemoval(); //Makes the Object connected with requestPropertyChange()

    private slots:
        void repaintRequested();
        void showContextMenu(const QPoint& position);
        void changeProperty(QString property, QString value);

    private:
        QColor color;
        QWidget* parent;
        bool invalid = false;
        bool contextMenuEnabled = true;

};

#endif // COMPONENT_H
