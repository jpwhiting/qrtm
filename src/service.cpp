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

#include "service.h"

RTM::Service::Service(QString key, QString secret, RTM::Permission perms, QString token, QObject *parent) :
    QObject(parent), authentication(key, secret, perms, token, this), apiKey(key), sharedSecret(secret)
{

}

void RTM::Service::authenticate()
{
    connect(&authentication, SIGNAL(authFinished(QVariantMap)), this, SIGNAL(authenticationSuccessful(QVariantMap)));
    connect(&authentication, SIGNAL(authError(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(authenticationFailed(QVariantMap,RTM::ResponseStatus)));
    authentication.beginAuth();
}

void RTM::Service::authCheckToken(QString tok)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Unsigned, this);
    connect(request, SIGNAL(requestFinished(QVariantMap, RTM::ResponseStatus)), this, SIGNAL(authCheckTokenFinished(QVariantMap, RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", tok);
    request->addArgument("method", RTM::AUTH_CHECK_TOKEN);
    request->sendRequest();
}

void RTM::Service::authGetToken()
{
    if(authentication.getToken().isEmpty())
        emit authGetTokenFinished("", RTM::Fail);
    else
        emit authGetTokenFinished(authentication.getToken(), RTM::OK);
}

void RTM::Service::contactsAdd(QString timeline, QString contact)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap, RTM::ResponseStatus)), this, SIGNAL(contactsAddFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::CONTACTS_ADD);
    request->addArgument("timeline", timeline);
    request->addArgument("contact", contact);
    request->sendRequest();
}

void RTM::Service::contactsDelete(QString timeline, QString contactID)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap, RTM::ResponseStatus)), this, SIGNAL(contactsDeleteFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::CONTACTS_DELETE);
    request->addArgument("timeline", timeline);
    request->addArgument("contact_id", contactID);
    request->sendRequest();
}

void RTM::Service::contactsGetList()
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap, RTM::ResponseStatus)), this, SIGNAL(contactsGetListFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::CONTACTS_GET_LIST);
    request->sendRequest();
}

void RTM::Service::groupsAdd(QString timeline, QString groupName)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap, RTM::ResponseStatus)), this, SIGNAL(groupsAddFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::GROUPS_ADD);
    request->addArgument("timeline", timeline);
    request->addArgument("group", groupName);
    request->sendRequest();
}

void RTM::Service::groupsAddContact(QString timeline, QString groupID, QString contactID)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap, RTM::ResponseStatus)), this, SIGNAL(groupsAddContactFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::GROUPS_ADD_CONTACT);
    request->addArgument("timeline", timeline);
    request->addArgument("group_id", groupID);
    request->addArgument("contact_id", contactID);
    request->sendRequest();
}

void RTM::Service::groupsDelete(QString timeline, QString groupID)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap, RTM::ResponseStatus)), this, SIGNAL(groupsDeleteFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::GROUPS_DELETE);
    request->addArgument("timeline", timeline);
    request->addArgument("group_id", groupID);
    request->sendRequest();
}

void RTM::Service::groupsGetList()
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap, RTM::ResponseStatus)), this, SIGNAL(groupsGetListFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::GROUPS_GET_LIST);
    request->sendRequest();
}

void RTM::Service::groupsRemoveContact(QString timeline, QString groupID, QString contactID)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap, RTM::ResponseStatus)), this, SIGNAL(groupsRemoveContactFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::GROUPS_REMOVE_CONTACT);
    request->addArgument("timeline", timeline);
    request->addArgument("group_id", groupID);
    request->addArgument("contact_id", contactID);
    request->sendRequest();
}

void RTM::Service::listsAdd(QString timeline, QString listName, QString filter)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(listsAddFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::LISTS_ADD);
    request->addArgument("timeline", timeline);
    request->addArgument("name", listName);
    if(!filter.isEmpty())
        request->addArgument("filter", filter);
    request->sendRequest();
}

void RTM::Service::listsArchive(QString timeline, QString listID)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(listsArchiveFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::LISTS_ARCHIVE);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->sendRequest();
}

