#include "PhysicsWidget.h"
#include "ArgoMaterialManager.h"
#include "ArgoModelManager.h"
#include "ArgoSceneManager.h"

PhysicsWidget::PhysicsWidget() 
	: QWidget(0)
{
	addShapeLbl = new QLabel("Add physics shape:");
	cubeShapeBtn = new QPushButton("Add Cube");
	cylinderShapeBtn = new QPushButton("Add Cylinder");
	sphereShapeBtn = new QPushButton("Add Sphere");

	QVBoxLayout *mainLayout = new QVBoxLayout;

	mainLayout->addWidget(addShapeLbl);
	mainLayout->addWidget(cubeShapeBtn);
	mainLayout->addWidget(cylinderShapeBtn);
	mainLayout->addWidget(sphereShapeBtn);

	setLayout(mainLayout);

	connect(cubeShapeBtn, SIGNAL(clicked()),this, SLOT(addBox()));
	connect(cylinderShapeBtn, SIGNAL(clicked()),this, SLOT(addCylinder()));
	connect(sphereShapeBtn, SIGNAL(clicked()),this, SLOT(addSphere()));

	layout()->setContentsMargins(0,0,0,0);
	setFixedHeight(sizeHint().height());
	setFixedWidth(sizeHint().width());
}

void PhysicsWidget::addBox()
{
	PhysicsShape *shape = new PhysicsShape(BOX, "Physics Box");
	ArgoSceneManager::Instance()->AddPhysicsShape(shape);
}

void PhysicsWidget::addCylinder()
{
	PhysicsShape *shape = new PhysicsShape(CYLINDER, "Physics Cylinder");
	ArgoSceneManager::Instance()->AddPhysicsShape(shape);
}

void PhysicsWidget::addSphere()
{
	PhysicsShape *shape = new PhysicsShape(SPHERE, "Physics Sphere");
	ArgoSceneManager::Instance()->AddPhysicsShape(shape);
}