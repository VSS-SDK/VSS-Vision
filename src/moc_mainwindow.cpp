/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[20];
    char stringdata[258];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 15),
QT_MOC_LITERAL(2, 27, 0),
QT_MOC_LITERAL(3, 28, 16),
QT_MOC_LITERAL(4, 45, 17),
QT_MOC_LITERAL(5, 63, 13),
QT_MOC_LITERAL(6, 77, 10),
QT_MOC_LITERAL(7, 88, 14),
QT_MOC_LITERAL(8, 103, 9),
QT_MOC_LITERAL(9, 113, 14),
QT_MOC_LITERAL(10, 128, 13),
QT_MOC_LITERAL(11, 142, 13),
QT_MOC_LITERAL(12, 156, 10),
QT_MOC_LITERAL(13, 167, 10),
QT_MOC_LITERAL(14, 178, 10),
QT_MOC_LITERAL(15, 189, 10),
QT_MOC_LITERAL(16, 200, 10),
QT_MOC_LITERAL(17, 211, 10),
QT_MOC_LITERAL(18, 222, 16),
QT_MOC_LITERAL(19, 239, 17)
    },
    "MainWindow\0mouseCurrentPos\0\0"
    "mouseLeftPressed\0mouseRightPressed\0"
    "mouseReleased\0mouseLeave\0evtCalibration\0"
    "evtVision\0checkboxCamera\0checkboxImage\0"
    "checkboxVideo\0updateHmin\0updateSmin\0"
    "updateVmin\0updateHmax\0updateSmax\0"
    "updateVmax\0getNewImageCalib\0"
    "getNewStateVision\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  104,    2, 0x0a,
       3,    0,  105,    2, 0x0a,
       4,    0,  106,    2, 0x0a,
       5,    0,  107,    2, 0x0a,
       6,    0,  108,    2, 0x0a,
       7,    0,  109,    2, 0x0a,
       8,    0,  110,    2, 0x0a,
       9,    1,  111,    2, 0x0a,
      10,    1,  114,    2, 0x0a,
      11,    1,  117,    2, 0x0a,
      12,    1,  120,    2, 0x0a,
      13,    1,  123,    2, 0x0a,
      14,    1,  126,    2, 0x0a,
      15,    1,  129,    2, 0x0a,
      16,    1,  132,    2, 0x0a,
      17,    1,  135,    2, 0x0a,
      18,    0,  138,    2, 0x0a,
      19,    0,  139,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->mouseCurrentPos(); break;
        case 1: _t->mouseLeftPressed(); break;
        case 2: _t->mouseRightPressed(); break;
        case 3: _t->mouseReleased(); break;
        case 4: _t->mouseLeave(); break;
        case 5: _t->evtCalibration(); break;
        case 6: _t->evtVision(); break;
        case 7: _t->checkboxCamera((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->checkboxImage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->checkboxVideo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->updateHmin((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->updateSmin((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->updateVmin((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->updateHmax((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->updateSmax((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->updateVmax((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->getNewImageCalib(); break;
        case 17: _t->getNewStateVision(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