void RTM::Service::listsDelete(QString timeline, QString listID)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(listsDeleteFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::LISTS_DELETE);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->sendRequest();
}

void RTM::Service::listsGetList()
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap, RTM::ResponseStatus)), this, SIGNAL(listsGetListFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::LISTS_GET_LIST);
    request->sendRequest();
}

void RTM::Service::listsSetDefaultList(QString timeline, QString listID)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(listsSetDefaultListFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::LISTS_SET_DEFAULT_LIST);
    request->addArgument("timeline", timeline);
    if(!listID.isEmpty())
        request->addArgument("list_id", listID);
    request->sendRequest();
}

void RTM::Service::listsSetName(QString timeline, QString listID, QString listName)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(listsSetNameFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::LISTS_SET_NAME);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->addArgument("name", listName);
    request->sendRequest();
}

void RTM::Service::listsUnarchive(QString timeline, QString listID)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(listsUnarchiveFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::LISTS_UNARCHIVE);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->sendRequest();
}

void RTM::Service::locationsGetList()
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(locationsGetListFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::LOCATIONS_GET_LIST);
    request->sendRequest();
}

void RTM::Service::settingsGetList()
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(settingsGetListFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::SETTINGS_GET_LIST);
    request->sendRequest();
}

void RTM::Service::tasksAdd(QString timeline, QString taskName, QString listID)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksAddFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::TASKS_ADD);
    request->addArgument("timeline", timeline);
    request->addArgument("name", taskName);
    request->addArgument("parse", "0");
    if(!listID.isEmpty())
        request->addArgument("list_id", listID);
    request->sendRequest();
}

void RTM::Service::tasksSmartAdd(QString timeline, QString taskName, QString listID)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksAddFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::TASKS_ADD);
    request->addArgument("timeline", timeline);
    request->addArgument("name", taskName);
    request->addArgument("parse", "1");
    if(!listID.isEmpty())
        request->addArgument("list_id", listID);
    request->sendRequest();
}

void RTM::Service::tasksAddTags(QString timeline, QString listID, QString taskSeriesID, QString taskID, QString tags)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksAddTagsFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::TASKS_ADD_TAGS);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->addArgument("taskseries_id", taskSeriesID);
    request->addArgument("task_id", taskID);
    request->addArgument("tags", tags);
    request->sendRequest();
}

void RTM::Service::tasksComplete(QString timeline, QString listID, QString taskSeriesID, QString taskID)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksCompleteFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::TASKS_COMPLETE);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->addArgument("taskseries_id", taskSeriesID);
    request->addArgument("task_id", taskID);
    request->sendRequest();
}

void RTM::Service::tasksDelete(QString timeline, QString listID, QString taskSeriesID, QString taskID)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksDeleteFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::TASKS_DELETE);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->addArgument("taskseries_id", taskSeriesID);
    request->addArgument("task_id", taskID);
    request->sendRequest();
}

void RTM::Service::tasksGetList()
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksGetListFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::TASKS_GET_LIST);
    request->sendRequest();
}

void RTM::Service::tasksGetList(QMap<QString, QString> args)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksGetListFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::TASKS_GET_LIST);
    if(args.contains("list_id"))
    request->addArgument("list_id", args.value("list_id"));
    if(args.contains("filter"))
        request->addArgument("filter", args.value("filter"));
    if(args.contains("last_sync"))
        request->addArgument("last_sync", args.value("last_sync"));
    request->sendRequest();
}

void RTM::Service::tasksMovePriority(QString timeline, QString listID, QString taskSeriesID, QString taskID, QString direction)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksMovePriorityFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::TASKS_MOVE_PRIORITY);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->addArgument("taskseries_id", taskSeriesID);
    request->addArgument("task_id", taskID);
    request->addArgument("direction", direction);
    request->sendRequest();
}

