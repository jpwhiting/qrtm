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

#ifndef RTMSERVICE_H
#define RTMSERVICE_H

#include "rtm.h"
#include "authentication.h"
#include "libqjson/parser.h"
#include <QObject>
#include <QtCore/QTime>

namespace RTM {

    class RTMAPISHARED_EXPORT RtmService : public QObject
    {
	Q_OBJECT

    public:
	RtmService(QString key, QString secret, RTM::Permission perms, QString token = "", QObject *parent = 0);

    protected:

    signals:

    public slots:

    protected slots:

    protected:
	RTM::Authentication authentication;
	QTime lastAttempt;
	QJson::Parser jsonParser;

    };
}

#endif // RTMSERVICE_H
