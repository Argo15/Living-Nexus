/****************************************************************************
** Meta object code from reading C++ file 'MaterialEditor.h'
**
** Created: Sun Jun 3 16:46:01 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MaterialEditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MaterialEditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MaterialEditor[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x0a,
      35,   31,   15,   15, 0x0a,
      67,   62,   15,   15, 0x08,
      94,   88,   15,   15, 0x08,
     111,   88,   15,   15, 0x08,
     129,   15,   15,   15, 0x08,
     144,   15,   15,   15, 0x08,
     162,  158,   15,   15, 0x08,
     189,  158,   15,   15, 0x08,
     217,   15,   15,   15, 0x08,
     234,   88,   15,   15, 0x08,
     258,   88,   15,   15, 0x08,
     282,   88,   15,   15, 0x08,
     308,   88,   15,   15, 0x08,
     334,   88,   15,   15, 0x08,
     356,   15,   15,   15, 0x08,
     372,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MaterialEditor[] = {
    "MaterialEditor\0\0updateEditor()\0mat\0"
    "currentMatChanged(QString)\0name\0"
    "nameChanged(QString)\0value\0specChanged(int)\0"
    "shineChanged(int)\0colorChanged()\0"
    "glowChanged()\0tex\0currentTexChanged(QString)\0"
    "currentNormChanged(QString)\0"
    "addNewMaterial()\0uTexOffChanged(QString)\0"
    "vTexOffChanged(QString)\0"
    "uTexScaleChanged(QString)\0"
    "vTexScaleChanged(QString)\0"
    "texRotateChanged(int)\0normalChanged()\0"
    "saveAll()\0"
};

const QMetaObject MaterialEditor::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MaterialEditor,
      qt_meta_data_MaterialEditor, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MaterialEditor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MaterialEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MaterialEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MaterialEditor))
        return static_cast<void*>(const_cast< MaterialEditor*>(this));
    return QDialog::qt_metacast(_clname);
}

int MaterialEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateEditor(); break;
        case 1: currentMatChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: nameChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: specChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: shineChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: colorChanged(); break;
        case 6: glowChanged(); break;
        case 7: currentTexChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: currentNormChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: addNewMaterial(); break;
        case 10: uTexOffChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: vTexOffChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: uTexScaleChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: vTexScaleChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: texRotateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: normalChanged(); break;
        case 16: saveAll(); break;
        default: ;
        }
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
