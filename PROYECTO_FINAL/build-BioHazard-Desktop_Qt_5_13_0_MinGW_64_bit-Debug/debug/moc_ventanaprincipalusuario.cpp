/****************************************************************************
** Meta object code from reading C++ file 'ventanaprincipalusuario.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../BioHazard/ventanaprincipalusuario.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ventanaprincipalusuario.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VentanaPrincipalUsuario_t {
    QByteArrayData data[10];
    char stringdata0[179];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VentanaPrincipalUsuario_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VentanaPrincipalUsuario_t qt_meta_stringdata_VentanaPrincipalUsuario = {
    {
QT_MOC_LITERAL(0, 0, 23), // "VentanaPrincipalUsuario"
QT_MOC_LITERAL(1, 24, 13), // "buttonClicked"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 18), // "on_Campana_clicked"
QT_MOC_LITERAL(4, 58, 22), // "on_Cooperativo_clicked"
QT_MOC_LITERAL(5, 81, 18), // "on_Ranking_clicked"
QT_MOC_LITERAL(6, 100, 23), // "on_CerrarSesion_clicked"
QT_MOC_LITERAL(7, 124, 8), // "Aparecer"
QT_MOC_LITERAL(8, 133, 20), // "on_comojugar_clicked"
QT_MOC_LITERAL(9, 154, 24) // "IniciarNivelSeleccionado"

    },
    "VentanaPrincipalUsuario\0buttonClicked\0"
    "\0on_Campana_clicked\0on_Cooperativo_clicked\0"
    "on_Ranking_clicked\0on_CerrarSesion_clicked\0"
    "Aparecer\0on_comojugar_clicked\0"
    "IniciarNivelSeleccionado"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VentanaPrincipalUsuario[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void VentanaPrincipalUsuario::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VentanaPrincipalUsuario *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->buttonClicked(); break;
        case 1: _t->on_Campana_clicked(); break;
        case 2: _t->on_Cooperativo_clicked(); break;
        case 3: _t->on_Ranking_clicked(); break;
        case 4: _t->on_CerrarSesion_clicked(); break;
        case 5: _t->Aparecer(); break;
        case 6: _t->on_comojugar_clicked(); break;
        case 7: _t->IniciarNivelSeleccionado(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (VentanaPrincipalUsuario::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VentanaPrincipalUsuario::buttonClicked)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject VentanaPrincipalUsuario::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_VentanaPrincipalUsuario.data,
    qt_meta_data_VentanaPrincipalUsuario,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VentanaPrincipalUsuario::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VentanaPrincipalUsuario::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VentanaPrincipalUsuario.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int VentanaPrincipalUsuario::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void VentanaPrincipalUsuario::buttonClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
