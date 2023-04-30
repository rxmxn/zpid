/****************************************************************************
** Meta object code from reading C++ file 'ayuda.h'
**
** Created: Mon 8. Apr 18:37:07 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Software/ayuda.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ayuda.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Ayuda[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,    7,    6,    6, 0x08,
      61,    6,    6,    6, 0x08,
      90,   84,    6,    6, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Ayuda[] = {
    "Ayuda\0\0currentText\0"
    "on_listBuscar_currentTextChanged(QString)\0"
    "on_btnBuscar_clicked()\0index\0"
    "on_listIndice_currentRowChanged(int)\0"
};

const QMetaObject Ayuda::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Ayuda,
      qt_meta_data_Ayuda, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Ayuda::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Ayuda::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Ayuda::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Ayuda))
        return static_cast<void*>(const_cast< Ayuda*>(this));
    return QDialog::qt_metacast(_clname);
}

int Ayuda::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_listBuscar_currentTextChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: on_btnBuscar_clicked(); break;
        case 2: on_listIndice_currentRowChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
