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

#include "task.h"

#include <QDateTime>
#include <QStringList>

#include <QtDebug>

namespace RTM {

class Task::Private {
public:
    QString listId;
    QString seriesId;
    QString taskId;
    QString name;
    QString locationId;
    QString url;
    QDateTime created;
    QDateTime modified;
    QDateTime added;
    QDateTime completed;
    QDateTime deleted;
    QDateTime dueDate;
    bool hasDueTime;
    Task::Priority priority;
    QString estimate;
    unsigned int postponed;
    QString source;
    QString recurrence;
    bool recurrenceEvery;

    QStringList tags;
    QStringList participants;
    QStringList notes;
};

Task::Task()
    :d(new Private)
{
}

Task::Task(const Task &rhs)
    :d(new Private)
{
    d->listId = rhs.d->listId;
    d->seriesId = rhs.d->seriesId;
    d->taskId = rhs.d->taskId;
    d->name = rhs.d->name;
    d->locationId = rhs.d->locationId;
    d->url = rhs.d->url;
    d->created = rhs.d->created;
    d->modified = rhs.d->modified;
    d->added = rhs.d->added;
    d->completed = rhs.d->completed;
    d->deleted = rhs.d->deleted;
    d->dueDate = rhs.d->dueDate;
    d->hasDueTime = rhs.d->hasDueTime;
    d->priority = rhs.d->priority;
    d->estimate = rhs.d->estimate;
    d->postponed = rhs.d->postponed;
    d->source = rhs.d->source;
    d->recurrence = rhs.d->recurrence;
    d->recurrenceEvery = rhs.d->recurrenceEvery;

    d->tags = rhs.d->tags;
    d->participants = rhs.d->participants;
    d->notes = rhs.d->notes;
}

Task &Task::operator=(const Task &rhs)
{
    if (this != &rhs)
    {
        d->listId = rhs.d->listId;
        d->seriesId = rhs.d->seriesId;
        d->taskId = rhs.d->taskId;
        d->name = rhs.d->name;
        d->locationId = rhs.d->locationId;
        d->url = rhs.d->url;
        d->created = rhs.d->created;
        d->modified = rhs.d->modified;
        d->added = rhs.d->added;
        d->completed = rhs.d->completed;
        d->deleted = rhs.d->deleted;
        d->dueDate = rhs.d->dueDate;
        d->hasDueTime = rhs.d->hasDueTime;
        d->priority = rhs.d->priority;
        d->estimate = rhs.d->estimate;
        d->postponed = rhs.d->postponed;
        d->source = rhs.d->source;
        d->recurrence = rhs.d->recurrence;
        d->recurrenceEvery = rhs.d->recurrenceEvery;

        d->tags = rhs.d->tags;
        d->participants = rhs.d->participants;
        d->notes = rhs.d->notes;
    }
    return *this;
}

Task::~Task()
{

}

void Task::load(const QVariantMap &data, const QString &listId)
{
    // First load the list id
    d->listId = listId;

    // Then load the taskseries id and attributes
    d->seriesId     = data.value("id").toString();
    d->name         = data.value("name").toString();
    d->url          = data.value("url").toString();
    d->locationId   = data.value("location_id").toString();
    d->source       = data.value("source").toString();
    d->created      = QDateTime::fromString(data.value("created").toString(),
                                            Qt::ISODate);
    d->modified     = QDateTime::fromString(data.value("modified").toString(),
                                            Qt::ISODate);

    QVariantMap rRuleMap = data.value("rrule").toMap();
    QVariantMap tagsMap = data.value("tags").toMap();
    QVariantList tagsList = tagsMap.values();
    Q_FOREACH(const QVariant &tag, tagsList)
    {
        if (tag.type() == QVariant::String)
            d->tags.append(tag.toString());
        else
            Q_FOREACH(const QVariant &subtag, tag.toList())
            {
                d->tags.append(subtag.toString());
            }
    }

    // Finally load the task id and attributes
    QVariantMap taskMap = data.value("task").toMap();
    d->taskId = taskMap.value("id").toString();
    d->dueDate = QDateTime::fromString(taskMap.value("due").toString(),
                                        Qt::ISODate);
    d->hasDueTime = taskMap.value("has_due_time").toBool();
    d->added = QDateTime::fromString(taskMap.value("added").toString(),
                                     Qt::ISODate);
    d->completed = QDateTime::fromString(taskMap.value("completed").toString(),
                                         Qt::ISODate);
    d->deleted = QDateTime::fromString(taskMap.value("deleted").toString(),
                                       Qt::ISODate);
    d->postponed = taskMap.value("postponed").toBool();
    d->estimate = taskMap.value("estimate").toString();
    switch (taskMap.value("priority").toUInt())
    {
    case 1:
        d->priority = Task::High;
        break;
    case 2:
        d->priority = Task::Medium;
        break;
    case 3:
        d->priority = Task::Low;
        break;
    default:
        d->priority = Task::None;
        break;
    }

}

QString Task::name() const
{
    return d->name;
}

QString Task::seriesId() const
{
    return d->seriesId;
}

QString Task::taskId() const
{
    return d->taskId;
}

QString Task::listId() const
{
    return d->listId;
}

Task::Priority Task::priority() const
{
    return d->priority;
}

QDateTime Task::completed() const
{
    return d->completed;
}

QString Task::location() const
{
    return d->locationId;
}

QDateTime Task::dueDate() const
{
    return d->dueDate;
}

QString Task::url() const
{
    return d->url;
}

QStringList Task::tags() const
{
    return d->tags;
}

QStringList Task::notes() const
{
    return d->notes;
}

QList<Task> GenerateTaskList(const QVariantMap &data)
{
    QList<Task> resultList;

    QVariantMap tasksMap = data.value("tasks").toMap();
    QVariantList lists = tasksMap.value("list").toList();
    Q_FOREACH(const QVariant &list, lists)
    {
        QString id = list.toMap().value("id").toString();
        QVariantList seriesList = list.toMap().value("taskseries").toList();
        Q_FOREACH(const QVariant &series, seriesList)
        {
            QVariantMap tasks = series.toMap();

            Task newInfo;
            newInfo.load(tasks, id);
            resultList.append(newInfo);
        }
    }

    return resultList;
}

}
