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

namespace RTM
{
    class Authentication : public Request
    {
        Q_OBJECT

    public:
        Authentication(QString key, QString secret, Permission perms, QString token = "", QObject *parent = 0);
        void setApiKey(QString key);
        void setSharedSecret(QString secret);
        void setPermission(Permission perm);
        void setToken(QString tok);
        QString getApiKey();
        QString getSharedSecret();
        Permission getPermission();
        QString getToken();

    protected:
        QString getPermission(Permission p);

    signals:
        void authFinished(QVariantMap auth);
        void authError(QVariantMap response, ResponseStatus status);

    public slots:
        void beginAuth();

    protected slots:
        void frobReceived(QVariantMap response, ResponseStatus status);
        void login();
        void requestToken();
        void tokenReceived(QVariantMap response, ResponseStatus status);

    protected:
        QString apiKey;
        QString frob;
        QString token;
        Permission permission;
        Request * frobRequest;
        Request * tokenRequest;
    };
}

#endif // AUTHENTICATION_H
