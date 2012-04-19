/*
 *  Copyright (C) 2012  Jeremy Whiting <jpwhiting@kde.org>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>

 */

#include "list.h"
#include <QSharedData>

#include <QtDebug>

namespace RTM {

class List::Private {
public:
    QString id;
    QString name;
    bool deleted;
    bool locked;
    bool archived;
    int position; // Possible values: -1, 0, 1
    bool smart;
    List::SortOrder sortOrder;
    QString filter;
};

List::List() : d(new Private)
{
}

List::List(const List &rhs)
    :d(new Private)
{
    d->id = rhs.d->id;
    d->name = rhs.d->name;
    d->deleted = rhs.d->deleted;
    d->locked = rhs.d->locked;
    d->archived = rhs.d->archived;
    d->position = rhs.d->position;
    d->smart = rhs.d->smart;
    d->filter = rhs.d->filter;
    d->sortOrder = rhs.d->sortOrder;
}

List &List::operator=(const List &rhs)
{
    if (this != &rhs)
    {
        d->id = rhs.d->id;
        d->name = rhs.d->name;
        d->deleted = rhs.d->deleted;
        d->locked = rhs.d->locked;
        d->archived = rhs.d->archived;
        d->position = rhs.d->position;
        d->smart = rhs.d->smart;
        d->filter = rhs.d->filter;
        d->sortOrder = rhs.d->sortOrder;
    }
    return *this;
}

List::~List()
{
    delete d;
}

QString List::name() const
{
    return d->name;
}

QString List::id() const
{
    return d->id;
}

int List::position() const
{
    return d->position;
}

bool List::isSmart() const
{
    return d->smart;
}

QString List::filter() const
{
    return d->filter;
}

List::SortOrder List::sortOrder() const
{
    return d->sortOrder;
}

void List::load(const QVariantMap &data)
{
    d->id        = data.value("id").toString();
    d->name      = data.value("name").toString();
    d->deleted   = data.value("deleted").toBool();
    d->locked    = data.value("locked").toBool();
    d->archived  = data.value("archived").toBool();
    d->position  = data.value("position").toInt();
    d->smart     = data.value("smart").toBool();
    d->sortOrder = List::SortOrder(data.value("sort_order").toInt());
    qDebug() << "Sort order for list with name " << d->name
             << " is " << d->sortOrder << " data " << data.value("sort_order").toString();
    d->filter    = data.value("filter").toString();
}

}
