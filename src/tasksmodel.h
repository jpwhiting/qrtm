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

#ifndef TASKSMODEL_H
#define TASKSMODEL_H

#include <QAbstractListModel>

#include "task.h"

namespace RTM {

class TasksModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum {
        PriorityRole = Qt::UserRole + 1,
        CompletedRole,
        ListIdRole,
        SeriesIdRole,
        TaskIdRole,
        DueDateRole,
        TagsRole,
        NotesRole,
        LocationRole,
        UrlRole
    };

    explicit TasksModel(QObject *parent = 0);

    virtual int rowCount(const QModelIndex &index) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    virtual QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    Q_INVOKABLE RTM::Task *taskForRow(const int row) const;

    friend class Service;

    void addTask(Task *task);
    void clear();
signals:

public slots:

private:
    class Private;
    Private * const d;
};

} // namespace RTM

#endif // RTM_TASKSMODEL_H
