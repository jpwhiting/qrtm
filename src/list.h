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

#ifndef LIST_H
#define LIST_H

#include <QVariantMap>

namespace RTM {

class List
{
public:
    enum SortOrder {
        ByPriority,
        ByDueDate,
        ByName
    };

    List();
    List(const List &);
    List &operator=(const List &);
    ~List();

    QString name() const;
    QString id() const;
    int position() const;
    bool isSmart() const;
    QString filter() const;
    SortOrder sortOrder() const;

    void load(const QVariantMap &data);

private:
    class Private;
    Private *const d;
};

}

#endif // LIST_H