void RTM::Service::tasksMoveTo(QString timeline, QString fromListID, QString toListID, QString taskSeriesID, QString taskID)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksMoveToFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::TASKS_MOVE_TO);
    request->addArgument("timeline", timeline);
    request->addArgument("from_list_id", fromListID);
    request->addArgument("to_list_id", toListID);
    request->addArgument("taskseries_id", taskSeriesID);
    request->addArgument("task_id", taskID);
    request->sendRequest();
}

void RTM::Service::tasksPostpone(QString timeline, QString listID, QString taskSeriesID, QString taskID)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksPostponeFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::TASKS_POSTPONE);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->addArgument("taskseries_id", taskSeriesID);
    request->addArgument("task_id", taskID);
    request->sendRequest();
}

void RTM::Service::tasksRemoveTags(QString timeline, QString listID, QString taskSeriesID, QString taskID, QString tags)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksRemoveTagsFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::TASKS_REMOVE_TAGS);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->addArgument("taskseries_id", taskSeriesID);
    request->addArgument("task_id", taskID);
    request->addArgument("tags", tags);
    request->sendRequest();
}

void RTM::Service::tasksSetDueDate(QString timeline, QString listID, QString taskSeriesID, QString taskID)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksSetDueDateFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::TASKS_SET_DUE_DATE);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->addArgument("taskseries_id", taskSeriesID);
    request->addArgument("task_id", taskID);
    request->sendRequest();
}

void RTM::Service::tasksSetDueDate(QString timeline, QString listID, QString taskSeriesID, QString taskID, QMap<QString, QString>optArgs)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksSetDueDateFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::TASKS_SET_DUE_DATE);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->addArgument("taskseries_id", taskSeriesID);
    request->addArgument("task_id", taskID);
    if(optArgs.contains("due"))
        request->addArgument("due", optArgs.value("due"));
    if(optArgs.contains("has_due_time"))
        request->addArgument("has_due_time", optArgs.value("has_due_time"));
    if(optArgs.contains("parse"))
        request->addArgument("parse", optArgs.value("parse"));
    request->sendRequest();
}

void RTM::Service::tasksSetEstimate(QString timeline, QString listID, QString taskSeriesID, QString taskID, QString estimate)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksSetEstimateFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::TASKS_SET_ESTIMATE);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->addArgument("taskseries_id", taskSeriesID);
    request->addArgument("task_id", taskID);
    if(!estimate.isEmpty())
        request->addArgument("estimate", estimate);
    request->sendRequest();
}

void RTM::Service::tasksSetLocation(QString timeline, QString listID, QString taskSeriesID, QString taskID, QString locationID)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksSetLocationFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::TASKS_SET_LOCATION);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->addArgument("taskseries_id", taskSeriesID);
    request->addArgument("task_id", taskID);
    if(!locationID.isEmpty())
        request->addArgument("location_id", locationID);
    request->sendRequest();
}

void RTM::Service::tasksSetName(QString timeline, QString listID, QString taskSeriesID, QString taskID, QString taskName)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksSetNameFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::TASKS_SET_NAME);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->addArgument("taskseries_id", taskSeriesID);
    request->addArgument("task_id", taskID);
    request->addArgument("name", taskName);
    request->sendRequest();
}

void RTM::Service::tasksSetPriority(QString timeline, QString listID, QString taskSeriesID, QString taskID, QString priority)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksSetPriorityFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::TASKS_SET_PRIORITY);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->addArgument("taskseries_id", taskSeriesID);
    request->addArgument("task_id", taskID);
    if(!priority.isEmpty())
        request->addArgument("priority", priority);
    request->sendRequest();
}

void RTM::Service::tasksSetRecurrence(QString timeline, QString listID, QString taskSeriesID, QString taskID, QString repeat)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksSetRecurrenceFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::TASKS_SET_RECURRENCE);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->addArgument("taskseries_id", taskSeriesID);
    request->addArgument("task_id", taskID);
    if(!repeat.isEmpty())
        request->addArgument("repeat", repeat);
    request->sendRequest();
}

