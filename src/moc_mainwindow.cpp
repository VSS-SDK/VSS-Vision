/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[22];
    char stringdata0[296];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 15), // "mouseCurrentPos"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 16), // "mouseLeftPressed"
QT_MOC_LITERAL(4, 45, 17), // "mouseRightPressed"
QT_MOC_LITERAL(5, 63, 13), // "mouseReleased"
QT_MOC_LITERAL(6, 77, 10), // "mouseLeave"
QT_MOC_LITERAL(7, 88, 20), // "evtCalibrationColors"
QT_MOC_LITERAL(8, 109, 9), // "evtVision"
QT_MOC_LITERAL(9, 119, 17), // "evtCalibrationCam"
QT_MOC_LITERAL(10, 137, 14), // "checkboxCamera"
QT_MOC_LITERAL(11, 152, 13), // "checkboxImage"
QT_MOC_LITERAL(12, 166, 13), // "checkboxVideo"
QT_MOC_LITERAL(13, 180, 10), // "updateHmin"
QT_MOC_LITERAL(14, 191, 10), // "updateSmin"
QT_MOC_LITERAL(15, 202, 10), // "updateVmin"
QT_MOC_LITERAL(16, 213, 10), // "updateHmax"
QT_MOC_LITERAL(17, 224, 10), // "updateSmax"
QT_MOC_LITERAL(18, 235, 10), // "updateVmax"
QT_MOC_LITERAL(19, 246, 14), // "updateRotation"
QT_MOC_LITERAL(20, 261, 16), // "getNewImageCalib"
QT_MOC_LITERAL(21, 278, 17) // "getNewStateVision"

    },
    "MainWindow\0mouseCurrentPos\0\0"
    "mouseLeftPressed\0mouseRightPressed\0"
    "mouseReleased\0mouseLeave\0evtCalibrationColors\0"
    "evtVision\0evtCalibrationCam\0checkboxCamera\0"
    "checkboxImage\0checkboxVideo\0updateHmin\0"
    "updateSmin\0updateVmin\0updateHmax\0"
    "updateSmax\0updateVmax\0updateRotation\0"
    "getNewImageCalib\0getNewStateVision"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  114,    2, 0x0a /* Public */,
       3,    0,  115,    2, 0x0a /* Public */,
       4,    0,  116,    2, 0x0a /* Public */,
       5,    0,  117,    2, 0x0a /* Public */,
       6,    0,  118,    2, 0x0a /* Public */,
       7,    0,  119,    2, 0x0a /* Public */,
       8,    0,  120,    2, 0x0a /* Public */,
       9,    0,  121,    2, 0x0a /* Public */,
      10,    1,  122,    2, 0x0a /* Public */,
      11,    1,  125,    2, 0x0a /* Public */,
      12,    1,  128,    2, 0x0a /* Public */,
      13,    1,  131,    2, 0x0a /* Public */,
      14,    1,  134,    2, 0x0a /* Public */,
      15,    1,  137,    2, 0x0a /* Public */,
      16,    1,  140,    2, 0x0a /* Public */,
      17,    1,  143,    2, 0x0a /* Public */,
      18,    1,  146,    2, 0x0a /* Public */,
      19,    1,  149,    2, 0x0a /* Public */,
      20,    0,  152,    2, 0x0a /* Public */,
      21,    0,  153,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
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
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->mouseCurrentPos(); break;
        case 1: _t->mouseLeftPressed(); break;
        case 2: _t->mouseRightPressed(); break;
        case 3: _t->mouseReleased(); break;
        case 4: _t->mouseLeave(); break;
        case 5: _t->evtCalibrationColors(); break;
        case 6: _t->evtVision(); break;
        case 7: _t->evtCalibrationCam(); break;
        case 8: _t->checkboxCamera((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->checkboxImage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->checkboxVideo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->updateHmin((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->updateSmin((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->updateVmin((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->updateHmax((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->updateSmax((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->updateVmax((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->updateRotation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->getNewImageCalib(); break;
        case 19: _t->getNewStateVision(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 20;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
