/****************************************************************************
** Meta object code from reading C++ file 'grafica.h'
**
** Created: Fri Oct 7 22:04:06 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Software/grafica.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'grafica.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Grafica[] = {

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
      61,    9,    8,    8, 0x0a,
     163,  133,    8,    8, 0x0a,
     234,  216,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Grafica[] = {
    "Grafica\0\0name,ubicacion_texto,linea,label,eje_Y,valor,parent\0"
    "add_marker(QwtPlotMarker*,Qt::Alignment,QPen,QwtText,bool,int,QwtPlot*"
    ")\0"
    "name,label,eje_Y,valor,parent\0"
    "add_marker(QwtPlotMarker*,QwtText,bool,int,QwtPlot*)\0"
    "name,color,parent\0add_curve(QString,QPen,QwtPlot*)\0"
};

const QMetaObject Grafica::staticMetaObject = {
    { &QwtPlot::staticMetaObject, qt_meta_stringdata_Grafica,
      qt_meta_data_Grafica, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Grafica::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Grafica::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Grafica::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Grafica))
        return static_cast<void*>(const_cast< Grafica*>(this));
    return QwtPlot::qt_metacast(_clname);
}

int Grafica::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QwtPlot::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: add_marker((*reinterpret_cast< QwtPlotMarker*(*)>(_a[1])),(*reinterpret_cast< Qt::Alignment(*)>(_a[2])),(*reinterpret_cast< QPen(*)>(_a[3])),(*reinterpret_cast< QwtText(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< QwtPlot*(*)>(_a[7]))); break;
        case 1: add_marker((*reinterpret_cast< QwtPlotMarker*(*)>(_a[1])),(*reinterpret_cast< QwtText(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< QwtPlot*(*)>(_a[5]))); break;
        case 2: add_curve((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QPen(*)>(_a[2])),(*reinterpret_cast< QwtPlot*(*)>(_a[3]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
