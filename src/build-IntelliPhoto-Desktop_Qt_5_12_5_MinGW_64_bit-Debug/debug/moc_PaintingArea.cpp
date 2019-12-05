/****************************************************************************
** Meta object code from reading C++ file 'PaintingArea.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Painting/Layer/PaintingArea.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PaintingArea.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PaintingArea_t {
    QByteArrayData data[18];
    char stringdata0[155];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PaintingArea_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PaintingArea_t qt_meta_stringdata_PaintingArea = {
    {
QT_MOC_LITERAL(0, 0, 12), // "PaintingArea"
QT_MOC_LITERAL(1, 13, 10), // "clearImage"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 1), // "r"
QT_MOC_LITERAL(4, 27, 1), // "g"
QT_MOC_LITERAL(5, 29, 1), // "b"
QT_MOC_LITERAL(6, 31, 8), // "activate"
QT_MOC_LITERAL(7, 40, 1), // "a"
QT_MOC_LITERAL(8, 42, 8), // "setAlpha"
QT_MOC_LITERAL(9, 51, 9), // "getMoveUp"
QT_MOC_LITERAL(10, 61, 11), // "getMoveDown"
QT_MOC_LITERAL(11, 73, 12), // "getMoveRight"
QT_MOC_LITERAL(12, 86, 11), // "getMoveLeft"
QT_MOC_LITERAL(13, 98, 14), // "getMoveLayerUp"
QT_MOC_LITERAL(14, 113, 16), // "getMoveLayerDown"
QT_MOC_LITERAL(15, 130, 5), // "setUp"
QT_MOC_LITERAL(16, 136, 8), // "maxWidth"
QT_MOC_LITERAL(17, 145, 9) // "maxHeight"

    },
    "PaintingArea\0clearImage\0\0r\0g\0b\0activate\0"
    "a\0setAlpha\0getMoveUp\0getMoveDown\0"
    "getMoveRight\0getMoveLeft\0getMoveLayerUp\0"
    "getMoveLayerDown\0setUp\0maxWidth\0"
    "maxHeight"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PaintingArea[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   64,    2, 0x0a /* Public */,
       6,    1,   71,    2, 0x0a /* Public */,
       8,    1,   74,    2, 0x0a /* Public */,
       9,    1,   77,    2, 0x0a /* Public */,
      10,    1,   80,    2, 0x0a /* Public */,
      11,    1,   83,    2, 0x0a /* Public */,
      12,    1,   86,    2, 0x0a /* Public */,
      13,    0,   89,    2, 0x0a /* Public */,
      14,    0,   90,    2, 0x0a /* Public */,
      15,    2,   91,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   16,   17,

       0        // eod
};

void PaintingArea::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PaintingArea *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clearImage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->activate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setAlpha((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->getMoveUp((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->getMoveDown((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->getMoveRight((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->getMoveLeft((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->getMoveLayerUp(); break;
        case 8: _t->getMoveLayerDown(); break;
        case 9: _t->setUp((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PaintingArea::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_PaintingArea.data,
    qt_meta_data_PaintingArea,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PaintingArea::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PaintingArea::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PaintingArea.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PaintingArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
