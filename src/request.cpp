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

#include "request.h"
#include <QtCore/QCryptographicHash>
#include <QtCore/QDebug>
#include <QtCore/QMap>
#include <QtCore/QMapIterator>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

using namespace RTM;

Request::Request(QString secret, QString baseURL, MethodType rType, QObject *parent) :
    QObject(parent), baseUrl(baseURL), sharedSecret(secret), accessManager(new QNetworkAccessManager(this)), type(rType)
{
    connect(accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(responseReceived(QNetworkReply *)));
}

void Request::addArgument(QString key, QString value)
{
    arguments.insert(key, value);
}

void Request::clearArguments()
{
    arguments.clear();
}

void Request::setSecret(QString secret)
{
    sharedSecret = secret;
}

void Request::setType(MethodType t)
{
    type = t;
}

QUrl Request::prepareUrl()
{
    arguments.insert("format", "json");
    QString url = baseUrl;

    if(type == Signed) {
        signRequest();
    }
    else {
        unsignRequest();
    }
    QMapIterator<QString, QString> it(arguments);

    while(it.hasNext()) {
        it.next();
        url.append(it.key());
        url.append("=");
        url.append(it.value());
        url.append("&");
    }
    return QUrl(url);
}

void Request::signRequest()
{
    QString rawSign = sharedSecret;
    QMapIterator<QString, QString> it(arguments);

    if(arguments.find("api_sig") == arguments.end()) {
        while(it.hasNext()) {
            it.next();
            rawSign.append(it.key());
            rawSign.append(it.value());
        }

        arguments.insert("api_sig", QString(QCryptographicHash::hash(rawSign.toAscii(), QCryptographicHash::Md5).toHex()));
    }
}

void Request::unsignRequest()
{
    arguments.remove("api_sig");
}

void Request::sendRequest()
{
    accessManager->get(QNetworkRequest(prepareUrl()));
}

QString Request::sendSyncRequest(QUrl url)
{
    // TODO if necessary

    return url.toString();
}

void Request::responseReceived(QNetworkReply * reply)
{
    bool ok;
    QVariantMap result;
    QByteArray response = reply->readAll();

    qDebug() << "Resp url: " << reply->url().toString();
    qDebug() << "Resp rec: " << QString(response);

    reply->deleteLater();

    result = (jsonParser.parse(response, &ok).toMap())["rsp"].toMap();

    if(ok) {
        QString status = result["stat"].toString();

        if(status == "ok") {
            emit requestFinished(result, OK);
        }
        else {
            emit requestFinished(result, Fail);
        }
    }
    else {
        emit requestFinished(result, Malformed);
    }
}
