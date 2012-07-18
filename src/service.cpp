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
#include "authentication.h"
#include "listsmodel.h"
#include "tasksmodel.h"
#include "filteredtasksmodel.h"

#include <QtDebug>

using namespace RTM;

class Service::Private
{
public:
    Private(Service *service)
    {
        authentication = 0;
        listsModel = new ListsModel(service);

        connect(service, SIGNAL(listsGetListFinished(QVariantMap,RTM::ResponseStatus)),
                listsModel, SLOT(onGetListFinished(QVariantMap,RTM::ResponseStatus)));
    }

    Authentication * authentication;
    QString apiKey;
    QString sharedSecret;
    QString token;
    QMap <RTM::Request*, QString> requestIds;

    ListsModel *listsModel;
};

Service::Service(QObject *parent) :
    QObject(parent), d(new Private(this))
{
}

Service::Service(QString key, QString secret, QObject *parent) :
    QObject(parent), d(new Private(this))
{
    d->apiKey = key;
    d->sharedSecret = secret;
    d->authentication = new Authentication(key, secret, Read, "", this);
    connect(d->authentication, SIGNAL(authFinished(QVariantMap)),
            this, SLOT(onAuthFinished()));
    connect(d->authentication, SIGNAL(authError(QVariantMap,RTM::ResponseStatus)),
            this, SLOT(onAuthError()));
    connect(d->authentication, SIGNAL(loadAuthUrl(QUrl)),
            this, SIGNAL(authenticationLoadUrl(QUrl)));
}

Service::~Service()
{
    delete d->authentication;
    d->authentication = 0;

    delete d->listsModel;
    d->listsModel = 0;
}

void Service::setKey(QString key, QString secret)
{
    d->apiKey = key;
    d->sharedSecret = secret;

    if (d->authentication)
        delete d->authentication;
    d->authentication = new Authentication(key, secret, Read, "", this);
    connect(d->authentication, SIGNAL(authFinished(QVariantMap)),
            this, SLOT(onAuthFinished()));
    connect(d->authentication, SIGNAL(authError(QVariantMap,RTM::ResponseStatus)),
            this, SLOT(onAuthError()));
    connect(d->authentication, SIGNAL(loadAuthUrl(QUrl)),
            this, SIGNAL(authenticationLoadUrl(QUrl)));
}

Permission Service::getPermission()
{
    return d->authentication->getPermission();
}

ListsModel *Service::getListsModel()
{
    return d->listsModel;
}

void Service::authenticate(Permission p)
{
    d->authentication->setPermission(p);
    d->authentication->beginAuth();
}

void Service::onAuthFinished()
{
    d->token = d->authentication->getToken();
    emit authenticationDone(true);
}

void Service::onAuthError()
{
    d->listsModel->clear();
    emit authenticationDone(false);
}

void Service::authRequestToken()
{
    qDebug() << "Requesting authorized token";
    d->authentication->requestToken();
}

QString Service::getToken() const
{
    return d->token;
}

void Service::authCheckToken(QString tok)
{
    d->token = tok; // Store the token we are checking.
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Unsigned, this);
    connect(request, SIGNAL(requestFinished(QVariantMap, RTM::ResponseStatus)),
            this, SLOT(onCheckTokenFinished(QVariantMap, RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", tok);
    request->addArgument("method", AUTH_CHECK_TOKEN);
    request->sendRequest();
}

void Service::onCheckTokenFinished(QVariantMap response, RTM::ResponseStatus status)
{
    if (status == RTM::OK)
    {
        // use the token checked.
        emit authenticationDone(true);
    }
    else
    {
        // It was no good, so clear it.
        d->token = QString();
        emit authenticationDone(false);
    }
}

void Service::contactsAdd(QString timeline, QString contact)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap, RTM::ResponseStatus)), this, SIGNAL(contactsAddFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", CONTACTS_ADD);
    request->addArgument("timeline", timeline);
    request->addArgument("contact", contact);
    request->sendRequest();
}

void Service::contactsDelete(QString timeline, QString contactID)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap, RTM::ResponseStatus)), this, SIGNAL(contactsDeleteFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", CONTACTS_DELETE);
    request->addArgument("timeline", timeline);
    request->addArgument("contact_id", contactID);
    request->sendRequest();
}

void Service::contactsGetList()
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap, RTM::ResponseStatus)), this, SIGNAL(contactsGetListFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", CONTACTS_GET_LIST);
    request->sendRequest();
}

