/****************************************************************************
** Meta object code from reading C++ file 'player1.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../BioHazard/player1.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'player1.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_player1_t {
    QByteArrayData data[10];
    char stringdata0[97];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_player1_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_player1_t qt_meta_stringdata_player1 = {
    {
QT_MOC_LITERAL(0, 0, 7), // "player1"
QT_MOC_LITERAL(1, 8, 13), // "buttonPressed"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 13), // "buttonClicked"
QT_MOC_LITERAL(4, 37, 14), // "buttonClicked2"
QT_MOC_LITERAL(5, 52, 5), // "spawn"
QT_MOC_LITERAL(6, 58, 4), // "move"
QT_MOC_LITERAL(7, 63, 12), // "change_speed"
QT_MOC_LITERAL(8, 76, 7), // "animate"
QT_MOC_LITERAL(9, 84, 12) // "anim_counter"

    },
    "player1\0buttonPressed\0\0buttonClicked\0"
    "buttonClicked2\0spawn\0move\0change_speed\0"
    "animate\0anim_counter"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_player1[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,
       4,    0,   56,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   57,    2, 0x0a /* Public */,
       6,    0,   58,    2, 0x0a /* Public */,
       7,    0,   59,    2, 0x0a /* Public */,
       8,    0,   60,    2, 0x0a /* Public */,
       9,    0,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void player1::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<player1 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->buttonPressed(); break;
        case 1: _t->buttonClicked(); break;
        case 2: _t->buttonClicked2(); break;
        case 3: _t->spawn(); break;
        case 4: _t->move(); break;
        case 5: _t->change_speed(); break;
        case 6: _t->animate(); break;
        case 7: _t->anim_counter(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (player1::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&player1::buttonPressed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (player1::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&player1::buttonClicked)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (player1::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&player1::buttonClicked2)) {
                *result = 2;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject player1::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_player1.data,
    qt_meta_data_player1,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *player1::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *player1::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_player1.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QGraphicsPixmapItem"))
        return static_cast< QGraphicsPixmapItem*>(this);
    return QObject::qt_metacast(_clname);
}

int player1::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void player1::buttonPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void player1::buttonClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void player1::buttonClicked2()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
