#include <QString>
#include <QStringList>
#include <QStringListIterator>
#include <QVariantMap>

namespace JSONParser {
    QVariant parse(QString json, bool &valid)
    {
	QVariant parsedData;
	bool validJson = false;

	if(json.startsWith('{', Qt::CaseInsensitive) && json.endsWith('}', Qt::CaseInsensitive)) {
	    parsedData = parsePairs(json, &validJson);
	}
	else if(json.startsWith('[', Qt::CaseInsensitive) && json.endsWith(']', Qt::CaseInsensitive)) {
	    parsedData = parseArray(json, &validJson);
	}
	else;

	if(!validJson) {
	    valid = validJson;
	    parsedData = QVariant(false);
	}

	return parsedData;
    }

    QVariant parsePairs(QString json, bool &valid)
    {
	QVariant parsedData;
	QVariantMap dict;
	bool validJson = false;
	QStringList pairs = json.split(',', QString::SkipEmptyParts);
	QStringListIterator it(pairs);



    }


}