void Service::groupsAdd(QString timeline, QString groupName)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap, RTM::ResponseStatus)), this, SIGNAL(groupsAddFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", GROUPS_ADD);
    request->addArgument("timeline", timeline);
    request->addArgument("group", groupName);
    request->sendRequest();
}

void Service::groupsAddContact(QString timeline, QString groupID, QString contactID)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap, RTM::ResponseStatus)), this, SIGNAL(groupsAddContactFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", GROUPS_ADD_CONTACT);
    request->addArgument("timeline", timeline);
    request->addArgument("group_id", groupID);
    request->addArgument("contact_id", contactID);
    request->sendRequest();
}

void Service::groupsDelete(QString timeline, QString groupID)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap, RTM::ResponseStatus)), this, SIGNAL(groupsDeleteFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", GROUPS_DELETE);
    request->addArgument("timeline", timeline);
    request->addArgument("group_id", groupID);
    request->sendRequest();
}

void Service::groupsGetList()
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap, RTM::ResponseStatus)), this, SIGNAL(groupsGetListFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", GROUPS_GET_LIST);
    request->sendRequest();
}

void Service::groupsRemoveContact(QString timeline, QString groupID, QString contactID)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap, RTM::ResponseStatus)), this, SIGNAL(groupsRemoveContactFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", GROUPS_REMOVE_CONTACT);
    request->addArgument("timeline", timeline);
    request->addArgument("group_id", groupID);
    request->addArgument("contact_id", contactID);
    request->sendRequest();
}

void Service::listsAdd(QString timeline, QString listName, QString filter)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(listsAddFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", LISTS_ADD);
    request->addArgument("timeline", timeline);
    request->addArgument("name", listName);
    if(!filter.isEmpty())
        request->addArgument("filter", filter);
    request->sendRequest();
}

void Service::listsArchive(QString timeline, QString listID)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(listsArchiveFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", LISTS_ARCHIVE);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->sendRequest();
}

void Service::listsDelete(QString timeline, QString listID)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(listsDeleteFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", LISTS_DELETE);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->sendRequest();
}

void Service::listsGetList()
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap, RTM::ResponseStatus)),
            this, SIGNAL(listsGetListFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", LISTS_GET_LIST);
    request->sendRequest();
}

void Service::listsSetDefaultList(QString timeline, QString listID)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(listsSetDefaultListFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", LISTS_SET_DEFAULT_LIST);
    request->addArgument("timeline", timeline);
    if(!listID.isEmpty())
        request->addArgument("list_id", listID);
    request->sendRequest();
}

void Service::listsSetName(QString timeline, QString listID, QString listName)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(listsSetNameFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", LISTS_SET_NAME);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->addArgument("name", listName);
    request->sendRequest();
}

void Service::listsUnarchive(QString timeline, QString listID)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(listsUnarchiveFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", LISTS_UNARCHIVE);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->sendRequest();
}

void Service::locationsGetList()
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(locationsGetListFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", LOCATIONS_GET_LIST);
    request->sendRequest();
}

void Service::settingsGetList()
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(settingsGetListFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", SETTINGS_GET_LIST);
    request->sendRequest();
}

void Service::tasksAdd(QString timeline, QString taskName, QString listID)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksAddFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", TASKS_ADD);
    request->addArgument("timeline", timeline);
    request->addArgument("name", taskName);
    request->addArgument("parse", "0");
    if(!listID.isEmpty())
        request->addArgument("list_id", listID);
    request->sendRequest();
}

void Service::tasksSmartAdd(QString timeline, QString taskName, QString listID)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksAddFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", TASKS_ADD);
    request->addArgument("timeline", timeline);
    request->addArgument("name", taskName);
    request->addArgument("parse", "1");
    if(!listID.isEmpty())
        request->addArgument("list_id", listID);
    request->sendRequest();
}

void Service::tasksAddTags(QString timeline, QString listID, QString taskSeriesID, QString taskID, QString tags)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksAddTagsFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", TASKS_ADD_TAGS);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->addArgument("taskseries_id", taskSeriesID);
    request->addArgument("task_id", taskID);
    request->addArgument("tags", tags);
    request->sendRequest();
}

void Service::tasksComplete(QString timeline, QString listID, QString taskSeriesID, QString taskID)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksCompleteFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", TASKS_COMPLETE);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->addArgument("taskseries_id", taskSeriesID);
    request->addArgument("task_id", taskID);
    request->sendRequest();
}

void Service::tasksDelete(QString timeline, QString listID, QString taskSeriesID, QString taskID)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksDeleteFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", TASKS_DELETE);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->addArgument("taskseries_id", taskSeriesID);
    request->addArgument("task_id", taskID);
    request->sendRequest();
}

