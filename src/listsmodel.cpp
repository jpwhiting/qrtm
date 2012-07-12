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

#include "listsmodel.h"

#include "list.h"

#include <QtDebug>

namespace RTM {

class ListsModel::Private {
public:
    QList<List> lists;
};

ListsModel::ListsModel(QObject *parent) :
    QAbstractListModel(parent),
    d(new Private)
{
    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole] = "display";
    roles[IdRole] = "id";
    roles[FilterRole] = "filter";
    roles[SortOrderRole] = "sortorder";
    setRoleNames(roles);
}

const List &ListsModel::listFromId(const QString &id)
{
    Q_FOREACH(const List &list, d->lists)
    {
        if (list.id() == id)
        {
            qDebug() << "Got list with id " << id
                     << " name " << list.name()
                     << " and sort order " << list.sortOrder();
            return list;
        }
    }
}

void ListsModel::clear()
{
    beginResetModel();
    d->lists.clear();
    endResetModel();
}

int ListsModel::rowCount(const QModelIndex &index) const
{
    if (!index.isValid())
        return d->lists.size();
    return 0;
}

QVariant ListsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant retval;

    if (orientation == Qt::Horizontal && section == 0)
    {
        switch (role)
        {
        case Qt::DisplayRole:
            retval = "Lists";
            break;
        }
    }
    return retval;
}

QVariant ListsModel::data ( const QModelIndex & index, int role) const
{
    QVariant retval;

    if (index.isValid())
    {
        switch (role)
        {
        case Qt::DisplayRole:
            retval = d->lists.at(index.row()).name();
            break;
        case IdRole:
            retval = d->lists.at(index.row()).id();
            break;
        case FilterRole:
            retval = d->lists.at(index.row()).filter();
            break;
        case SortOrderRole:
            retval = d->lists.at(index.row()).sortOrder();
            break;
        }
    }

    return retval;
}

bool SortLists(const List &l1, const List &l2)
{
    if (l1.isSmart() == l2.isSmart())
    {
        if (l1.position() != l2.position())
            return l1.position() < l2.position();
        else
            return l1.name() < l2.name();
    }
    else
        // If l2 is smart, l1 goes first.
        return (l2.isSmart());
}

void ListsModel::onGetListFinished(QVariantMap response, ResponseStatus status)
{
    qDebug() << "Adding lists data to model";
    if (status == RTM::OK)
    {
        clear();

        QVariantList lists = response.value("lists").toMap().value("list").toList();
        beginInsertRows(QModelIndex(), 0, lists.size());
        qDebug() << "List items: " << lists.size();
        Q_FOREACH(const QVariant &info, lists)
        {
            QVariantMap data = info.toMap();
            List newInfo;
            newInfo.load(data);
            d->lists.append(newInfo);
            emit loadedListInfo(newInfo);
        }
        qSort(d->lists.begin(), d->lists.end(), SortLists);

        endInsertRows();
    }
}

}
