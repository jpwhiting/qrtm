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

#include "authentication.h"
#include <QtCore/QDebug>
#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtCore/QVariantMap>
#include <QtGui/QWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QPushButton>
#include <QtWebKit/QWebView>

RTM::Authentication::Authentication(QString key, QString sharedSecret, RTM::Permission perms, QString token, QObject *parent) :
	RTM::Request(sharedSecret, RTM::baseAuthUrl, RTM::Signed, parent), apiKey(key), token(token), permission(perms)
{
}

void RTM::Authentication::setApiKey(QString key)
{
    apiKey = key;
}

void RTM::Authentication::setSharedSecret(QString secret)
{
    sharedSecret = secret;
}

void RTM::Authentication::setPermission(RTM::Permission perm)
{
    permission = perm;
}

void RTM::Authentication::setToken(QString tok) {
    token = tok;
}

QString RTM::Authentication::getApiKey()
{
    return apiKey;
}

QString RTM::Authentication::getSharedSecret()
{
    return sharedSecret;
}

RTM::Permission RTM::Authentication::getPermission()
{
    return permission;
}

QString RTM::Authentication::getToken()
{
    return token;
}

void RTM::Authentication::beginAuth()
{
    if(frob.isEmpty()) {
        qDebug() << "Frob empty, new frob requested\n";
        frobRequest = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
	connect(frobRequest, SIGNAL(requestFinished(QVariantMap, RTM::ResponseStatus)), this, SLOT(frobReceived(QVariantMap, RTM::ResponseStatus)));
        frobRequest->addArgument("api_key", apiKey);
        frobRequest->addArgument("method", "rtm.auth.getFrob");
        frobRequest->sendRequest();
    }
    else {
        login();
    }
}

void RTM::Authentication::frobReceived(QVariantMap response, RTM::ResponseStatus status)
{
    if(status == RTM::OK) {
	frob = response["frob"].toString();
	qDebug() << "Frob: " << frob << " received\n";
	login();
    }
    else {
	emit authError(response, status);
    }
}

void RTM::Authentication::login()
{
    qDebug() << "Login and authorize\n";
    QWidget * loginWidget = new QWidget();
    QVBoxLayout * layout = new QVBoxLayout(loginWidget);
    QPushButton * button = new QPushButton(loginWidget);
    QWebView * loginPage  = new QWebView(loginWidget);

    button->setText("Click after authorization completed");

    clearArguments();
    addArgument("api_key", apiKey);
    addArgument("perms", getPermission(permission));
    addArgument("frob", frob);

    loginPage->setUrl(prepareUrl());
    qDebug() << "Login URL:" << loginPage->url().toString() << "\n";
    loginPage->resize(800, 600);
    loginPage->scroll(0, 200);

    layout->addWidget(loginPage);
    layout->addWidget(button);

    connect(button, SIGNAL(clicked(bool)), loginWidget, SLOT(hide()));
    connect(button, SIGNAL(clicked(bool)), loginWidget, SLOT(deleteLater()));
    connect(button, SIGNAL(clicked(bool)), this, SLOT(requestToken()));

    loginWidget->show();
}

void RTM::Authentication::requestToken()
{
    qDebug() << "Authorization completed get token\n";

    tokenRequest = new RTM::Request(sharedSecret, RTM::baseMethodUrl, RTM::Signed, this);
    connect(tokenRequest, SIGNAL(requestFinished(QVariantMap, RTM::ResponseStatus)), this, SLOT(tokenReceived(QVariantMap, RTM::ResponseStatus)));
    tokenRequest->addArgument("api_key", apiKey);
    tokenRequest->addArgument("frob", frob);
    tokenRequest->addArgument("method", "rtm.auth.getToken");
    tokenRequest->sendRequest();
}

void RTM::Authentication::tokenReceived(QVariantMap response, RTM::ResponseStatus status)
{
    if(status == RTM::OK) {
	token = (response["auth"].toMap())["token"].toString();
	qDebug() << "Token: " << token << " received\n";
	emit authFinished(response["auth"].toMap());
    }
    else
	emit authError(response, status);
}

QString RTM::Authentication::getPermission(RTM::Permission p)
{
    switch(p) {
    case RTM::Read:
        return "read";
    case RTM::Write:
        return "write";
    case RTM::Delete:
        return "delete";
    default:
        return "";
    }
}
