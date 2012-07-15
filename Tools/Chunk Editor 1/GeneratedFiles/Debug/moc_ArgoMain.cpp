/****************************************************************************
** Meta object code from reading C++ file 'ArgoMain.h'
**
** Created: Sun Jul 15 16:28:33 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ArgoMain.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ArgoMain.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ArgoMain[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x08,
      20,    9,    9,    9, 0x08,
      27,    9,    9,    9, 0x08,
      40,   36,    9,    9, 0x08,
      63,    9,    9,    9, 0x08,
      79,    9,    9,    9, 0x08,
      96,    9,    9,    9, 0x08,
     111,    9,    9,    9, 0x08,
     132,    9,    9,    9, 0x08,
     154,    9,    9,    9, 0x08,
     173,    9,    9,    9, 0x08,
     192,    9,    9,    9, 0x08,
     211,    9,    9,    9, 0x08,
     222,    9,    9,    9, 0x08,
     239,  234,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ArgoMain[] = {
    "ArgoMain\0\0newFile()\0open()\0saveAs()\0"
    "buf\0bufferChanged(QString)\0shaderChanged()\0"
    "physicsChanged()\0tilesChanged()\0"
    "openTextureManager()\0openMaterialManager()\0"
    "openModelManager()\0openLightManager()\0"
    "openActorManager()\0saveTile()\0saveChunk()\0"
    "mode\0modeChanged(QString)\0"
};

const QMetaObject ArgoMain::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ArgoMain,
      qt_meta_data_ArgoMain, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ArgoMain::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ArgoMain::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ArgoMain::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ArgoMain))
        return static_cast<void*>(const_cast< ArgoMain*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ArgoMain::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: newFile(); break;
        case 1: open(); break;
        case 2: saveAs(); break;
        case 3: bufferChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: shaderChanged(); break;
        case 5: physicsChanged(); break;
        case 6: tilesChanged(); break;
        case 7: openTextureManager(); break;
        case 8: openMaterialManager(); break;
        case 9: openModelManager(); break;
        case 10: openLightManager(); break;
        case 11: openActorManager(); break;
        case 12: saveTile(); break;
        case 13: saveChunk(); break;
        case 14: modeChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
