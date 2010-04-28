/*
 *  Copyright (C) 2010  Sertac Olgunsoylu <sertacolgunsoylu@gmail.com>
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

#ifndef H
#define H

#include "libqrtm_global.h"
#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtCore/QVariantMap>
#include "libqjson/parser.h"

namespace RTM
{
    enum MethodType {Signed, Unsigned};
    enum Permission {Read, Write, Delete};
    enum ResponseStatus {Malformed = -1, Fail = 0, OK = 1};

    const QString baseMethodUrl = "http://api.rememberthemilk.com/services/rest/?";
    const QString baseAuthUrl = "http://www.rememberthemilk.com/services/auth/?";


    const QString AUTH_CHECK_TOKEN = "rtm.auth.checkToken";
    const QString CONTACTS_ADD = "rtm.contacts.add";
    const QString CONTACTS_DELETE = "rtm.contacts.delete";
    const QString CONTACTS_GET_LIST = "rtm.contacts.getList";
    const QString GROUPS_ADD = "rtm.groups.add";
    const QString GROUPS_ADD_CONTACT = "rtm.groups.addContact";
    const QString GROUPS_DELETE = "rtm.groups.delete";
    const QString GROUPS_GET_LIST = "rtm.groups.getList";
    const QString GROUPS_REMOVE_CONTACT = "rtm.groups.removeContact";
    const QString LISTS_ADD = "rtm.lists.add";
    const QString LISTS_ARCHIVE = "rtm.lists.archive";
    const QString LISTS_DELETE = "rtm.lists.delete";
    const QString LISTS_GET_LIST = "rtm.lists.getList";
    const QString LISTS_SET_DEFAULT_LIST = "rtm.lists.setDefaultList";
    const QString LISTS_SET_NAME = "rtm.lists.setName";
    const QString LISTS_UNARCHIVE = "rtm.lists.unarchive";
    const QString LOCATIONS_GET_LIST = "rtm.locations.getList";
    const QString SETTINGS_GET_LIST = "rtm.settings.getList";
    const QString TASKS_ADD = "rtm.tasks.add";
    const QString TASKS_ADD_TAGS = "rtm.tasks.addTags";
    const QString TASKS_COMPLETE = "rtm.tasks.complete";
    const QString TASKS_DELETE = "rtm.tasks.delete";
    const QString TASKS_GET_LIST = "rtm.tasks.getList";
    const QString TASKS_MOVE_PRIORITY = "rtm.tasks.movePriority";
    const QString TASKS_MOVE_TO = "rtm.tasks.moveTo";
    const QString TASKS_POSTPONE = "rtm.tasks.postpone";
    const QString TASKS_REMOVE_TAGS = "rtm.tasks.removeTags";
    const QString TASKS_SET_DUE_DATE = "rtm.tasks.setDueDate";
    const QString TASKS_SET_ESTIMATE = "rtm.tasks.setEstimate";
    const QString TASKS_SET_LOCATION = "rtm.tasks.setLocation";
    const QString TASKS_SET_NAME = "rtm.tasks.setName";
    const QString TASKS_SET_PRIORITY = "rtm.tasks.setPriority";
    const QString TASKS_SET_RECURRENCE = "rtm.tasks.setRecurrence";
    const QString TASKS_SET_TAGS = "rtm.tasks.setTags";
    const QString TASKS_SET_URL = "rtm.tasks.setURL";
    const QString TASKS_UNCOMPLETE = "rtm.tasks.uncomplete";
    const QString TASKS_NOTES_ADD = "rtm.tasks.notes.add";
    const QString TASKS_NOTES_DELETE = "rtm.tasks.notes.delete";
    const QString TASKS_NOTES_EDIT = "rtm.tasks.notes.edit";
    const QString TIME_CONVERT = "rtm.time.convert";
    const QString TIME_PARSE = "rtm.time.parse";
    const QString TIMELINES_CREATE = "rtm.timelines.create";
    const QString TIMEZONES_GET_LIST = "rtm.timezones.getList";
    const QString TRANSACTIONS_UNDO = "rtm.transactions.undo";
    const QString TEST_LOGIN = "rtm.test.login";
}

#endif // H
