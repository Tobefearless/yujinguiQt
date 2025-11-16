/****************************************************************************
** Meta object code from reading C++ file 'distortsubwindow2.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../distort/distortsubwindow2.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'distortsubwindow2.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DistortsubWindow2_t {
    QByteArrayData data[9];
    char stringdata0[152];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DistortsubWindow2_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DistortsubWindow2_t qt_meta_stringdata_DistortsubWindow2 = {
    {
QT_MOC_LITERAL(0, 0, 17), // "DistortsubWindow2"
QT_MOC_LITERAL(1, 18, 11), // "startThread"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 24), // "updatePickedProductTable"
QT_MOC_LITERAL(4, 56, 25), // "QList<pickedProduct_Type>"
QT_MOC_LITERAL(5, 82, 8), // "products"
QT_MOC_LITERAL(6, 91, 21), // "updateRawInspectTable"
QT_MOC_LITERAL(7, 113, 23), // "QList<RawInspectionRow>"
QT_MOC_LITERAL(8, 137, 14) // "startKeepAlive"

    },
    "DistortsubWindow2\0startThread\0\0"
    "updatePickedProductTable\0"
    "QList<pickedProduct_Type>\0products\0"
    "updateRawInspectTable\0QList<RawInspectionRow>\0"
    "startKeepAlive"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DistortsubWindow2[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   35,    2, 0x08 /* Private */,
       6,    1,   38,    2, 0x08 /* Private */,
       8,    0,   41,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 7,    5,
    QMetaType::Void,

       0        // eod
};

void DistortsubWindow2::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DistortsubWindow2 *_t = static_cast<DistortsubWindow2 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startThread(); break;
        case 1: _t->updatePickedProductTable((*reinterpret_cast< const QList<pickedProduct_Type>(*)>(_a[1]))); break;
        case 2: _t->updateRawInspectTable((*reinterpret_cast< const QList<RawInspectionRow>(*)>(_a[1]))); break;
        case 3: _t->startKeepAlive(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<pickedProduct_Type> >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<RawInspectionRow> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DistortsubWindow2::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DistortsubWindow2::startThread)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject DistortsubWindow2::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DistortsubWindow2.data,
      qt_meta_data_DistortsubWindow2,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DistortsubWindow2::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DistortsubWindow2::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DistortsubWindow2.stringdata0))
        return static_cast<void*>(const_cast< DistortsubWindow2*>(this));
    return QDialog::qt_metacast(_clname);
}

int DistortsubWindow2::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void DistortsubWindow2::startThread()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
