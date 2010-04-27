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

#ifndef SERVICE_H
#define SERVICE_H

#include "rtm.h"
#include "authentication.h"
#include "libqjson/parser.h"
#include <QObject>
#include <QtCore/QTime>

namespace RTM {

    class RTMAPISHARED_EXPORT Service : public QObject
    {
	Q_OBJECT

    public:
	Service(QString key, QString secret, RTM::Permission perms, QString token = "", QObject *parent = 0);

    protected:

    signals:
	void authCheckTokenFinished(bool successful, bool valid);
	void authGetTokenFinished(bool successful, QString token);
	void contactsAddFinished(bool successful);
	void contactsDeleteFinished(bool successful);
	void contactsGetListFinished(bool successful);
	void groupsAddFinished(bool successful);
	void groupsAddContactFinished(bool successful);
	void groupsDeleteFinished(bool successful);
	void groupsGetListFinished(bool successful);
	void groupsremoveContactFinished(bool successful);
	void listsAddFinished(bool successful);
	void listsArchiveFinished(bool successful);
	void listsDeleteFinished(bool successful);
	void listsGetListFinished(bool successful);
	void listsSetDefaultListFinished(bool successful);
	void listsSetNameFinished(bool successful);
	void listsUnarchiveFinished(bool successful);
	void locationsGetListFinished(bool successful);
	void settingsGetListFinished(bool successful);
	void tasksAddFinished(bool successful);
	void tasksAddTagsFinished(bool successful);
	void tasksCompleteFinished(bool successful);
	void tasksDeleteFinished(bool successful);
	void tasksGetListFinished(bool successful);
	void tasksMovePriorityFinished(bool successful);
	void tasksMoveToFinished(bool successful);
	void tasksPostponeFinished(bool successful);
	void tasksRemoveTagsFinished(bool successful);
	void tasksSetDueDateFinished(bool successful);
	void tasksSetEstimateFinished(bool successful);
	void tasksSetLocationFinished(bool successful);
	void tasksSetNameFinished(bool successful);
	void tasksSetPriorityFinished(bool successful);
	void tasksSetRecurrenceFinished(bool successful);
	void tasksSetTagsFinished(bool successful);
	void tasksSetUrlFinished(bool successful);
	void tasksUncompleteFinished(bool successful);
	void tasksNotesAddFinished(bool successful);
	void tasksNotesDeleteFinished(bool successful);
	void tasksNotesEditFinished(bool successful);
	void timeConvertFinished(bool successful);
	void timeParseFinished(bool successful);
	void timelinesCreateFinished(bool successful);
	void timezonesGetListFinished(bool successful);
	void transactionsUndoFinished(bool successful);

    public slots:
	void authCheckToken();
	void authGetToken();
	void contactsAdd();
	void contactsDelete();
	void contactsGetList();
	void groupsAdd();
	void groupsAddContact();
	void groupsDelete();
	void groupsGetList();
	void groupsremoveContact();
	void listsAdd();
	void listsArchive();
	void listsDelete();
	void listsGetList();
	void listsSetDefaultList();
	void listsSetName();
	void listsUnarchive();
	void locationsGetList();
	void settingsGetList();
	void tasksAdd();
	void tasksAddTags();
	void tasksComplete();
	void tasksDelete();
	void tasksGetList();
	void tasksMovePriority();
	void tasksMoveTo();
	void tasksPostpone();
	void tasksRemoveTags();
	void tasksSetDueDate();
	void tasksSetEstimate();
	void tasksSetLocation();
	void tasksSetName();
	void tasksSetPriority();
	void tasksSetRecurrence();
	void tasksSetTags();
	void tasksSetUrl();
	void tasksUncomplete();
	void tasksNotesAdd();
	void tasksNotesDelete();
	void tasksNotesEdit();
	void timeConvert();
	void timeParse();
	void timelinesCreate();
	void timezonesGetList();
	void transactionsUndo();

    protected slots:

    protected:
	RTM::Authentication authentication;
	QTime lastAttempt;
	QJson::Parser jsonParser;

    };
}

#endif // SERVICE_H
