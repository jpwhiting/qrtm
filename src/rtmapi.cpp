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

#include "rtmapi.h"

#include <QtCore/QByteArray>
#include <QtCore/QCryptographicHash>
#include <QtCore/QDebug>
#include <QtCore/QMap>
#include <QtCore/QMapIterator>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QWebView>
#include "libqjson/parser.h">
#include "loginview.h"

RtmAPI::RtmAPI(QString apikey, QString secret, QObject * parent) : QObject(parent), API_KEY(apikey), SECRET(secret), networkAccessManager(this)
{
    connect(&networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getResponse(QNetworkReply*)));
}

QString RtmAPI::generateSignedQuery(QMap<QString, QString> &args)
{
    QCryptographicHash encrypter(QCryptographicHash::Md5);

    QString raw;
    QString queryString;
    if(args.contains("loginURL")) {
	queryString = args.value("loginURL");
	args.remove("loginURL");
    }
    else {
	queryString = API_URL;
    }

    args.insert("api_key", API_KEY);
    args.insert("format", "json");
    QMapIterator<QString, QString> it(args);

    while(it.hasNext()) {
	it.next();
	raw += it.key() + it.value();
	queryString += it.key() + "=" + it.value() + "&";
    }

    raw = SECRET + raw;
    return queryString + "api_sig=" + QString(encrypter.hash(raw.toAscii(), QCryptographicHash::Md5).toHex());
}

QString RtmAPI::getFrob()
{
    bool ok;
    QVariantMap parsedData;
    QMap<QString, QString> args;

    QJson::Parser parser;

    args.insert("method","rtm.auth.getFrob");
    request(generateSignedQuery(args));
    parsedData = parser.parse(response, &ok).toMap();

    if(ok)
	return frob = (parsedData["rsp"].toMap())["frob"].toString();
    else
	return frob = "";
}

QString RtmAPI::getToken()
{
    /*bool ok;
    QVariantMap parsedData;
    QMap<QString, QString> args;

    QJson::Parser parser;

    args.insert("frob", frob);
    args.insert("method","rtm.auth.getToken");
    request(generateSignedQuery(args));
    parsedData = parser.parse(response, &ok).toMap();

    if(ok)
	return frob = ((parsedData["rsp"].toMap())["auth"].toMap())["token"].toString();
    else
	return "";
	*/
    return frob = "0db250fd5d48ce807f9675f5aa6bd7624518f8dd";
}

QString RtmAPI::testLogin()
{
    bool ok;
    QVariantMap parsedData;
    QMap<QString, QString> args;

    QJson::Parser parser;

    args.insert("auth_token", frob);
    args.insert("method","rtm.test.login");
    QString url = generateSignedQuery(args);
    qDebug() << "TEST: " << url;
    request(url);
    parsedData = parser.parse(response, &ok).toMap();

    if(ok)
	//return (parsedData["auth"].toMap())["token"].toString();
	return response;
    else
	return "";
}

void RtmAPI::request(QString url)
{
    qDebug() << url << "\n";
    networkAccessManager.get(QNetworkRequest(QUrl(url)));

    loop.exec();
}

void RtmAPI::getResponse(QNetworkReply *reply)
{
    QByteArray byteResponse;
    byteResponse = reply->readAll();
    QString stringResponse;
    stringResponse = QString(byteResponse);
    response = stringResponse;
    loop.exit();
}

void RtmAPI::loginSuccessful(bool successful)
{
    loop.exit();
    if(successful)
	qDebug() << "SUCCESSFUL\n";
    else
	qDebug() << "FAILED\n";
}

void RtmAPI::login(QString windowTitle)
{
    QMap<QString, QString> args;
    LoginView browser;
    // TODO windowICON
    browser.setWindowTitle(windowTitle);
    connect(&browser, SIGNAL(windowClosed(bool)), this, SLOT(loginSuccessful(bool)));

    args.insert("perms", "delete");
    args.insert("frob", getFrob());
    args.insert("loginURL", LOGIN_URL);
    QString s = generateSignedQuery(args);
    qDebug() << "LOGIN: " << s;
    browser.load(QUrl(s));
    browser.show();
    loop.exec();
}


