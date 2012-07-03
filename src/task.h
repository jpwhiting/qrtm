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

#ifndef TASK_H
#define TASK_H

#include "rtm.h"

#include <QDateTime>
#include <QObject>
#include <QStringList>
#include <QVariantMap>

namespace RTM {

class RTMAPISHARED_EXPORT Task: public QObject
{
    Q_OBJECT
    Q_ENUMS(Priority)
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(Priority priority READ priority)
    Q_PROPERTY(QString location READ location)
    Q_PROPERTY(QDateTime duedate READ dueDate)
    Q_PROPERTY(QStringList tags READ tags)

public:
    enum Priority {
        High,
        Medium,
        Low,
        None
    };

    Task();
    Task(const Task &);
    Task &operator=(const Task &);
    virtual ~Task();

    void load(const QVariantMap &data, const QString &listId);

    QString name() const;
    QString seriesId() const;
    QString taskId() const;
    QString listId() const;
    Priority priority() const;
    QString location() const;
    QDateTime completed() const;
    QDateTime dueDate() const;
    QString url() const;
    QStringList tags() const;
    QStringList notes() const;

private:
    class Private;
    Private *const d;
};

// Helper method to extract taskGetList result into list of Tasks.
QList<Task> GenerateTaskList(const QVariantMap &data);

}

#endif // TASK_H
