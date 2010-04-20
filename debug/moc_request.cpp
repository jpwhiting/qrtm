/****************************************************************************
** Meta object code from reading C++ file 'request.h'
**
** Created: Sun 18. Apr 00:41:53 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/request.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'request.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RTM__Request[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      25,   14,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      51,   47,   13,   13, 0x0a,
      77,   47,   69,   13, 0x0a,
     105,   99,   13,   13, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_RTM__Request[] = {
    "RTM::Request\0\0successful\0requestFinished(bool)\0"
    "url\0sendRequest(QUrl)\0QString\0"
    "sendSyncRequest(QUrl)\0reply\0"
    "responseReceived(QNetworkReply*)\0"
};

const QMetaObject RTM::Request::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_RTM__Request,
      qt_meta_data_RTM__Request, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RTM::Request::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RTM::Request::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RTM::Request::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RTM__Request))
        return static_cast<void*>(const_cast< Request*>(this));
    return QObject::qt_metacast(_clname);
}

int RTM::Request::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: requestFinished((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: sendRequest((*reinterpret_cast< QUrl(*)>(_a[1]))); break;
        case 2: { QString _r = sendSyncRequest((*reinterpret_cast< QUrl(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 3: responseReceived((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void RTM::Request::requestFinished(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
