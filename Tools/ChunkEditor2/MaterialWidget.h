#ifndef MATERIALWIDGET_H
#define MATERIALWIDGET_H

#include <QtGUI>
#include <string>
#include "MaterialViewWidget.h"

class MaterialWidget : public QWidget
{
	Q_OBJECT

private:
	MaterialWidget(QGLWidget *glWidget);
	static MaterialWidget* pInstance;

	QComboBox *matCmb;
	QPushButton *newMaterialBtn, *saveBtn;
	QLabel *nameLbl,*colorLbl,*specLbl,*shineLbl,*glowLbl,
			*colorViewLbl,*glowViewLbl,*textureLbl,
			*uvOffLbl,*uvScaleLbl,*texRotateLbl,*normalLbl;
	QLineEdit *nameEdt,*uTexOffEdt,*vTexOffEdt,*uTexScaleEdt,*vTexScaleEdt;
	QSlider *specSld,*shineSld,*texRotateSld;

	MaterialViewWidget *materialView;

public:
    static MaterialWidget *getInstance(QGLWidget *glWidget = 0);

public slots:
	void refresh();

private slots:
	void currentMatChanged(QString mat);
	void saveAll();
	void addNewMaterial();
};

#endif