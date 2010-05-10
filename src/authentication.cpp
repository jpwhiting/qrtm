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
#include <QtGui/QWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QPushButton>
#include <QtWebKit/QWebView>

using namespace RTM;

Authentication::Authentication(QString key, QString sharedSecret, Permission perms, QString token, QObject *parent) :
    Request(sharedSecret, baseAuthUrl, Signed, parent), apiKey(key), token(token), permission(perms)
{
}

void Authentication::setApiKey(QString key)
{
    apiKey = key;
}

void Authentication::setSharedSecret(QString secret)
{
    sharedSecret = secret;
}

void Authentication::setPermission(Permission perm)
{
    permission = perm;
}

void Authentication::setToken(QString tok) {
    token = tok;
}

QString Authentication::getApiKey()
{
    return apiKey;
}

QString Authentication::getSharedSecret()
{
    return sharedSecret;
}

Permission Authentication::getPermission()
{
    return permission;
}

QString Authentication::getToken()
{
    return token;
}

void Authentication::beginAuth()
{
    if(frob.isEmpty()) {
        qDebug() << "Frob empty, new frob requested\n";
        frobRequest = new Request(sharedSecret, baseMethodUrl, Signed, this);
        connect(frobRequest, SIGNAL(requestFinished(QVariantMap, ResponseStatus)), this, SLOT(frobReceived(QVariantMap, ResponseStatus)));
        frobRequest->addArgument("api_key", apiKey);
        frobRequest->addArgument("method", "rtm.auth.getFrob");
        frobRequest->sendRequest();
    }
    else {
        login();
    }
}

void Authentication::frobReceived(QVariantMap response, ResponseStatus status)
{
    if(status == OK) {
        frob = response["frob"].toString();
        qDebug() << "Frob: " << frob << " received\n";
        login();
    }
    else {
        emit authError(response, status);
    }
}

void Authentication::login()
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

void Authentication::requestToken()
{
    qDebug() << "Authorization completed get token\n";

    tokenRequest = new Request(sharedSecret, baseMethodUrl, Signed, this);
    connect(tokenRequest, SIGNAL(requestFinished(QVariantMap, ResponseStatus)), this, SLOT(tokenReceived(QVariantMap, ResponseStatus)));
    tokenRequest->addArgument("api_key", apiKey);
    tokenRequest->addArgument("frob", frob);
    tokenRequest->addArgument("method", "rtm.auth.getToken");
    tokenRequest->sendRequest();
}

void Authentication::tokenReceived(QVariantMap response, ResponseStatus status)
{
    if(status == OK) {
        token = (response["auth"].toMap())["token"].toString();
        qDebug() << "Token: " << token << " received\n";
        emit authFinished(response["auth"].toMap());
    }
    else
        emit authError(response, status);
}

QString Authentication::getPermission(Permission p)
{
    switch(p) {
    case Read:
        return "read";
    case Write:
        return "write";
    case Delete:
        return "delete";
    default:
        return "";
    }
}
