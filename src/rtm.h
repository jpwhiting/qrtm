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

#ifndef RTM_H
#define RTM_H

#include "libqrtm_global.h"
#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtCore/QVariantMap>
#include "libqjson/parser.h"

namespace RTM
{
    enum MethodType {Signed, Unsigned};
    enum Permission {Read, Write, Delete};
    enum ErrorCode {Malformed = 0, WrongAPIKey = 90, Sign = 12, Etc};

    const QString baseMethodUrl = "http://api.rememberthemilk.com/services/rest/?";
    const QString baseAuthUrl = "http://www.rememberthemilk.com/services/auth/?";

}

#endif // RTM_H
