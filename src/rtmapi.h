#ifndef RTMAPI_H
#define RTMAPI_H
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

#include "rtmapi_global.h"
#include <parser.h>
#include <QObject>
#include <QtCore/QEventLoop>
#include <QtNetwork/QNetworkAccessManager>

#define API_URL "http://api.rememberthemilk.com/services/rest/?"
#define LOGIN_URL "http://www.rememberthemilk.com/services/auth/?"


template <class Key, class T> class QMap;
class QString;
class QEventLoop;
class QNetworkAccessManager;
class QNetworkReply;

class RTMAPISHARED_EXPORT RtmAPI : public QObject {
    Q_OBJECT

public:
    RtmAPI(QString apikey, QString secret, QObject * parent = 0);
    void login(QString windowTitle);
    QString getFrob();
    QString getToken();
    QString testLogin();

private:
    QString generateSignedQuery(QMap<QString, QString> &args);
    void request(QString url);

private slots:
    void getResponse(QNetworkReply * reply);
    void loginSuccessful(bool successful);

private:
    QString API_KEY;
    QString SECRET;
    QNetworkAccessManager networkAccessManager;
    QEventLoop loop;
    QString response;
    QString frob;

};

#endif // RTMAPI_H
