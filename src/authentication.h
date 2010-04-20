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

#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include "rtm.h"
#include "request.h"
#include "rtmexception.h"

class QString;

namespace RTM
{
    class RTMAPISHARED_EXPORT Authentication : public RTM::Request
    {
        Q_OBJECT

    public:
	Authentication(QString key, QString secret, RTM::Permission perms, QString token = "", QObject *parent = 0);
        QString getToken();
    protected:
        QString getPermission(RTM::Permission p);

    signals:
        void authFinished(QVariantMap auth);
        void authError(RTM::RtmException ex);

    public slots:
        void beginAuth();

    protected slots:
        void frobReceived(QVariantMap response);
        void login();
        void requestToken();
        void tokenReceived(QVariantMap response);

    protected:
	QString apiKey;
	QString frob;
	QString token;
	RTM::Permission permission;
        RTM::Request * frobRequest;
        RTM::Request * tokenRequest;
    };
}

#endif // AUTHENTICATION_H
