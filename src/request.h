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

#ifndef REQUEST_H
#define REQUEST_H

#include "rtm.h"
#include <qjson/parser.h>

#include <QtCore/QObject>
#include <QtCore/QUrl>
#include <QtCore/QVariantMap>

class QNetworkAccessManager;
class QNetworkReply;
template <class x, class y> class QMap;

namespace RTM
{
    class Request : public QObject
    {
        Q_OBJECT

    public:
        Request(QString secret, QString baseURL = baseMethodUrl, MethodType rType = Signed, QObject *parent = 0);
        void addArgument(QString key, QString value);
        void clearArguments();
        void setSecret(QString secret);
        void setType(MethodType t);
    protected:
        QUrl prepareUrl();
        void signRequest();
        void unsignRequest();

    signals:
        void requestFinished(QVariantMap response, RTM::ResponseStatus status);

    public slots:
        void sendRequest();
        QString sendSyncRequest(QUrl url);

    protected slots:
        void responseReceived(QNetworkReply * reply);

    protected:
        QMap<QString, QString> arguments;
        QString baseUrl;
        QString sharedSecret;
        QNetworkAccessManager * accessManager;
        MethodType type;
        QJson::Parser jsonParser;
    };
}

#endif // REQUEST_H
