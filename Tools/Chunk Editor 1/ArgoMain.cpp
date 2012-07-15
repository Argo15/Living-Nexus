#include <QtGui>
#include "SaveTile.h"
#include "SaveChunk.h"
#include "ArgoMain.h"

/* Constructor */
ArgoMain::ArgoMain()
{
	QGLFormat fmt;
	fmt.setDirectRendering(true);
	fmt.setDoubleBuffer(true);
	glWidget = new ArgoGLMain(fmt,this);
	fpsLabel=new QLabel("FPS: ?");
	bufferCmb = new QComboBox();
	shaderChk = new QCheckBox("Shaders");
	physicsChk = new QCheckBox("Physics");
	tilesChk = new QCheckBox("Tiles");
	fpsLabel->setAlignment(Qt::AlignHCenter);

	toolBar = addToolBar(tr("ToolBar"));
	bufferCmb->addItem("Final");
	bufferCmb->addItem("Depth");
	bufferCmb->addItem("Normal");
	bufferCmb->addItem("Color");
	bufferCmb->addItem("Specular");
	bufferCmb->addItem("Lighting");

	modeCmb = new QComboBox();
	modeCmb->addItem("Default");
	modeCmb->addItem("Tile");
	modeCmb->addItem("Chunk");

	openBtn = new QPushButton("Open");
	saveBtn = new QPushButton("Save");
	
	toolBar->addWidget(bufferCmb);
	toolBar->addSeparator();
	toolBar->addWidget(shaderChk);
	toolBar->addSeparator();
	toolBar->addWidget(physicsChk);
	toolBar->addSeparator();
	toolBar->addWidget(tilesChk);

	shaderChk->setCheckState(Qt::Checked);
	physicsChk->setCheckState(Qt::Checked);
	tilesChk->setCheckState(Qt::Unchecked);

	setCentralWidget(glWidget);

	createActions();
	createMenus();

	startTimer(0);

	statusBar()->addWidget(fpsLabel);

	DockedActorEditor::Initialize();
	DockedPhysicsWidget::Initialize();

	this->addDockWidget(Qt::RightDockWidgetArea,DockedActorEditor::Instance());
	this->addDockWidget(Qt::BottomDockWidgetArea,DockedPhysicsWidget::Instance());

	timer.Init();

	connect(bufferCmb, SIGNAL(activated(QString)),this, SLOT(bufferChanged(QString)));
	connect(shaderChk, SIGNAL(clicked()),this, SLOT(shaderChanged()));
	connect(physicsChk, SIGNAL(clicked()),this, SLOT(physicsChanged()));
	connect(tilesChk, SIGNAL(clicked()),this, SLOT(tilesChanged()));
	connect(modeCmb, SIGNAL(activated(QString)),this, SLOT(modeChanged(QString)));

	ArgoTextureManager::Initialize();
	ArgoMaterialManager::Initialize();
	ArgoModelManager::Initialize();
	ArgoSceneManager::Initialize();
	ArgoGraphicsSettings::Initialize();
	TileManager::Initialize();

	glWidget->showFullScreen();
}

/* createActions() */
void ArgoMain::createActions()
{
	newAction = new QAction(tr("&New"),this);
	newAction->setIcon(QIcon("Data/Icons/new.png"));
	newAction->setShortcut(QKeySequence::New);
	newAction->setStatusTip(tr("Create a new file"));
	connect(newAction,SIGNAL(triggered()),this,SLOT(newFile()));

	openAction = new QAction(tr("&Open"),this);
	openAction->setIcon(QIcon("Data/Icons/open.png"));
	openAction->setShortcut(QKeySequence::Open);
	openAction->setStatusTip(tr("Open a file"));
	connect(openAction,SIGNAL(triggered()),this,SLOT(open()));

	saveAsAction = new QAction(tr("Save &As"),this);
	saveAsAction->setIcon(QIcon("Data/Icons/save.png"));
	saveAsAction->setShortcut(tr("Ctrl+A"));
	saveAsAction->setStatusTip(tr("Save file"));
	connect(saveAsAction,SIGNAL(triggered()),this,SLOT(saveAs()));

	exitAction = new QAction(tr("E&xit"),this);
	exitAction->setStatusTip(tr("Exit the application"));
	connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));

	texManagerAction = new QAction(tr("Texture Manager"),this);
	texManagerAction->setStatusTip(tr("Texture Manager"));
	connect(texManagerAction,SIGNAL(triggered()),this,SLOT(openTextureManager()));

	matManagerAction = new QAction(tr("Material Manager"),this);
	matManagerAction->setStatusTip(tr("Material Manager"));
	connect(matManagerAction,SIGNAL(triggered()),this,SLOT(openMaterialManager()));

	modelManagerAction = new QAction(tr("Model Manager"),this);
	modelManagerAction->setStatusTip(tr("Model Manager"));
	connect(modelManagerAction,SIGNAL(triggered()),this,SLOT(openModelManager()));

	lightManagerAction = new QAction(tr("Light Manager"),this);
	lightManagerAction->setStatusTip(tr("Light Manager"));
	connect(lightManagerAction,SIGNAL(triggered()),this,SLOT(openLightManager()));

	actorManagerAction = new QAction(tr("Actor Manager"),this);
	actorManagerAction->setStatusTip(tr("Actor Manager"));
	connect(actorManagerAction,SIGNAL(triggered()),this,SLOT(openActorManager()));

	exportChunkAction = new QAction(tr("Chunk (.achk)"),this);
	exportChunkAction->setStatusTip(tr("Export Chunk"));
	connect(exportChunkAction,SIGNAL(triggered()),this,SLOT(saveChunk()));

	exportTileAction = new QAction(tr("Tile (.atl)"),this);
	exportTileAction->setStatusTip(tr("Export Tile"));
	connect(exportTileAction,SIGNAL(triggered()),this,SLOT(saveTile()));
}

