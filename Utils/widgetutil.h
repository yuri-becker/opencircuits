/*
 * widgetutil.h: Helpful methods for working with QWidgets.
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

#ifndef WIDGETUTIL_H
#define WIDGETUTIL_H

#include <QWidget>

class WidgetUtil
{
    public:
        template<typename O>
        static O *getParentByType(QObject* object)
        {
            QObject* parent = object;
            while(parent->parent() != 0)
            {
                parent = parent->parent();

                O*  cast = qobject_cast<O*>(parent);
                if(cast != 0) { return cast; }
            }

            return 0;
        }

        static bool widgetIsOnPoint(QPoint point_global, QWidget* widget);

        template<typename P>
        static QList<P*> findChildrenSafe(QWidget* widget)
        {
            QList<P*> children;
            Q_FOREACH(QObject* uncastedChild, widget->findChildren<QObject*>())
            {
                P* castedChild = qobject_cast<P*>(uncastedChild);
                if(castedChild != 0)
                {
                    children.append(castedChild);
                }
            }

            return children;
        }

        static QMouseEvent* mapMouseEvent(QWidget* from, QWidget* to, QMouseEvent* originalEvent);
};

#endif // WIDGETUTIL_H