void RTM::Service::tasksSetTags(QString timeline, QString listID, QString taskSeriesID, QString taskID, QString tags)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksSetTagsFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::TASKS_SET_TAGS);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->addArgument("taskseries_id", taskSeriesID);
    request->addArgument("task_id", taskID);
    if(!tags.isEmpty())
        request->addArgument("tags", tags);
    request->sendRequest();
}

void RTM::Service::tasksSetUrl(QString timeline, QString listID, QString taskSeriesID, QString taskID, QString url)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksSetUrlFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::TASKS_SET_URL);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->addArgument("taskseries_id", taskSeriesID);
    request->addArgument("task_id", taskID);
    if(!url.isEmpty())
        request->addArgument("url", url);
    request->sendRequest();
}

void RTM::Service::tasksUncomplete(QString timeline, QString listID, QString taskSeriesID, QString taskID)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksUncompleteFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::TASKS_UNCOMPLETE);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->addArgument("taskseries_id", taskSeriesID);
    request->addArgument("task_id", taskID);
    request->sendRequest();
}

void RTM::Service::tasksNotesAdd(QString timeline, QString listID, QString taskSeriesID, QString taskID, QString noteTitle, QString noteText)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksNotesAddFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::TASKS_NOTES_ADD);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->addArgument("taskseries_id", taskSeriesID);
    request->addArgument("task_id", taskID);
    request->addArgument("note_title", noteTitle);
    request->addArgument("note_text", noteText);
    request->sendRequest();
}

void RTM::Service::tasksNotesDelete(QString timeline, QString noteID)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksNotesDeleteFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::TASKS_NOTES_DELETE);
    request->addArgument("timeline", timeline);
    request->addArgument("note_id", noteID);
    request->sendRequest();
}

void RTM::Service::tasksNotesEdit(QString timeline, QString noteID, QString noteTitle, QString noteText)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksNotesEditFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::TASKS_NOTES_EDIT);
    request->addArgument("timeline", timeline);
    request->addArgument("note_id", noteID);
    request->addArgument("note_title", noteTitle);
    request->addArgument("note_text", noteText);
    request->sendRequest();
}

void RTM::Service::timeConvert(QString toTimezone)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(timeConvertFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::TIME_CONVERT);
    request->addArgument("to_timezone", toTimezone);
    request->sendRequest();
}

void RTM::Service::timeConvert(QString toTimezone, QMap<QString, QString> optArgs)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(timeConvertFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::TIME_CONVERT);
    request->addArgument("to_timezone", toTimezone);
    if(optArgs.contains("from_timezone"))
        request->addArgument("from_timezone", optArgs.value("from_timezone"));
    if(optArgs.contains("time"))
        request->addArgument("time", optArgs.value("time"));
    request->sendRequest();
}

void RTM::Service::timeParse(QString text)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(timeParseFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::TIME_PARSE);
    request->addArgument("text", text);
    request->sendRequest();
}

void RTM::Service::timeParse(QString text, QMap<QString, QString> optArgs)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(timeParseFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::TIME_PARSE);
    request->addArgument("text", text);
    if(optArgs.contains("timezone"))
        request->addArgument("timezone", optArgs.value("timezone"));
    if(optArgs.contains("dateformat"))
        request->addArgument("dateformat", optArgs.value("dateformat"));
    request->sendRequest();
}

void RTM::Service::timelinesCreate()
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(timelinesCreateFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::TIMELINES_CREATE);
    request->sendRequest();
}

void RTM::Service::timezonesGetList()
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(timezonesGetListFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("method", RTM::TIMEZONES_GET_LIST);
    request->sendRequest();
}

void RTM::Service::transactionsUndo(QString timeline, QString transactionID)
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(transactionsUndoFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::TRANSACTIONS_UNDO);
    request->addArgument("timeline", timeline);
    request->addArgument("transaction_id", transactionID);
    request->sendRequest();
}

void RTM::Service::testLogin()
{
    RTM::Request * request = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(testLoginFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", apiKey);
    request->addArgument("auth_token", token);
    request->addArgument("method", RTM::TEST_LOGIN);
    request->sendRequest();
}
