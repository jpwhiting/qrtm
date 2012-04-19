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

#include "tasksmodel.h"

#include "task.h"

#include <QDateTime>
#include <QStringList>

namespace RTM {

class TasksModel::Private {
public:
    QList<Task> tasks;
};

TasksModel::TasksModel(QObject *parent) :
    QAbstractListModel(parent),
    d(new Private)
{
    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole] = "display";
    roles[PriorityRole] = "priority";
    roles[ListIdRole] = "listid";
    roles[CompletedRole] = "completed";
    roles[DueDateRole] = "duedate";
    roles[TagsRole] = "tags";
    roles[NotesRole] = "notes";
    roles[LocationRole] = "location";
    roles[UrlRole] = "url";
    setRoleNames(roles);
}

void TasksModel::addTask(const Task &task)
{
    beginInsertRows(QModelIndex(), d->tasks.size(), d->tasks.size());
    d->tasks.append(task);
    endInsertRows();
}

void TasksModel::clear()
{
    beginResetModel();
    d->tasks.clear();
    endResetModel();
}

int TasksModel::rowCount(const QModelIndex &index) const
{
    if (!index.isValid())
        return d->tasks.size();
    return 0;
}

QVariant TasksModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant retval;

    if (orientation == Qt::Horizontal && section == 0)
    {
        switch (role)
        {
        case Qt::DisplayRole:
            retval = tr("Tasks");
            break;
        }
    }
    return retval;
}

QVariant TasksModel::data ( const QModelIndex & index, int role) const
{
    QVariant retval;

    if (index.isValid())
    {
        Task task = d->tasks.at(index.row());
        switch (role)
        {
        case Qt::DisplayRole:
            retval = task.name();
            break;
        case PriorityRole:
            retval = task.priority();
            break;
        case ListIdRole:
            retval = task.listId();
            break;
        case CompletedRole:
            retval = task.completed();
            break;
        case DueDateRole:
            retval = task.dueDate();
            break;
        case TagsRole:
            retval = task.tags();
            break;
        case NotesRole:
            retval = task.notes();
            break;
        case LocationRole:
            retval = task.location();
            break;
        case UrlRole:
            retval = task.url();
            break;
//        case TaskRole:
//            retval = task;
//            break;
        }
    }

    return retval;
}

} // namespace RTM
