/*
 *  component.cpp: Implementation of component.h
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

#include <Components/component.h>

#include <Widgets/componentarea.h>

#include <QMouseEvent>

Component::Component(QWidget *parent, QPoint location, QSize size, QColor color) : QWidget(parent)
{
    QColor palcl = QColor(Qt::transparent);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Base, palcl);
    palette.setColor(QPalette::Window, palcl);
    palette.setColor(QPalette::AlternateBase, palcl);
    this->setPalette(palette);

    connect(this, SIGNAL(requestRepaint()), this, SLOT(repaintRequested()));
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu(const QPoint&)));
    connect(this, SIGNAL(destroyed(QObject*)), this, SLOT(invalidate()));
    connect(this, SIGNAL(incomingProperyChange(QString,QString)), this, SLOT(changeProperty(QString,QString)));
    setAttribute(Qt::WA_TransparentForMouseEvents);
    this->parent = parent;
    this->move(location);
    this->setFixedSize(size);
    this->color = color;
}

void Component::setColor(QColor color)
{
    this->color = color;
    foreach(QObject *child, this->children())
    {
        ((Component*)child)->setColor(color);
    }
    emit requestRepaint();
}

QColor Component::getColor()
{
    return this->color;
}

bool Component::isValid()
{
    return !invalid;
}

void Component::triggerEnterEvent()
{
    onEnter();
}

void Component::triggerMouseMoveEvent(QMouseEvent *event)
{
    onMouseMove(event);
}

void Component::triggerLeaveEvent()
{
    onLeave();
}

void Component::triggerMousePressEvent(QMouseEvent *event)
{
    beforeMousePress(event);
    onMousePress(event);
}

void Component::triggerMouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        showContextMenu(event->pos());
    }
    onMouseRelease(event);
}

void Component::acceptPropertyChange(QString property, QString value)
{
    emit incomingProperyChange(property, value);
}

void Component::repaintRequested()
{
    this->repaint();
}

void Component::showContextMenu(const QPoint &position)
{
    if(contextMenuEnabled && active)
    {
        contextMenu.exec(this->mapToGlobal(position), 0);
    }
}

void Component::invalidate()
{
    invalid = true;
    emit invalidated(this);
}

void Component::enableContextMenu()
{
    contextMenuEnabled = true;
}

void Component::disableContextMenu()
{
    contextMenuEnabled = false;
}

void Component::changeProperty(QString property, QString value)
{
    if(property == property_component_color) setColor(QColor(value));
}

void Component::requestRemoval()
{
    emit requestPropertyChange(property_component_removal, "1");
}
