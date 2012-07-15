/****************************************************************************
** Meta object code from reading C++ file 'PointLightWidget.h'
**
** Created: Sun Jul 15 16:28:26 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PointLightWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PointLightWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PointLightWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x0a,
      39,   33,   17,   17, 0x0a,
      59,   33,   17,   17, 0x0a,
      79,   33,   17,   17, 0x0a,
     100,   33,   17,   17, 0x0a,
     129,  124,   17,   17, 0x0a,
     150,  124,   17,   17, 0x0a,
     173,   17,   17,   17, 0x0a,
     188,   17,   17,   17, 0x0a,
     205,   17,   17,   17, 0x0a,
     219,  124,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PointLightWidget[] = {
    "PointLightWidget\0\0updateWidget()\0value\0"
    "ambientChanged(int)\0diffuseChanged(int)\0"
    "specularChanged(int)\0attenuationChanged(int)\0"
    "name\0nameChanged(QString)\0"
    "radiusChanged(QString)\0colorChanged()\0"
    "enabledChanged()\0addNewLight()\0"
    "currentLightChanged(QString)\0"
};

const QMetaObject PointLightWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PointLightWidget,
      qt_meta_data_PointLightWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PointLightWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PointLightWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PointLightWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PointLightWidget))
        return static_cast<void*>(const_cast< PointLightWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int PointLightWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateWidget(); break;
        case 1: ambientChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: diffuseChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: specularChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: attenuationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: nameChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: radiusChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: colorChanged(); break;
        case 8: enabledChanged(); break;
        case 9: addNewLight(); break;
        case 10: currentLightChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
