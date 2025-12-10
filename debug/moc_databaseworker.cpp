/****************************************************************************
** Meta object code from reading C++ file 'databaseworker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../thread/databaseworker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'databaseworker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DatabaseWorker_t {
    QByteArrayData data[15];
    char stringdata0[262];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DatabaseWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DatabaseWorker_t qt_meta_stringdata_DatabaseWorker = {
    {
QT_MOC_LITERAL(0, 0, 14), // "DatabaseWorker"
QT_MOC_LITERAL(1, 15, 21), // "pickedProducdataReady"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 25), // "QList<pickedProduct_Type>"
QT_MOC_LITERAL(4, 64, 8), // "products"
QT_MOC_LITERAL(5, 73, 20), // "RawInspectcdataReady"
QT_MOC_LITERAL(6, 94, 23), // "QList<RawInspectionRow>"
QT_MOC_LITERAL(7, 118, 16), // "RawInspectionRow"
QT_MOC_LITERAL(8, 135, 15), // "sensorDataReady"
QT_MOC_LITERAL(9, 151, 22), // "QList<SensorData_Type>"
QT_MOC_LITERAL(10, 174, 20), // "weighbridgeDataReady"
QT_MOC_LITERAL(11, 195, 26), // "QList<WeighRecordViewType>"
QT_MOC_LITERAL(12, 222, 12), // "weighRecords"
QT_MOC_LITERAL(13, 235, 13), // "databaseError"
QT_MOC_LITERAL(14, 249, 12) // "errorMessage"

    },
    "DatabaseWorker\0pickedProducdataReady\0"
    "\0QList<pickedProduct_Type>\0products\0"
    "RawInspectcdataReady\0QList<RawInspectionRow>\0"
    "RawInspectionRow\0sensorDataReady\0"
    "QList<SensorData_Type>\0weighbridgeDataReady\0"
    "QList<WeighRecordViewType>\0weighRecords\0"
    "databaseError\0errorMessage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DatabaseWorker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       5,    1,   42,    2, 0x06 /* Public */,
       8,    1,   45,    2, 0x06 /* Public */,
      10,    1,   48,    2, 0x06 /* Public */,
      13,    1,   51,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9,    4,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, QMetaType::QString,   14,

       0        // eod
};

void DatabaseWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DatabaseWorker *_t = static_cast<DatabaseWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->pickedProducdataReady((*reinterpret_cast< const QList<pickedProduct_Type>(*)>(_a[1]))); break;
        case 1: _t->RawInspectcdataReady((*reinterpret_cast< const QList<RawInspectionRow>(*)>(_a[1]))); break;
        case 2: _t->sensorDataReady((*reinterpret_cast< const QList<SensorData_Type>(*)>(_a[1]))); break;
        case 3: _t->weighbridgeDataReady((*reinterpret_cast< const QList<WeighRecordViewType>(*)>(_a[1]))); break;
        case 4: _t->databaseError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<pickedProduct_Type> >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<RawInspectionRow> >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<SensorData_Type> >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<WeighRecordViewType> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DatabaseWorker::*_t)(const QList<pickedProduct_Type> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DatabaseWorker::pickedProducdataReady)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (DatabaseWorker::*_t)(const QList<RawInspectionRow> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DatabaseWorker::RawInspectcdataReady)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (DatabaseWorker::*_t)(const QList<SensorData_Type> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DatabaseWorker::sensorDataReady)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (DatabaseWorker::*_t)(const QList<WeighRecordViewType> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DatabaseWorker::weighbridgeDataReady)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (DatabaseWorker::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DatabaseWorker::databaseError)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject DatabaseWorker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DatabaseWorker.data,
      qt_meta_data_DatabaseWorker,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DatabaseWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DatabaseWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DatabaseWorker.stringdata0))
        return static_cast<void*>(const_cast< DatabaseWorker*>(this));
    return QObject::qt_metacast(_clname);
}

int DatabaseWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void DatabaseWorker::pickedProducdataReady(const QList<pickedProduct_Type> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DatabaseWorker::RawInspectcdataReady(const QList<RawInspectionRow> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DatabaseWorker::sensorDataReady(const QList<SensorData_Type> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DatabaseWorker::weighbridgeDataReady(const QList<WeighRecordViewType> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void DatabaseWorker::databaseError(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
