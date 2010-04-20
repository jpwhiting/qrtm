/****************************************************************************
** Meta object code from reading C++ file 'rtmapi.h'
**
** Created: Sun 11. Apr 05:22:39 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/rtmapi.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rtmapi.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RtmAPI[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,    8,    7,    7, 0x08,
      53,   42,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_RtmAPI[] = {
    "RtmAPI\0\0reply\0getResponse(QNetworkReply*)\0"
    "successful\0loginSuccessful(bool)\0"
};

const QMetaObject RtmAPI::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_RtmAPI,
      qt_meta_data_RtmAPI, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RtmAPI::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RtmAPI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RtmAPI::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RtmAPI))
        return static_cast<void*>(const_cast< RtmAPI*>(this));
    return QObject::qt_metacast(_clname);
}

int RtmAPI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: getResponse((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 1: loginSuccessful((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