/* createMenus() */
void ArgoMain::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(newAction);
	fileMenu->addAction(openAction);
	fileMenu->addAction(saveAsAction);
	exportMenu = fileMenu->addMenu(tr("Export"));
		exportMenu->addAction(exportChunkAction);
		exportMenu->addAction(exportTileAction);
	fileMenu->addAction(exitAction);

	editMenu = menuBar()->addMenu(tr("&Edit"));

	toolsMenu = menuBar()->addMenu(tr("&Tools"));
	toolsMenu->addAction(texManagerAction);
	toolsMenu->addAction(matManagerAction);
	toolsMenu->addAction(modelManagerAction);
	toolsMenu->addAction(lightManagerAction);
	toolsMenu->addAction(actorManagerAction);

	/*gameMenu = menuBar()->addMenu(tr("&Game"));
	tileMenu = new QMenu(tr("&Tiles"));
	chunkMenu = new QMenu(tr("&Chunks"));
	gameMenu->addMenu(tileMenu);
	gameMenu->addMenu(chunkMenu);
	tileMenu->addAction(grassTileAction);
	chunkMenu->addAction(grassChunkAction);*/
}

void ArgoMain::newFile()
{
	ArgoSceneManager::Instance()->DeleteScene();
	ArgoModelManager::Instance()->DeleteAllModels();
	ArgoMaterialManager::Instance()->DeleteAllMaterials();
	ArgoTextureManager::Instance()->DeleteAllTextures();
	LoadDefaultScene();

	TextureEditor::Instance()->hide();
	MaterialEditor::Instance()->hide();
	ModelEditor::Instance()->hide();
	LightEditor::Instance()->hide();
	TextureEditor::Initialize(glWidget);
	MaterialEditor::Initialize(glWidget);
	ModelEditor::Initialize(glWidget);
	LightEditor::Initialize(glWidget);
}

void ArgoMain::open()
{
	QString filename =  QFileDialog::getOpenFileName(this, "Open","Data/Saves",tr("*.ascn"));
	if (!filename.isEmpty()){
		ArgoSceneManager::Instance()->DeleteScene();
		ArgoModelManager::Instance()->DeleteAllModels();
		ArgoMaterialManager::Instance()->DeleteAllMaterials();
		ArgoTextureManager::Instance()->DeleteAllTextures();

		ArgoSaveFile open;
		open.openScene(qPrintable(filename));

		TextureEditor::Instance()->hide();
		MaterialEditor::Instance()->hide();
		ModelEditor::Instance()->hide();
		LightEditor::Instance()->hide();
		TextureEditor::Initialize(glWidget);
		MaterialEditor::Initialize(glWidget);
		ModelEditor::Initialize(glWidget);
		LightEditor::Initialize(glWidget);
	}
}

void ArgoMain::saveAs()
{
	QString filename =  QFileDialog::getSaveFileName(this, "Save As","Data/Saves",tr("*.ascn"));
	if (!filename.isEmpty()){
		ArgoSaveFile save;
		save.saveScene(qPrintable(filename));
	}
}

void ArgoMain::bufferChanged(QString buf)
{
	glWidget->setBuffer(buf);
}

void ArgoMain::shaderChanged()
{
	ArgoGraphicsSettings::Instance()->setShadersEnabled(!ArgoGraphicsSettings::Instance()->shadersEnabled());
}

void ArgoMain::physicsChanged()
{
	ArgoGraphicsSettings::Instance()->setPhysicsEnabled(!ArgoGraphicsSettings::Instance()->physicsEnabled());
}

void ArgoMain::tilesChanged()
{
	ArgoGraphicsSettings::Instance()->editMode = 2 - ArgoGraphicsSettings::Instance()->editMode;
}

void ArgoMain::openTextureManager()
{
	TextureEditor::Instance()->show();
}

void ArgoMain::openMaterialManager()
{
	MaterialEditor::Instance()->show();
}

void ArgoMain::openModelManager()
{
	ModelEditor::Instance()->show();
}

void ArgoMain::openLightManager()
{
	LightEditor::Instance()->show();
}

void ArgoMain::openActorManager()
{
	DockedActorEditor::Instance()->show();
}

void ArgoMain::timerEvent(QTimerEvent *event)
{
	static float time = 0;
	static int frameCount = 0;
	float fps = timer.GetFPS();
	time+=1.0/fps;
	frameCount++;
	if (time>1.0){
		fpsLabel->setText("FPS: " + QString::number((int)(frameCount)));
		time=0;
		frameCount=0;
	}
	glWidget->setFPS(fps);
	glWidget->repaint();
}

void ArgoMain::closeEvent(QCloseEvent *event)
{
	exit(0);
}

void ArgoMain::saveTile()
{
	QString filename =  QFileDialog::getSaveFileName(this, "Save Tile","Data/Tiles",tr("*.atl"));
	if (!filename.isEmpty()){
		SaveTile save;
		save.saveTile(qPrintable(filename));
	}
}

void ArgoMain::saveChunk()
{
	QString filename =  QFileDialog::getSaveFileName(this, "Save Chunk","Data/Chunks",tr("*.achk"));
	if (!filename.isEmpty()){
		SaveChunk save;
		save.saveChunk(qPrintable(filename));
	}
}

void ArgoMain::modeChanged(QString mode)
{
	if (mode == "Default")	ArgoGraphicsSettings::Instance()->editMode = 0;
	if (mode == "Tile")		ArgoGraphicsSettings::Instance()->editMode = 1;
	if (mode == "Chunk")	ArgoGraphicsSettings::Instance()->editMode = 2;
}