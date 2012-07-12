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

#include "filteredtasksmodel.h"

#include "tasksmodel.h"

#include <QDateTime>
#include <QtDebug>

namespace RTM
{

class FilteredTasksModel::Private {
public:
    QString listId;
    QString filter;
    List::SortOrder sortOrder;
    bool completed;
};

FilteredTasksModel::FilteredTasksModel(QObject *parent) :
    QSortFilterProxyModel(parent), d(new Private)
{
    // Default to show uncompleted items.
    d->completed = false;
    d->sortOrder = List::ByName;
    setDynamicSortFilter(true);
}

bool FilteredTasksModel::filterAcceptsRow(int sourceRow,
                                        const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
    QDateTime completedTime =
            sourceModel()->data(index, TasksModel::CompletedRole).toDateTime();

    // If it doesn't match the completed, don't accept it.
    if (d->completed)
    {
        // Don't accept uncompleted tasks.
        if (!completedTime.isValid())
        {
            return false;
        }
    }
    else
    {
        // Don't accept completed tasks.
        if (completedTime.isValid())
        {
            return false;
        }
    }

    // It's a smart list, so accept any listId
    // Or if the listId matches, accept it.
    if (d->listId.isEmpty() ||
        index.data(TasksModel::ListIdRole).toString() == d->listId)
    {
        return true;
    }

    return false;
}

void FilteredTasksModel::setListParameters(const QString &id,
                                           List::SortOrder sortOrder)
{
    d->listId = id;
    d->sortOrder = sortOrder;
    invalidateFilter();
    invalidate();
    sort(0);
}

void FilteredTasksModel::setCompleted(bool completed)
{
    d->completed = completed;
    invalidateFilter();
    sort(0);
}

bool FilteredTasksModel::lessThan(const QModelIndex &left,
                                  const QModelIndex &right) const
{
    // If sorting by due date, do that first, then priority, then name.
    if (d->sortOrder == List::ByDueDate)
    {
        if (left.data(TasksModel::DueDateRole).toDateTime() !=
                right.data(TasksModel::DueDateRole).toDateTime())
            return left.data(TasksModel::DueDateRole).toDateTime() <
                    right.data(TasksModel::DueDateRole).toDateTime();
        else if (left.data(TasksModel::PriorityRole).toUInt() !=
                 right.data(TasksModel::PriorityRole).toUInt())
             return left.data(TasksModel::PriorityRole).toUInt() <
                     right.data(TasksModel::PriorityRole).toUInt();
    }
    // If sorting by priority, do that first, then due date, then name.
    if (d->sortOrder == List::ByPriority)
    {
        if (left.data(TasksModel::PriorityRole).toUInt() !=
                right.data(TasksModel::PriorityRole).toUInt())
            return left.data(TasksModel::PriorityRole).toUInt() <
                    right.data(TasksModel::PriorityRole).toUInt();
        else if (left.data(TasksModel::DueDateRole).toDateTime() !=
                 right.data(TasksModel::DueDateRole).toDateTime())
            return left.data(TasksModel::DueDateRole).toDateTime() <
                    right.data(TasksModel::DueDateRole).toDateTime();
    }

    // If sorting by name, only sort by name.
    return QString::compare(left.data().toString(),
                            right.data().toString(), Qt::CaseInsensitive) < 0;
}

RTM::Task* FilteredTasksModel::taskForRow(const int row) const
{
    QModelIndex proxyIndex = index(row, 0, QModelIndex());
    QModelIndex sourceIndex = mapToSource(proxyIndex);
    TasksModel * model = qobject_cast<TasksModel*>(sourceModel());
    return model->taskForRow(sourceIndex.row());
}

}