void Service::tasksGetList()
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)),
            this, SIGNAL(tasksGetListFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", TASKS_GET_LIST);
    request->sendRequest();
}

void Service::tasksGetSmartList(QString id, QString filter)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)),
            this, SLOT(onTasksGetSmartListFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", TASKS_GET_LIST);
    request->addArgument("list_id", id);
    request->addArgument("filter", filter);
    d->requestIds.insert(request, id);
    request->sendRequest();
}

void Service::onTasksGetSmartListFinished(QVariantMap response, ResponseStatus status)
{
    Request * request = qobject_cast<Request*>(sender());
    Q_ASSERT(request != NULL);
    Q_ASSERT(d->requestIds.contains(request));

    QString list_id = d->requestIds.value(request);
    d->requestIds.remove(request);

    emit tasksGetSmartListFinished(list_id, response, status);
}

void Service::tasksMovePriority(QString timeline, QString listID, QString taskSeriesID, QString taskID, QString direction)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksMovePriorityFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", TASKS_MOVE_PRIORITY);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->addArgument("taskseries_id", taskSeriesID);
    request->addArgument("task_id", taskID);
    request->addArgument("direction", direction);
    request->sendRequest();
}

void Service::tasksMoveTo(QString timeline, QString fromListID, QString toListID, QString taskSeriesID, QString taskID)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksMoveToFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", TASKS_MOVE_TO);
    request->addArgument("timeline", timeline);
    request->addArgument("from_list_id", fromListID);
    request->addArgument("to_list_id", toListID);
    request->addArgument("taskseries_id", taskSeriesID);
    request->addArgument("task_id", taskID);
    request->sendRequest();
}

void Service::tasksPostpone(QString timeline, QString listID, QString taskSeriesID, QString taskID)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksPostponeFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", TASKS_POSTPONE);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->addArgument("taskseries_id", taskSeriesID);
    request->addArgument("task_id", taskID);
    request->sendRequest();
}

void Service::tasksRemoveTags(QString timeline, QString listID, QString taskSeriesID, QString taskID, QString tags)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksRemoveTagsFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", TASKS_REMOVE_TAGS);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->addArgument("taskseries_id", taskSeriesID);
    request->addArgument("task_id", taskID);
    request->addArgument("tags", tags);
    request->sendRequest();
}

void Service::tasksSetDueDate(QString timeline, QString listID, QString taskSeriesID, QString taskID)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksSetDueDateFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", TASKS_SET_DUE_DATE);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->addArgument("taskseries_id", taskSeriesID);
    request->addArgument("task_id", taskID);
    request->sendRequest();
}

void Service::tasksSetDueDate(QString timeline, QString listID, QString taskSeriesID, QString taskID, QMap<QString, QString>optArgs)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksSetDueDateFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", TASKS_SET_DUE_DATE);
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

void Service::tasksSetEstimate(QString timeline, QString listID, QString taskSeriesID, QString taskID, QString estimate)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksSetEstimateFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", TASKS_SET_ESTIMATE);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->addArgument("taskseries_id", taskSeriesID);
    request->addArgument("task_id", taskID);
    if(!estimate.isEmpty())
        request->addArgument("estimate", estimate);
    request->sendRequest();
}

void Service::tasksSetLocation(QString timeline, QString listID, QString taskSeriesID, QString taskID, QString locationID)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksSetLocationFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", TASKS_SET_LOCATION);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->addArgument("taskseries_id", taskSeriesID);
    request->addArgument("task_id", taskID);
    if(!locationID.isEmpty())
        request->addArgument("location_id", locationID);
    request->sendRequest();
}

void Service::tasksSetName(QString timeline, QString listID, QString taskSeriesID, QString taskID, QString taskName)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksSetNameFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", TASKS_SET_NAME);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->addArgument("taskseries_id", taskSeriesID);
    request->addArgument("task_id", taskID);
    request->addArgument("name", taskName);
    request->sendRequest();
}

void Service::tasksSetPriority(QString timeline, QString listID, QString taskSeriesID, QString taskID, QString priority)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksSetPriorityFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", TASKS_SET_PRIORITY);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->addArgument("taskseries_id", taskSeriesID);
    request->addArgument("task_id", taskID);
    if(!priority.isEmpty())
        request->addArgument("priority", priority);
    request->sendRequest();
}

