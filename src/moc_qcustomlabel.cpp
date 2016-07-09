/****************************************************************************
** Meta object code from reading C++ file 'qcustomlabel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qcustomlabel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qcustomlabel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QCustomLabel_t {
    QByteArrayData data[9];
    char stringdata[114];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QCustomLabel_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QCustomLabel_t qt_meta_stringdata_QCustomLabel = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 9),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 18),
QT_MOC_LITERAL(4, 43, 19),
QT_MOC_LITERAL(5, 63, 13),
QT_MOC_LITERAL(6, 77, 10),
QT_MOC_LITERAL(7, 88, 12),
QT_MOC_LITERAL(8, 101, 11)
    },
    "QCustomLabel\0Mouse_Pos\0\0Mouse_Left_Pressed\0"
    "Mouse_Right_Pressed\0Mouse_Release\0"
    "Mouse_Left\0Mouse_Scroll\0Key_Pressed\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QCustomLabel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06,
       3,    0,   50,    2, 0x06,
       4,    0,   51,    2, 0x06,
       5,    0,   52,    2, 0x06,
       6,    0,   53,    2, 0x06,
       7,    0,   54,    2, 0x06,
       8,    0,   55,    2, 0x06,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QCustomLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QCustomLabel *_t = static_cast<QCustomLabel *>(_o);
        switch (_id) {
        case 0: _t->Mouse_Pos(); break;
        case 1: _t->Mouse_Left_Pressed(); break;
        case 2: _t->Mouse_Right_Pressed(); break;
        case 3: _t->Mouse_Release(); break;
        case 4: _t->Mouse_Left(); break;
        case 5: _t->Mouse_Scroll(); break;
        case 6: _t->Key_Pressed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QCustomLabel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QCustomLabel::Mouse_Pos)) {
                *result = 0;
            }
        }
        {
            typedef void (QCustomLabel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QCustomLabel::Mouse_Left_Pressed)) {
                *result = 1;
            }
        }
        {
            typedef void (QCustomLabel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QCustomLabel::Mouse_Right_Pressed)) {
                *result = 2;
            }
        }
        {
            typedef void (QCustomLabel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QCustomLabel::Mouse_Release)) {
                *result = 3;
            }
        }
        {
            typedef void (QCustomLabel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QCustomLabel::Mouse_Left)) {
                *result = 4;
            }
        }
        {
            typedef void (QCustomLabel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QCustomLabel::Mouse_Scroll)) {
                *result = 5;
            }
        }
        {
            typedef void (QCustomLabel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QCustomLabel::Key_Pressed)) {
                *result = 6;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject QCustomLabel::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_QCustomLabel.data,
      qt_meta_data_QCustomLabel,  qt_static_metacall, 0, 0}
};


const QMetaObject *QCustomLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCustomLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QCustomLabel.stringdata))
        return static_cast<void*>(const_cast< QCustomLabel*>(this));
    return QLabel::qt_metacast(_clname);
}

int QCustomLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void QCustomLabel::Mouse_Pos()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QCustomLabel::Mouse_Left_Pressed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void QCustomLabel::Mouse_Right_Pressed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void QCustomLabel::Mouse_Release()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void QCustomLabel::Mouse_Left()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void QCustomLabel::Mouse_Scroll()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void QCustomLabel::Key_Pressed()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}
QT_END_MOC_NAMESPACE
