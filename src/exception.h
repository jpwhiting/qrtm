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

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "rtm.h"

class QString;

namespace RTM
{
    class RTMAPISHARED_EXPORT Exception
    {
    public:
	Exception(RTM::ErrorCode eCode = RTM::Malformed, QString eMessage = "", QMap<QString, QString> args = QMap<QString, QString>());

    protected:
	RTM::ErrorCode code;
	QString message;
	QMap<QString, QString> arguments;
    };
}

#endif // EXCEPTION_H
