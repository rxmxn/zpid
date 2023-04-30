/****************************************************************************
** Meta object code from reading C++ file 'loadedfile.h'
**
** Created: Fri 26. Oct 17:51:23 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Software/loadedfile.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'loadedfile.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LoadedFile[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   11,   12,   11, 0x0a,
      46,   11,   37,   11, 0x0a,
      72,   11,   61,   11, 0x0a,
      95,   89,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_LoadedFile[] = {
    "LoadedFile\0\0QTextEdit*\0change_text()\0"
    "QAction*\0event_Action()\0QShortcut*\0"
    "event_Shortcut()\0event\0"
    "contextMenuEvent(QContextMenuEvent*)\0"
};

const QMetaObject LoadedFile::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_LoadedFile,
      qt_meta_data_LoadedFile, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LoadedFile::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LoadedFile::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LoadedFile::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LoadedFile))
        return static_cast<void*>(const_cast< LoadedFile*>(this));
    return QDialog::qt_metacast(_clname);
}

int LoadedFile::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { QTextEdit* _r = change_text();
            if (_a[0]) *reinterpret_cast< QTextEdit**>(_a[0]) = _r; }  break;
        case 1: { QAction* _r = event_Action();
            if (_a[0]) *reinterpret_cast< QAction**>(_a[0]) = _r; }  break;
        case 2: { QShortcut* _r = event_Shortcut();
            if (_a[0]) *reinterpret_cast< QShortcut**>(_a[0]) = _r; }  break;
        case 3: contextMenuEvent((*reinterpret_cast< QContextMenuEvent*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
