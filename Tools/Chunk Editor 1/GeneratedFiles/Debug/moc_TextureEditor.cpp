/****************************************************************************
** Meta object code from reading C++ file 'TextureEditor.h'
**
** Created: Sun Jul 15 16:28:26 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TextureEditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TextureEditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TextureEditor[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x0a,
      34,   30,   14,   14, 0x08,
      66,   61,   14,   14, 0x08,
      87,   14,   14,   14, 0x08,
     106,  101,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TextureEditor[] = {
    "TextureEditor\0\0updateEditor()\0tex\0"
    "currentTexChanged(QString)\0type\0"
    "typeChanged(QString)\0loadTexture()\0"
    "name\0nameChanged(QString)\0"
};

const QMetaObject TextureEditor::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_TextureEditor,
      qt_meta_data_TextureEditor, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TextureEditor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TextureEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TextureEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TextureEditor))
        return static_cast<void*>(const_cast< TextureEditor*>(this));
    return QDialog::qt_metacast(_clname);
}

int TextureEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateEditor(); break;
        case 1: currentTexChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: typeChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: loadTexture(); break;
        case 4: nameChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