void Service::tasksSetRecurrence(QString timeline, QString listID, QString taskSeriesID, QString taskID, QString repeat)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksSetRecurrenceFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", TASKS_SET_RECURRENCE);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->addArgument("taskseries_id", taskSeriesID);
    request->addArgument("task_id", taskID);
    if(!repeat.isEmpty())
        request->addArgument("repeat", repeat);
    request->sendRequest();
}

void Service::tasksSetTags(QString timeline, QString listID, QString taskSeriesID, QString taskID, QString tags)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksSetTagsFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", TASKS_SET_TAGS);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->addArgument("taskseries_id", taskSeriesID);
    request->addArgument("task_id", taskID);
    if(!tags.isEmpty())
        request->addArgument("tags", tags);
    request->sendRequest();
}

void Service::tasksSetUrl(QString timeline, QString listID, QString taskSeriesID, QString taskID, QString url)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksSetUrlFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", TASKS_SET_URL);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->addArgument("taskseries_id", taskSeriesID);
    request->addArgument("task_id", taskID);
    if(!url.isEmpty())
        request->addArgument("url", url);
    request->sendRequest();
}

void Service::tasksUncomplete(QString timeline, QString listID, QString taskSeriesID, QString taskID)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksUncompleteFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", TASKS_UNCOMPLETE);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->addArgument("taskseries_id", taskSeriesID);
    request->addArgument("task_id", taskID);
    request->sendRequest();
}

void Service::tasksNotesAdd(QString timeline, QString listID, QString taskSeriesID, QString taskID, QString noteTitle, QString noteText)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksNotesAddFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", TASKS_NOTES_ADD);
    request->addArgument("timeline", timeline);
    request->addArgument("list_id", listID);
    request->addArgument("taskseries_id", taskSeriesID);
    request->addArgument("task_id", taskID);
    request->addArgument("note_title", noteTitle);
    request->addArgument("note_text", noteText);
    request->sendRequest();
}

void Service::tasksNotesDelete(QString timeline, QString noteID)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksNotesDeleteFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", TASKS_NOTES_DELETE);
    request->addArgument("timeline", timeline);
    request->addArgument("note_id", noteID);
    request->sendRequest();
}

void Service::tasksNotesEdit(QString timeline, QString noteID, QString noteTitle, QString noteText)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(tasksNotesEditFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", TASKS_NOTES_EDIT);
    request->addArgument("timeline", timeline);
    request->addArgument("note_id", noteID);
    request->addArgument("note_title", noteTitle);
    request->addArgument("note_text", noteText);
    request->sendRequest();
}

void Service::timeConvert(QString toTimezone)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(timeConvertFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", TIME_CONVERT);
    request->addArgument("to_timezone", toTimezone);
    request->sendRequest();
}

void Service::timeConvert(QString toTimezone, QMap<QString, QString> optArgs)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(timeConvertFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", TIME_CONVERT);
    request->addArgument("to_timezone", toTimezone);
    if(optArgs.contains("from_timezone"))
        request->addArgument("from_timezone", optArgs.value("from_timezone"));
    if(optArgs.contains("time"))
        request->addArgument("time", optArgs.value("time"));
    request->sendRequest();
}

void Service::timeParse(QString text)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(timeParseFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", TIME_PARSE);
    request->addArgument("text", text);
    request->sendRequest();
}

void Service::timeParse(QString text, QMap<QString, QString> optArgs)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(timeParseFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", TIME_PARSE);
    request->addArgument("text", text);
    if(optArgs.contains("timezone"))
        request->addArgument("timezone", optArgs.value("timezone"));
    if(optArgs.contains("dateformat"))
        request->addArgument("dateformat", optArgs.value("dateformat"));
    request->sendRequest();
}

void Service::timelinesCreate()
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(timelinesCreateFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", TIMELINES_CREATE);
    request->sendRequest();
}

void Service::timezonesGetList()
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(timezonesGetListFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("method", TIMEZONES_GET_LIST);
    request->sendRequest();
}

void Service::transactionsUndo(QString timeline, QString transactionID)
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(transactionsUndoFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", TRANSACTIONS_UNDO);
    request->addArgument("timeline", timeline);
    request->addArgument("transaction_id", transactionID);
    request->sendRequest();
}

void Service::testLogin()
{
    Request * request = new Request(d->sharedSecret, baseMethodUrl, Signed, this);
    connect(request, SIGNAL(requestFinished(QVariantMap,RTM::ResponseStatus)), this, SIGNAL(testLoginFinished(QVariantMap,RTM::ResponseStatus)));
    request->addArgument("api_key", d->apiKey);
    request->addArgument("auth_token", d->token);
    request->addArgument("method", TEST_LOGIN);
    request->sendRequest();
}
