#include "MaterialWidget.h"

MaterialWidget *MaterialWidget::pInstance = 0;

MaterialWidget *MaterialWidget::getInstance(QGLWidget *glWidget)
{
	if (pInstance == 0) {
		pInstance=new MaterialWidget(glWidget);
	}
	return pInstance;
}

MaterialWidget::MaterialWidget(QGLWidget *glWidget) : QWidget(0)
{
	materialView = new MaterialViewWidget(this, glWidget);
	materialView->setFixedWidth(195);
	materialView->setFixedHeight(195);

	matCmb = new QComboBox();
	newMaterialBtn = new QPushButton("New Material");
	saveBtn = new QPushButton("Save All");

	nameLbl			= new QLabel("Name:");
	colorLbl		= new QLabel("Color:");
	specLbl			= new QLabel("Specular:");
	shineLbl		= new QLabel("Shine:");
	glowLbl			= new QLabel("Glow:");
	colorViewLbl	= new QLabel("      ");
	glowViewLbl		= new QLabel("      ");
	textureLbl		= new QLabel("Texture:");
	uvOffLbl		= new QLabel("uvOff:   ");
	uvScaleLbl		= new QLabel("uvScale:");
	texRotateLbl	= new QLabel("uvRot:");
	normalLbl		= new QLabel("Normal:");

	nameEdt = new QLineEdit("test");
	uTexOffEdt = new QLineEdit("0");
	uTexOffEdt->setFixedWidth(40);
	vTexOffEdt = new QLineEdit("0");
	vTexOffEdt->setFixedWidth(40);
	uTexScaleEdt = new QLineEdit("1");
	uTexScaleEdt->setFixedWidth(40);
	vTexScaleEdt = new QLineEdit("1");
	vTexScaleEdt->setFixedWidth(40);

	specSld = new QSlider(Qt::Horizontal);
	specSld->setRange(0,255);
	shineSld = new QSlider(Qt::Horizontal);
	shineSld->setRange(5,128);
	texRotateSld = new QSlider(Qt::Horizontal);
	texRotateSld->setRange(0,360);

	QHBoxLayout *mainLayout = new QHBoxLayout;
		QVBoxLayout *leftLayout = new QVBoxLayout;
		QVBoxLayout *rightLayout = new QVBoxLayout;
			QHBoxLayout *nameLayout = new QHBoxLayout;
			QHBoxLayout *colorLayout = new QHBoxLayout;
			QHBoxLayout *glowLayout = new QHBoxLayout;
			QHBoxLayout *specLayout = new QHBoxLayout;
			QHBoxLayout *shineLayout = new QHBoxLayout;
			QHBoxLayout *textureLayout = new QHBoxLayout;
			QHBoxLayout *normalLayout = new QHBoxLayout;
			QHBoxLayout *uvOffLayout = new QHBoxLayout;
			QHBoxLayout *uvScaleLayout = new QHBoxLayout;
			QHBoxLayout *uvRotLayout = new QHBoxLayout;

	leftLayout->addWidget(materialView);
	leftLayout->addWidget(matCmb);
	leftLayout->addWidget(newMaterialBtn);
	leftLayout->addWidget(saveBtn);
	leftLayout->setContentsMargins(0,0,0,0);

	nameLayout->addWidget(nameLbl);
	nameLayout->addWidget(nameEdt);

	colorLayout->addWidget(colorLbl);
	colorLayout->addWidget(colorViewLbl);

	glowLayout->addWidget(glowLbl);
	glowLayout->addWidget(glowViewLbl);
	
	specLayout->addWidget(specLbl);
	specLayout->addWidget(specSld);

	shineLayout->addWidget(shineLbl);
	shineLayout->addWidget(shineSld);

	textureLayout->addWidget(textureLbl);

	normalLayout->addWidget(normalLbl);

	uvOffLayout->addWidget(uvOffLbl);
	uvOffLayout->addWidget(uTexOffEdt);
	uvOffLayout->addWidget(vTexOffEdt);
	uvOffLayout->addStretch();

	uvScaleLayout->addWidget(uvScaleLbl);
	uvScaleLayout->addWidget(uTexScaleEdt);
	uvScaleLayout->addWidget(vTexScaleEdt);
	uvScaleLayout->addStretch();

	uvRotLayout->addWidget(texRotateLbl);
	uvRotLayout->addWidget(texRotateSld);

	rightLayout->addLayout(nameLayout);
	rightLayout->addLayout(colorLayout);
	rightLayout->addLayout(glowLayout);
	rightLayout->addLayout(specLayout);
	rightLayout->addLayout(shineLayout);
	rightLayout->addLayout(textureLayout);
	rightLayout->addLayout(normalLayout);
	rightLayout->addLayout(uvOffLayout);
	rightLayout->addLayout(uvScaleLayout);
	rightLayout->addLayout(uvRotLayout);
	rightLayout->addStretch();
	rightLayout->setContentsMargins(0,0,0,0);

	mainLayout->addLayout(leftLayout);
	mainLayout->addLayout(rightLayout);
	mainLayout->setContentsMargins(0,0,0,0);

	setLayout(mainLayout);

	connect(matCmb, SIGNAL(activated(QString)),this, SLOT(currentMatChanged(QString)));
	connect(saveBtn, SIGNAL(clicked()),this, SLOT(saveAll()));
	connect(newMaterialBtn, SIGNAL(clicked()),this, SLOT(addNewMaterial()));

	setFixedHeight(mainLayout->sizeHint().height());
	setFixedWidth(400);
}


void MaterialWidget::refresh()
{
	matCmb->clear();
	std::map<std::string, Material *> *materials = Root::materialManager->getMaterials();
	for (std::map<std::string, Material *>::iterator it = materials->begin(); it != materials->end(); it++) {
		matCmb->addItem((*it).first.c_str());
	}

	currentMatChanged(matCmb->currentText());
}

void MaterialWidget::currentMatChanged(QString mat) 
{
	materialView->setMaterial(mat.toStdString());
	materialView->repaint();
}

void MaterialWidget::saveAll()
{
	Root::materialManager->SaveAllMaterials();
}

void MaterialWidget::addNewMaterial()
{
	Material *defaultMat = Root::materialManager->getMaterial("Default");
	Material *newMat = new Material();
	*newMat = *defaultMat;
	newMat->setName("New Material");
	Root::materialManager->AddMaterialSafe(newMat);
	refresh();
}