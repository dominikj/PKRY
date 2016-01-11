/****************************************************************************
** Meta object code from reading C++ file 'oknoglowne.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../klient/gui/oknoglowne.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'oknoglowne.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_OknoGlowne_t {
    QByteArrayData data[18];
    char stringdata0[230];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OknoGlowne_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OknoGlowne_t qt_meta_stringdata_OknoGlowne = {
    {
QT_MOC_LITERAL(0, 0, 10), // "OknoGlowne"
QT_MOC_LITERAL(1, 11, 17), // "odpowiedz_serwera"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 3), // "odp"
QT_MOC_LITERAL(4, 34, 10), // "powodzenie"
QT_MOC_LITERAL(5, 45, 16), // "zlap_nowa_aukcje"
QT_MOC_LITERAL(6, 62, 10), // "polaAukcji"
QT_MOC_LITERAL(7, 73, 2), // "pA"
QT_MOC_LITERAL(8, 76, 16), // "zlap_nowa_oferte"
QT_MOC_LITERAL(9, 93, 2), // "of"
QT_MOC_LITERAL(10, 96, 7), // "uruchom"
QT_MOC_LITERAL(11, 104, 1), // "t"
QT_MOC_LITERAL(12, 106, 31), // "on_listWidget_itemDoubleClicked"
QT_MOC_LITERAL(13, 138, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(14, 155, 4), // "item"
QT_MOC_LITERAL(15, 160, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(16, 184, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(17, 206, 23) // "on_pushButton_3_clicked"

    },
    "OknoGlowne\0odpowiedz_serwera\0\0odp\0"
    "powodzenie\0zlap_nowa_aukcje\0polaAukcji\0"
    "pA\0zlap_nowa_oferte\0of\0uruchom\0t\0"
    "on_listWidget_itemDoubleClicked\0"
    "QListWidgetItem*\0item\0on_pushButton_2_clicked\0"
    "on_pushButton_clicked\0on_pushButton_3_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OknoGlowne[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   59,    2, 0x0a /* Public */,
       8,    1,   62,    2, 0x0a /* Public */,
      10,    1,   65,    2, 0x0a /* Public */,
      12,    1,   68,    2, 0x08 /* Private */,
      15,    0,   71,    2, 0x08 /* Private */,
      16,    0,   72,    2, 0x08 /* Private */,
      17,    0,   73,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void OknoGlowne::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OknoGlowne *_t = static_cast<OknoGlowne *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->odpowiedz_serwera((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->zlap_nowa_aukcje((*reinterpret_cast< polaAukcji(*)>(_a[1]))); break;
        case 2: _t->zlap_nowa_oferte((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->uruchom((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->on_listWidget_itemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 5: _t->on_pushButton_2_clicked(); break;
        case 6: _t->on_pushButton_clicked(); break;
        case 7: _t->on_pushButton_3_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (OknoGlowne::*_t)(QString , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OknoGlowne::odpowiedz_serwera)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject OknoGlowne::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_OknoGlowne.data,
      qt_meta_data_OknoGlowne,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *OknoGlowne::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OknoGlowne::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_OknoGlowne.stringdata0))
        return static_cast<void*>(const_cast< OknoGlowne*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int OknoGlowne::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
void OknoGlowne::odpowiedz_serwera(QString _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
