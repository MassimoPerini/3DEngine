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
    QByteArrayData data[16];
    char stringdata[259];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
- idx * sizeof(QByteArrayData) \
)
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
        QT_MOC_LITERAL(0, 0, 10),
        QT_MOC_LITERAL(1, 11, 14),
        QT_MOC_LITERAL(2, 26, 0),
        QT_MOC_LITERAL(3, 27, 14),
        QT_MOC_LITERAL(4, 42, 8),
        QT_MOC_LITERAL(5, 51, 8),
        QT_MOC_LITERAL(6, 60, 16),
        QT_MOC_LITERAL(7, 77, 5),
        QT_MOC_LITERAL(8, 83, 16),
        QT_MOC_LITERAL(9, 100, 15),
        QT_MOC_LITERAL(10, 116, 21),
        QT_MOC_LITERAL(11, 138, 23),
        QT_MOC_LITERAL(12, 162, 23),
        QT_MOC_LITERAL(13, 186, 23),
        QT_MOC_LITERAL(14, 210, 23),
        QT_MOC_LITERAL(15, 234, 23)
    },
    "MainWindow\0rowChangedSlot\0\0QItemSelection\0"
    "selected\0deselect\0diffColorChoosen\0"
    "color\0specColorChoosen\0ambColorChoosen\0"
    "on_pushButton_clicked\0on_pushButton_2_clicked\0"
    "on_pushButton_3_clicked\0on_pushButton_4_clicked\0"
    "on_pushButton_5_clicked\0on_pushButton_6_clicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {
    
    // content:
    7,       // revision
    0,       // classname
    0,    0, // classinfo
    10,   14, // methods
    0,    0, // properties
    0,    0, // enums/sets
    0,    0, // constructors
    0,       // flags
    0,       // signalCount
    
    // slots: name, argc, parameters, tag, flags
    1,    2,   64,    2, 0x08,
    6,    1,   69,    2, 0x08,
    8,    1,   72,    2, 0x08,
    9,    1,   75,    2, 0x08,
    10,    0,   78,    2, 0x08,
    11,    0,   79,    2, 0x08,
    12,    0,   80,    2, 0x08,
    13,    0,   81,    2, 0x08,
    14,    0,   82,    2, 0x08,
    15,    0,   83,    2, 0x08,
    
    // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,
    QMetaType::Void, QMetaType::QColor,    7,
    QMetaType::Void, QMetaType::QColor,    7,
    QMetaType::Void, QMetaType::QColor,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    
    0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
            case 0: _t->rowChangedSlot((*reinterpret_cast< const QItemSelection(*)>(_a[1])),(*reinterpret_cast< const QItemSelection(*)>(_a[2]))); break;
            case 1: _t->diffColorChoosen((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
            case 2: _t->specColorChoosen((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
            case 3: _t->ambColorChoosen((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
            case 4: _t->confirm(); break;
            case 5: _t->on_btnAddLight_clicked(); break;
            case 6: _t->on_btnDeleteLight_clicked(); break;
            case 7: _t->on_btnOpenDiffColor_clicked(); break;
            case 8: _t->on_btnOpenSpecColor_clicked(); break;
            case 9: _t->on_btnOpenAmbColor_clicked(); break;
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
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE