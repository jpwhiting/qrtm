/*
 *  Copyright (C) 2010  Sertac Olgunsoylu <sertacolgunsoylu@gmail.com>
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

#ifndef SERVICE_H
#define SERVICE_H

#include "rtm.h"
#include <QObject>
#include <QtCore/QVariantMap>



namespace RTM {

    class Authentication;
    class List;
    class ListsModel;
    class FilteredTasksModel;
    class Request;
    class Task;

    class RTMAPISHARED_EXPORT Service : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(RTM::ListsModel * listsModel READ getListsModel)

    public:
        Service(QObject *parent = 0);
        Service(QString key, QString secret, QObject *parent = 0);
        ~Service();

        void setKey(QString key, QString secret);

        // Get the authenticated token.
        // Returns empty QString if not authenticated.
        QString getToken() const;

        Permission getPermission();

        Q_INVOKABLE ListsModel *getListsModel();

    signals:
        // Signal the ui should load the given url in order to authenticate.
        void authenticationLoadUrl(const QUrl &url);
        // Signal authentication is done.
        void authenticationDone(bool success);

        void contactsAddFinished(QVariantMap response, RTM::ResponseStatus status);
        void contactsDeleteFinished(QVariantMap response, RTM::ResponseStatus status);
        void contactsGetListFinished(QVariantMap response, RTM::ResponseStatus status);

        void groupsAddFinished(QVariantMap response, RTM::ResponseStatus status);
        void groupsAddContactFinished(QVariantMap response, RTM::ResponseStatus status);
        void groupsDeleteFinished(QVariantMap response, RTM::ResponseStatus status);
        void groupsGetListFinished(QVariantMap response, RTM::ResponseStatus status);
        void groupsRemoveContactFinished(QVariantMap response, RTM::ResponseStatus status);

        void listsAddFinished(QVariantMap response, RTM::ResponseStatus status);
        void listsArchiveFinished(QVariantMap response, RTM::ResponseStatus status);
        void listsDeleteFinished(QVariantMap response, RTM::ResponseStatus status);
        void listsGetListFinished(QVariantMap response, RTM::ResponseStatus status);
        void listsSetDefaultListFinished(QVariantMap response, RTM::ResponseStatus status);
        void listsSetNameFinished(QVariantMap response, RTM::ResponseStatus status);
        void listsUnarchiveFinished(QVariantMap response, RTM::ResponseStatus status);

        void locationsGetListFinished(QVariantMap response, RTM::ResponseStatus status);

        void settingsGetListFinished(QVariantMap response, RTM::ResponseStatus status);

        void tasksAddFinished(QVariantMap response, RTM::ResponseStatus status);
        void tasksAddTagsFinished(QVariantMap response, RTM::ResponseStatus status);
        void tasksCompleteFinished(QVariantMap response, RTM::ResponseStatus status);
        void tasksDeleteFinished(QVariantMap response, RTM::ResponseStatus status);
        void tasksGetListFinished(QVariantMap response, RTM::ResponseStatus status);
        void tasksGetSmartListFinished(QString list_id, QVariantMap response, RTM::ResponseStatus status);
        void tasksMovePriorityFinished(QVariantMap response, RTM::ResponseStatus status);
        void tasksMoveToFinished(QVariantMap response, RTM::ResponseStatus status);
        void tasksPostponeFinished(QVariantMap response, RTM::ResponseStatus status);
        void tasksRemoveTagsFinished(QVariantMap response, RTM::ResponseStatus status);
        void tasksSetDueDateFinished(QVariantMap response, RTM::ResponseStatus status);
        void tasksSetEstimateFinished(QVariantMap response, RTM::ResponseStatus status);
        void tasksSetLocationFinished(QVariantMap response, RTM::ResponseStatus status);
        void tasksSetNameFinished(QVariantMap response, RTM::ResponseStatus status);
        void tasksSetPriorityFinished(QVariantMap response, RTM::ResponseStatus status);
        void tasksSetRecurrenceFinished(QVariantMap response, RTM::ResponseStatus status);
        void tasksSetTagsFinished(QVariantMap response, RTM::ResponseStatus status);
        void tasksSetUrlFinished(QVariantMap response, RTM::ResponseStatus status);
        void tasksUncompleteFinished(QVariantMap response, RTM::ResponseStatus status);
        void tasksNotesAddFinished(QVariantMap response, RTM::ResponseStatus status);
        void tasksNotesDeleteFinished(QVariantMap response, RTM::ResponseStatus status);
        void tasksNotesEditFinished(QVariantMap response, RTM::ResponseStatus status);

        void timeConvertFinished(QVariantMap response, RTM::ResponseStatus status);
        void timeParseFinished(QVariantMap response, RTM::ResponseStatus status);

        void timelinesCreateFinished(QVariantMap response, RTM::ResponseStatus status);

        void timezonesGetListFinished(QVariantMap response, RTM::ResponseStatus status);

        void transactionsUndoFinished(QVariantMap response, RTM::ResponseStatus status);

        void testLoginFinished(QVariantMap response, RTM::ResponseStatus status);

    public slots:
        // Ask for given Permission.
        // This will send authLoadUrl signal with url to load in a webview.
        void authenticate(Permission p);
        // When user is done authenticating, call this to request their token.
        void authRequestToken();
        // Call this to check a stored token.
        void authCheckToken(QString token);

        void contactsAdd(QString timeline, QString contact);
        void contactsDelete(QString timeline, QString contact);
        void contactsGetList();

        void groupsAdd(QString timeline, QString groupName);
        void groupsAddContact(QString timeline, QString groupID, QString contactID);
        void groupsDelete(QString timeline, QString groupID);
        void groupsGetList();
        void groupsRemoveContact(QString timeline, QString groupID, QString contactID);

        void listsAdd(QString timeline, QString listName, QString filter="");
        void listsArchive(QString timeline, QString listID);
        void listsDelete(QString timeline, QString listID);
        void listsGetList();
        void listsSetDefaultList(QString timeline, QString listID = "");
        void listsSetName(QString timeline, QString listID, QString listName);
        void listsUnarchive(QString timeline, QString listID);

        void locationsGetList();

        void settingsGetList();

        void tasksAdd(QString timeline, QString taskName, QString listID = "");
        void tasksSmartAdd(QString timeline, QString taskName, QString listID = "");
        void tasksAddTags(QString timeline, QString listID, QString taskSeriesID, QString taskID, QString tags);
        void tasksComplete(QString timeline, QString listID, QString taskSeriesID, QString taskID);
        void tasksDelete(QString timeline, QString listID, QString taskSeriesID, QString taskID);
        void tasksGetList();
        void tasksGetSmartList(QString id, QString filter);
        void tasksMovePriority(QString timeline, QString listID, QString taskSeriesID, QString taskID, QString direction);
        void tasksMoveTo(QString timeline, QString fromListID, QString toListID, QString taskSeriesID, QString taskID);
        void tasksPostpone(QString timeline, QString listID, QString taskSeriesID, QString taskID);
        void tasksRemoveTags(QString timeline, QString listID, QString taskSeriesID, QString taskID, QString tags);
        void tasksSetDueDate(QString timeline, QString listID, QString taskSeriesID, QString taskID);
        void tasksSetDueDate(QString timeline, QString listID, QString taskSeriesID, QString taskID, QMap<QString, QString> optArgs);
        void tasksSetEstimate(QString timeline, QString listID, QString taskSeriesID, QString taskID, QString estimate = "");
        void tasksSetLocation(QString timeline, QString listID, QString taskSeriesID, QString taskID, QString locationID = "");
        void tasksSetName(QString timeline, QString listID, QString taskSeriesID, QString taskID, QString taskName);
        void tasksSetPriority(QString timeline, QString listID, QString taskSeriesID, QString taskID, QString priority = "");
        void tasksSetRecurrence(QString timeline, QString listID, QString taskSeriesID, QString taskID, QString repeat = "");
        void tasksSetTags(QString timeline, QString listID, QString taskSeriesID, QString taskID, QString tags = "");
        void tasksSetUrl(QString timeline, QString listID, QString taskSeriesID, QString taskID, QString url = "");
        void tasksUncomplete(QString timeline, QString listID, QString taskSeriesID, QString taskID);
        void tasksNotesAdd(QString timeline, QString listID, QString taskSeriesID, QString taskID, QString noteTitle, QString noteText);
        void tasksNotesDelete(QString timeline, QString noteID);
        void tasksNotesEdit(QString timeline, QString noteID, QString noteTitle, QString noteText);

        void timeConvert(QString toTimezone);
        void timeConvert(QString toTimezone, QMap<QString, QString> optArgs);
        void timeParse(QString text);
        void timeParse(QString text, QMap<QString, QString> optArgs);

        void timelinesCreate();

        void timezonesGetList();

        void transactionsUndo(QString timeline, QString transactionID);

        void testLogin();

    private slots:
        void onAuthFinished();
        void onAuthError();
        void onCheckTokenFinished(QVariantMap response, RTM::ResponseStatus status);
        void onTasksGetSmartListFinished(QVariantMap response, RTM::ResponseStatus status);

    private:
        class Private;
        Private *const d;
    };
}

#endif // SERVICE_H
