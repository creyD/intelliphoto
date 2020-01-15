// ---------- IntelliPhotoGui.cpp ----------

#include "IntelliPhotoGui.h"
#include "Layer/PaintingArea.h"

// IntelliPhotoGui constructor
IntelliPhotoGui::IntelliPhotoGui(){
		// create Gui elements and lay them out
		createGui();
		// Create actions
		createActions();
		// create Menus
		createMenus();
		// set style of the gui
		setIntelliStyle();
		// Size the app
		resize(600,600);
        //showMaximized();
        setDefaultToolValue();
}

// User tried to close the app
void IntelliPhotoGui::closeEvent(QCloseEvent*event){
		// If they try to close maybeSave() returns true
		// if no changes have been made and the app closes
		if (maybeSave()) {
				event->accept();
		} else {
				// If there have been changes ignore the event
				event->ignore();
		}
}

// Check if the current image has been changed and then
// open a dialog to open a file
void IntelliPhotoGui::slotOpen(){
		// Check if changes have been made since last save
		// maybeSave() returns true if no changes have been made
		if (maybeSave()) {

				// Get the file to open from a dialog
				// tr sets the window title to Open File
				// QDir opens the current dirctory
				QString fileName = QFileDialog::getOpenFileName(this,
				                                                tr("Open File"), QDir::currentPath(), nullptr, nullptr, QFileDialog::DontUseNativeDialog);

				// If we have a file name load the image and place
				// it in the paintingArea
				if (!fileName.isEmpty()) {
						paintingArea->open(fileName);
						UpdateGui();
				}
		}
}

// Called when the user clicks Save As in the menu
void IntelliPhotoGui::slotSave(){
		// A QAction represents the action of the user clicking
		QAction*action = qobject_cast<QAction*>(sender());

		// Stores the array of bytes of the users data
		QByteArray fileFormat = action->data().toByteArray();

		// Pass it to be saved
		saveFile(fileFormat);
}

// Opens a dialog that allows the user to create a New RASTER Layer
void IntelliPhotoGui::slotCreateNewRasterLayer(){
		// Stores button value
		bool ok1, ok2;

		// "New Layer" is the title of the window
		// the next tr is the text to display
		// Define the standard Value, min, max, step and ok button
		int width = IntelliInputDialog::getInt("New Layer", "Width:", 200, 1, paintingArea->getMaxWidth(), 1, &ok1);

		int height = IntelliInputDialog::getInt("New Layer", "Height:", 200, 1, paintingArea->getMaxHeight(), 1, &ok2);

		// Create New Layer
		if (ok1&&ok2) {
				paintingArea->addLayer(width,height,0,0,IntelliImage::ImageType::RASTERIMAGE);
				UpdateGui();
		}
}

// Opens a dialog that allows the user to create a New SHAPED Layer
void IntelliPhotoGui::slotCreateNewShapedLayer(){
		// Stores button value
		bool ok1, ok2;

		// "New Layer" is the title of the window
		// the next tr is the text to display
		// Define the standard Value, min, max, step and ok button
        int width = IntelliInputDialog::getInt("New Layer", "Width:", 200, 1, paintingArea->getMaxWidth(), 1, &ok1);

        int height = IntelliInputDialog::getInt("New Layer", "Height:", 200, 1, paintingArea->getMaxHeight(), 1, &ok2);

		// Create New Layer
		if (ok1&&ok2) {
				paintingArea->addLayer(width,height,0,0,IntelliImage::ImageType::SHAPEDIMAGE);
				UpdateGui();
		}
}

// Opens a dialog that allows the user to delete a Layer
void IntelliPhotoGui::slotDeleteLayer(){

        bool ok1;
		// "delete Layer" is the title of the window
		// the next tr is the text to display
		// Define the standard Value, min, max, step and ok button
        int layerNumber = IntelliInputDialog::getInt("Delete Layer", "Number:", paintingArea->getNumberOfActiveLayer()+1, 1, static_cast<int>(paintingArea->layerBundle.size()), 1, &ok1);

		// Create New Layer
        if(ok1){
                paintingArea->deleteLayer(layerNumber-1);
                UpdateGui();
        }
}

void IntelliPhotoGui::slotSetActiveAlpha(){

        bool ok1, ok2;
		// "Layer to set on" is the title of the window
		// the next tr is the text to display
		// Define the standard Value, min, max, step and ok button

        int layer = IntelliInputDialog::getInt("Layer to set on", "Layer:", paintingArea->getNumberOfActiveLayer()+1, 1, static_cast<int>(paintingArea->layerBundle.size()), 1, &ok1);

		// "New Alpha" is the title of the window
        int alpha = IntelliInputDialog::getInt("Layer to set on", "Alpha:", 255, 0, 255, 1, &ok2);

		if (ok1&&ok2)
		{
				paintingArea->setLayerAlpha(layer-1,alpha);
				UpdateGui();
		}
}

void IntelliPhotoGui::slotSetPolygon(){
		// Stores button value
		bool ok1;

		// "Layer to set on" is the title of the window
		// the next tr is the text to display
		// Define the standard Value, min, max, step and ok button
		int layer = IntelliInputDialog::getInt("Layer to set on", "Layer:", paintingArea->getNumberOfActiveLayer()+1, 1, static_cast<int>(paintingArea->layerBundle.size()), 1, &ok1);

		if (ok1)
		{
				paintingArea->setPolygon(layer-1);
				UpdateGui();
		}
}

void IntelliPhotoGui::slotPositionMoveUp(){
		paintingArea->movePositionActive(0,-20);
		update();
}

void IntelliPhotoGui::slotPositionMoveDown(){
		paintingArea->movePositionActive(0,20);
		update();
}

void IntelliPhotoGui::slotPositionMoveLeft(){
		paintingArea->movePositionActive(-20,0);
		update();
}

void IntelliPhotoGui::slotPositionMoveRight(){
		paintingArea->movePositionActive(20,0);
		update();
}

void IntelliPhotoGui::slotMoveLayerUp(){
		paintingArea->moveActiveLayer(1);
		update();
}

void IntelliPhotoGui::slotMoveLayerDown(){
		paintingArea->moveActiveLayer(-1);
		update();
}

void IntelliPhotoGui::slotSetActiveLayer(){
        bool ok1;
		// "Layer to set on" is the title of the window
		// the next tr is the text to display
		// Define the standard Value, min, max, step and ok button
        int layer = IntelliInputDialog::getInt("Layer to set on", "Layer:", 1, 1, static_cast<int>(paintingArea->layerBundle.size()), 1, &ok1);
		
        if(ok1){
                paintingArea->setLayerActive(layer-1);
                UpdateGui();
        }
}

void IntelliPhotoGui::slotUpdateRenderSettingsOn(){
		paintingArea->setRenderSettings(true);
		UpdateGui();
}

void IntelliPhotoGui::slotUpdateRenderSettingsOff(){
		paintingArea->setRenderSettings(false);
		UpdateGui();
}

void IntelliPhotoGui::slotSetFirstColor(){
		paintingArea->colorPickerSetFirstColor();
		UpdateGui();
}

void IntelliPhotoGui::slotSetSecondColor(){
		paintingArea->colorPickerSetSecondColor();
		UpdateGui();
}

void IntelliPhotoGui::slotSwapColor(){
		paintingArea->colorPickerSwapColors();
		UpdateGui();
}

void IntelliPhotoGui::slotCreatePenTool(){
		PenButton->setChecked(true);
		paintingArea->createPenTool();
}

void IntelliPhotoGui::slotCreatePlainTool(){
		PlainButton->setChecked(true);
		paintingArea->createPlainTool();
}

void IntelliPhotoGui::slotCreateLineTool(){
		LineButton->setChecked(true);
		paintingArea->createLineTool();
}

void IntelliPhotoGui::slotCreateRectangleTool(){
		RectangleButton->setChecked(true);
		paintingArea->createRectangleTool();
}

void IntelliPhotoGui::slotCreateCircleTool(){
		CircleButton->setChecked(true);
		paintingArea->createCircleTool();
}

void IntelliPhotoGui::slotCreatePolygonTool(){
		PolygonButton->setChecked(true);
		paintingArea->createPolygonTool();
}

void IntelliPhotoGui::slotCreateFloodFillTool(){
		FloodFillButton->setChecked(true);
		paintingArea->createFloodFillTool();
}

// Open an about dialog
void IntelliPhotoGui::slotAboutDialog(){
		// Window title and text to display
		QMessageBox::about(this, tr("About Painting"),
		                   tr("<p><b>IntelliPhoto - </b>A Pretty basic editor.</p> <br>Developed by Team 7."));
}

void IntelliPhotoGui::slotEnterPressed(){
        QString string = EditLineWidth->text();
        if(string.toInt() > 50) {
                EditLineWidth->setText("50");
        }
        paintingArea->Toolsettings.setLineWidth(string.toInt());
        string = EditLineInnerAlpha->text();
        if(string.toInt() > 255) {
                EditLineInnerAlpha->setText("255");
        }
        paintingArea->Toolsettings.setInnerAlpha(string.toInt());
}

void IntelliPhotoGui::slotResetTools(){
		CircleButton->setChecked(false);
		FloodFillButton->setChecked(false);
		LineButton->setChecked(false);
		PenButton->setChecked(false);
		PlainButton->setChecked(false);
		PolygonButton->setChecked(false);
		RectangleButton->setChecked(false);
}

void IntelliPhotoGui::slotSetWidth(){
        bool ok1;
        int temp = IntelliInputDialog::getInt("Toolsettings", "Width:", 5, 1, 50, 1, &ok1);
        if(ok1){
                paintingArea->Toolsettings.setLineWidth(temp);
                EditLineWidth->setText(QString("%1").arg(temp));
        }
}

void IntelliPhotoGui::slotSetInnerAlpha(){
        bool ok1;
        int temp = IntelliInputDialog::getInt("Toolsettings", "Width:", 5, 1, 50, 1, &ok1);
        if(ok1){
                paintingArea->Toolsettings.setInnerAlpha(temp);
                EditLineInnerAlpha->setText(QString("%1").arg(temp));
        }
}

// Define menu actions that call functions
void IntelliPhotoGui::createActions(){
		// Get a list of the supported file formats
		// QImageWriter is used to write images to files
		foreach (QByteArray format, QImageWriter::supportedImageFormats()) {
				QString text = tr("%1...").arg(QString(format).toUpper());

				// Create an action for each file format
				QAction*action = new QAction(text, this);

				// Set an action for each file format
				action->setData(format);

				// When clicked call IntelliPhotoGui::save()
				connect(action, SIGNAL(triggered()), this, SLOT(slotSave()));

				// Attach each file format option menu item to Save As
				actionSaveAs.append(action);
		}

		//set exporter to actions
		QAction*pngSaveAction = new QAction("PNG-8", this);
		pngSaveAction->setData("PNG");
		// When clicked call IntelliPhotoGui::save()
		connect(pngSaveAction, SIGNAL(triggered()), this, SLOT(slotSave()));
		// Attach each PNG in save Menu
		actionSaveAs.append(pngSaveAction);
		pngSaveAction->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_S));

		// Create exit action and tie to IntelliPhotoGui::close()
		actionExit = new QAction(tr("&Exit"), this);
		actionExit->setShortcuts(QKeySequence::Quit);
		connect(actionExit, SIGNAL(triggered()), this, SLOT(close()));

		actionOpen = new QAction(tr("&Open"), this);
		actionOpen->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
		connect(actionOpen, SIGNAL(triggered()), this, SLOT(slotOpen()));

		// Create New RASTER Layer action and tie to IntelliPhotoGui::newLayer()
		actionCreateNewRasterLayer = new QAction(tr("&Raster Image"), this);
		actionCreateNewRasterLayer->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
		connect(actionCreateNewRasterLayer, SIGNAL(triggered()), this, SLOT(slotCreateNewRasterLayer()));


		// Create New SHAPED Layer action and tie to IntelliPhotoGui::newLayer()
		actionCreateNewShapedLayer = new QAction(tr("&Shaped Image"), this);
		actionCreateNewShapedLayer->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N + Qt::ALT));
		connect(actionCreateNewShapedLayer, SIGNAL(triggered()), this, SLOT(slotCreateNewShapedLayer()));

		// Delete New Layer action and tie to IntelliPhotoGui::deleteLayer()
		actionDeleteLayer = new QAction(tr("&Delete Layer..."), this);
		actionDeleteLayer->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_D));
		connect(actionDeleteLayer, SIGNAL(triggered()), this, SLOT(slotDeleteLayer()));

		actionSetActiveLayer = new QAction(tr("&set Active"), this);
		actionSetActiveLayer->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));
		connect(actionSetActiveLayer, SIGNAL(triggered()), this, SLOT(slotSetActiveLayer()));

		actionSetActiveAlpha = new QAction(tr("&set Alpha"), this);
		actionSetActiveAlpha->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_A));
		connect(actionSetActiveAlpha, SIGNAL(triggered()), this, SLOT(slotSetActiveAlpha()));

		actionSetPolygon = new QAction(tr("&set new Polygondata"), this);
		actionSetPolygon->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_P));
		connect(actionSetPolygon, SIGNAL(triggered()), this, SLOT(slotSetPolygon()));

		actionMovePositionUp = new QAction(tr("&move Up"), this);
		actionMovePositionUp->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Up));
		connect(actionMovePositionUp, SIGNAL(triggered()), this, SLOT(slotPositionMoveUp()));

		actionMovePositionDown = new QAction(tr("&move Down"), this);
		actionMovePositionDown->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Down));
		connect(actionMovePositionDown, SIGNAL(triggered()), this, SLOT(slotPositionMoveDown()));

		actionMovePositionLeft = new QAction(tr("&move Left"), this);
		actionMovePositionLeft->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Left));
		connect(actionMovePositionLeft, SIGNAL(triggered()), this, SLOT(slotPositionMoveLeft()));

		actionMovePositionRight = new QAction(tr("&move Right"), this);
		actionMovePositionRight->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Right));
		connect(actionMovePositionRight, SIGNAL(triggered()), this, SLOT(slotPositionMoveRight()));

		actionMoveLayerUp = new QAction(tr("&move Layer Up"), this);
		actionMoveLayerUp->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_Up));
		connect(actionMoveLayerUp, SIGNAL(triggered()), this, SLOT(slotMoveLayerUp()));

		actionMoveLayerDown= new QAction(tr("&move Layer Down"), this);
		actionMoveLayerDown->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_Down));
		connect(actionMoveLayerDown, SIGNAL(triggered()), this, SLOT(slotMoveLayerDown()));

		//Create Update RenderSettings Actions here
		actionUpdateRenderSettingsOn = new QAction(tr("&On"), this);
		actionUpdateRenderSettingsOn->setShortcut(QKeySequence(Qt::ALT +Qt::SHIFT + +Qt::Key_A));
		connect(actionUpdateRenderSettingsOn, SIGNAL(triggered()),this, SLOT(slotUpdateRenderSettingsOn()));

		actionUpdateRenderSettingsOff = new QAction(tr("&Off"), this);
		actionUpdateRenderSettingsOff->setShortcut(QKeySequence(Qt::ALT +Qt::SHIFT + +Qt::Key_D));
		connect(actionUpdateRenderSettingsOff, SIGNAL(triggered()),this, SLOT(slotUpdateRenderSettingsOff()));

		//Create Color Actions here
		actionColorPickerFirstColor = new QAction(tr("&Main"), this);
		actionColorPickerFirstColor->setShortcut(QKeySequence(Qt::ALT + Qt::Key_N));
		connect(actionColorPickerFirstColor, SIGNAL(triggered()), this, SLOT(slotSetFirstColor()));
		connect(FirstColorButton, SIGNAL(clicked()), this, SLOT(slotSetFirstColor()));

		actionColorPickerSecondColor = new QAction(tr("&Secondary"), this);
		actionColorPickerSecondColor->setShortcut(QKeySequence(Qt::ALT + Qt::Key_M));
		connect(actionColorPickerSecondColor, SIGNAL(triggered()), this, SLOT(slotSetSecondColor()));
		connect(SecondColorButton, SIGNAL(clicked()), this, SLOT(slotSetSecondColor()));

		actionColorSwap = new QAction(tr("&Switch"), this);
		actionColorSwap->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_S));
		connect(actionColorSwap, SIGNAL(triggered()), this, SLOT(slotSwapColor()));
		connect(SwitchColorButton, SIGNAL(clicked()), this, SLOT(slotSwapColor()));

		//Create Tool actions down here
		actionCreatePlainTool = new QAction(tr("&Plain"), this);
		actionCreatePlainTool->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::SHIFT +Qt::Key_P));
		connect(actionCreatePlainTool, SIGNAL(triggered()), this, SLOT(slotResetTools()));
		connect(actionCreatePlainTool, SIGNAL(triggered()), this, SLOT(slotCreatePlainTool()));


		actionCreatePenTool = new QAction(tr("&Pen"),this);
		actionCreatePenTool->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::SHIFT +Qt::Key_S));
		connect(actionCreatePenTool, SIGNAL(triggered()), this, SLOT(slotResetTools()));
		connect(actionCreatePenTool, SIGNAL(triggered()), this, SLOT(slotCreatePenTool()));

		actionCreateLineTool = new QAction(tr("&Line"), this);
		actionCreateLineTool->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::SHIFT +Qt::Key_L));
		connect(actionCreateLineTool, SIGNAL(triggered()), this, SLOT(slotResetTools()));
		connect(actionCreateLineTool, SIGNAL(triggered()), this, SLOT(slotCreateLineTool()));

		actionCreateCircleTool = new QAction(tr("&Circle"), this);
		actionCreateCircleTool->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::SHIFT +Qt::Key_C));
		connect(actionCreateCircleTool, SIGNAL(triggered()), this, SLOT(slotResetTools()));
		connect(actionCreateCircleTool, SIGNAL(triggered()), this, SLOT(slotCreateCircleTool()));

		actionCreateRectangleTool = new QAction(tr("&Rectangle"), this);
		actionCreateRectangleTool->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::SHIFT +Qt::Key_R));
		connect(actionCreateRectangleTool, SIGNAL(triggered()), this, SLOT(slotResetTools()));
		connect(actionCreateRectangleTool, SIGNAL(triggered()), this, SLOT(slotCreateRectangleTool()));

		actionCreatePolygonTool = new QAction(tr("&Polygon"), this);
		actionCreatePolygonTool->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::SHIFT +Qt::Key_V));
		connect(actionCreatePolygonTool, SIGNAL(triggered()), this, SLOT(slotResetTools()));
		connect(actionCreatePolygonTool, SIGNAL(triggered()), this, SLOT(slotCreatePolygonTool()));

		actionCreateFloodFillTool = new QAction(tr("&FloodFill"), this);
		actionCreateFloodFillTool->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::SHIFT +Qt::Key_F));
		connect(actionCreateFloodFillTool, SIGNAL(triggered()), this, SLOT(slotResetTools()));
		connect(actionCreateFloodFillTool, SIGNAL(triggered()), this, SLOT(slotCreateFloodFillTool()));

		// Create about action and tie to IntelliPhotoGui::about()
		actionAboutDialog = new QAction(tr("&About"), this);
		actionAboutDialog->setShortcut(Qt::Key_F2);
		connect(actionAboutDialog, SIGNAL(triggered()), this, SLOT(slotAboutDialog()));

		// Create about Qt action and tie to IntelliPhotoGui::aboutQt()
		actionAboutQtDialog = new QAction(tr("About &Qt"), this);
		actionAboutQtDialog->setShortcut(Qt::Key_F3);
		connect(actionAboutQtDialog, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

		connect(EditLineWidth, SIGNAL(returnPressed()), this, SLOT(slotEnterPressed()));
		connect(EditLineInnerAlpha, SIGNAL(returnPressed()), this, SLOT(slotEnterPressed()));

		connect(CircleButton,SIGNAL(pressed()), this, SLOT(slotResetTools()));
		connect(CircleButton, SIGNAL(clicked()), this, SLOT(slotCreateCircleTool()));

		connect(FloodFillButton,SIGNAL(pressed()), this, SLOT(slotResetTools()));
		connect(FloodFillButton, SIGNAL(clicked()), this, SLOT(slotCreateFloodFillTool()));

		connect(LineButton,SIGNAL(pressed()), this, SLOT(slotResetTools()));
		connect(LineButton, SIGNAL(clicked()), this, SLOT(slotCreateLineTool()));

		connect(PenButton,SIGNAL(pressed()), this, SLOT(slotResetTools()));
		connect(PenButton, SIGNAL(clicked()), this, SLOT(slotCreatePenTool()));

		connect(PlainButton,SIGNAL(pressed()), this, SLOT(slotResetTools()));
		connect(PlainButton, SIGNAL(clicked()), this, SLOT(slotCreatePlainTool()));

		connect(PolygonButton,SIGNAL(pressed()), this, SLOT(slotResetTools()));
		connect(PolygonButton, SIGNAL(clicked()), this, SLOT(slotCreatePolygonTool()));

		connect(RectangleButton,SIGNAL(pressed()), this, SLOT(slotResetTools()));
		connect(RectangleButton, SIGNAL(clicked()), this, SLOT(slotCreateRectangleTool()));

		actionSetWidth = new QAction(tr("&Set Width"),this);
		actionSetWidth->setShortcut(QKeySequence(Qt::ALT + Qt::Key_W));
		connect(actionSetWidth, SIGNAL(triggered()), this, SLOT(slotSetWidth()));

		actionSetInnerAlpha = new QAction(tr("&Set Inner Alpha"),this);
		actionSetInnerAlpha->setShortcut(QKeySequence(Qt::ALT + Qt::Key_A));
		connect(actionSetInnerAlpha, SIGNAL(triggered()), this, SLOT(slotSetInnerAlpha()));
}

// Create the menubar
void IntelliPhotoGui::createMenus(){
		// Create Save As option and the list of file types
		saveAsMenu = new QMenu(tr("&Save As"), this);
		foreach (QAction *action, actionSaveAs)
		saveAsMenu->addAction(action);

		// Attach all actions to File
		fileMenu = new QMenu(tr("&File"), this);
		fileMenu->addAction(actionOpen);
		fileMenu->addMenu(saveAsMenu);
		fileMenu->addSeparator();
		fileMenu->addAction(actionExit);

		//Attach all actions to Render Settings
		renderMenu = new QMenu(tr("&Fast Renderer"), this);
		renderMenu->addAction(actionUpdateRenderSettingsOn);
		renderMenu->addAction(actionUpdateRenderSettingsOff);

		//Attach all Layer Creations to Menu
		layerCreationMenu = new QMenu(tr("&Create new Layer"), this);
		layerCreationMenu->addAction(actionCreateNewRasterLayer);
		layerCreationMenu->addAction(actionCreateNewShapedLayer);
		// Attach all actions to Layer
		layerMenu = new QMenu(tr("&Layer"), this);
		layerMenu->addMenu(layerCreationMenu);
		layerMenu->addSeparator();
		layerMenu->addAction(actionSetActiveAlpha);
		layerMenu->addAction(actionSetActiveLayer);
		layerMenu->addAction(actionSetPolygon);
		layerMenu->addSeparator();
		layerMenu->addAction(actionMovePositionUp);
		layerMenu->addAction(actionMovePositionDown);
		layerMenu->addAction(actionMovePositionLeft);
		layerMenu->addAction(actionMovePositionRight);
		layerMenu->addAction(actionMoveLayerUp);
		layerMenu->addAction(actionMoveLayerDown);
		layerMenu->addSeparator();
		layerMenu->addAction(actionDeleteLayer);

		//Attach all Color Options
		colorMenu = new QMenu(tr("&Color"), this);
		colorMenu->addAction(actionColorPickerFirstColor);
		colorMenu->addAction(actionColorPickerSecondColor);
		colorMenu->addAction(actionColorSwap);

		//Attach all Tool Creation Actions
		toolCreationMenu = new QMenu(tr("&Drawingtools"), this);
		toolCreationMenu->addAction(actionCreateCircleTool);
		toolCreationMenu->addAction(actionCreateFloodFillTool);
		toolCreationMenu->addAction(actionCreateLineTool);
		toolCreationMenu->addAction(actionCreatePenTool);
		toolCreationMenu->addAction(actionCreatePlainTool);
		toolCreationMenu->addAction(actionCreatePolygonTool);
		toolCreationMenu->addAction(actionCreateRectangleTool);

		//Attach all Tool Setting Actions
		toolSettingsMenu = new QMenu(tr("&Toolsettings"), this);
		toolSettingsMenu->addAction(actionSetWidth);
		toolSettingsMenu->addAction(actionSetInnerAlpha);

		//Attach all Tool Options
		toolMenu = new QMenu(tr("&Tools"), this);
		toolMenu->addMenu(toolCreationMenu);
		toolMenu->addMenu(toolSettingsMenu);
		toolMenu->addSeparator();
		toolMenu->addMenu(colorMenu);

		// Attach all actions to Options
		optionMenu = new QMenu(tr("&Options"), this);
		optionMenu->addMenu(layerMenu);
		optionMenu->addMenu(toolMenu);
		optionMenu->addSeparator();
		optionMenu->addMenu(renderMenu);

		// Attach all actions to Help
		helpMenu = new QMenu(tr("&Help"), this);
		helpMenu->addAction(actionAboutDialog);
		helpMenu->addAction(actionAboutQtDialog);

		// Add menu items to the menubar
		menuBar()->addMenu(fileMenu);
		menuBar()->addMenu(optionMenu);
		menuBar()->addMenu(helpMenu);
}

void IntelliPhotoGui::createGui(){
		// create a central widget to work on
		centralGuiWidget = new QWidget(this);
		setCentralWidget(centralGuiWidget);

		// create the grid for the layout
		mainLayout = new QGridLayout(centralGuiWidget);
		centralGuiWidget->setLayout(mainLayout);

		// create Gui elements
		paintingArea = new PaintingArea();
		paintingArea->DummyGui = this;

		preview = QPixmap(":/Icons/Buttons/icons/circle-tool.svg");
		CircleButton = new QPushButton();
		CircleButton->setFixedSize(Buttonsize);
		CircleButton->setIcon(preview);
		CircleButton->setIconSize(Buttonsize);
		CircleButton->setCheckable(true);

		preview = QPixmap(":/Icons/Buttons/icons/flood-fill-tool.svg");
		FloodFillButton = new QPushButton();
		FloodFillButton->setFixedSize(Buttonsize);
		FloodFillButton->setIcon(preview);
		FloodFillButton->setIconSize(Buttonsize);
		FloodFillButton->setCheckable(true);

		preview = QPixmap(":/Icons/Buttons/icons/line-tool.svg");
		LineButton = new QPushButton();
		LineButton->setFixedSize(Buttonsize);
		LineButton->setIcon(preview);
		LineButton->setIconSize(Buttonsize);
		LineButton->setCheckable(true);

		preview = QPixmap(":/Icons/Buttons/icons/pen-tool.svg");
		PenButton = new QPushButton();
		PenButton->setFixedSize(Buttonsize);
		PenButton->setIcon(preview);
		PenButton->setIconSize(Buttonsize);
		PenButton->setCheckable(true);

		preview = QPixmap(":/Icons/Buttons/icons/plain-tool.svg");
		PlainButton = new QPushButton();
		PlainButton->setFixedSize(Buttonsize);
		PlainButton->setIcon(preview);
		PlainButton->setIconSize(Buttonsize);
		PlainButton->setCheckable(true);

		preview = QPixmap(":/Icons/Buttons/icons/polygon-tool.svg");
		PolygonButton = new QPushButton();
		PolygonButton->setFixedSize(Buttonsize);
		PolygonButton->setIcon(preview);
		PolygonButton->setIconSize(Buttonsize);
		PolygonButton->setCheckable(true);

		preview = QPixmap(":/Icons/Buttons/icons/rectangle-tool.svg");
		RectangleButton = new QPushButton();
		RectangleButton->setFixedSize(Buttonsize);
		RectangleButton->setIcon(preview);
		RectangleButton->setIconSize(Buttonsize);
		RectangleButton->setCheckable(true);

		WidthLine = new QLabel();
		WidthLine->setText("Width");
		WidthLine->setFixedSize(Buttonsize.width()*2,(Buttonsize.height()*2)/3);

		EditLineWidth = new QLineEdit();
		EditLineWidth->setFixedSize(Buttonsize.width()*2,(Buttonsize.height()*2)/3);
		EditLineWidth->setText("5");
		ValidatorLineWidth = new QIntValidator();
		ValidatorLineWidth->setTop(99);
		ValidatorLineWidth->setBottom(1);
		EditLineWidth->setValidator(ValidatorLineWidth);

		innerAlphaLine = new QLabel();
		innerAlphaLine->setText("Inner Alpha");
		innerAlphaLine->setFixedSize(Buttonsize.width()*2,(Buttonsize.height()*2)/3);

		EditLineInnerAlpha = new QLineEdit();
		EditLineInnerAlpha->setFixedSize(Buttonsize.width()*2,(Buttonsize.height()*2)/3);
		EditLineInnerAlpha->setText("255");
		ValidatorInnerAlpha = new QIntValidator();
		ValidatorInnerAlpha->setTop(999);
		ValidatorInnerAlpha->setBottom(0);
		EditLineInnerAlpha->setValidator(ValidatorInnerAlpha);

		FirstColorButton = new QPushButton();
		FirstColorButton->setFixedSize(Buttonsize);

		SecondColorButton = new QPushButton();
		SecondColorButton->setFixedSize(Buttonsize);

		preview = QPixmap(":/Icons/Buttons/icons/Wechselpfeile.png");
		SwitchColorButton = new QPushButton();
		SwitchColorButton->setFixedSize(Buttonsize.width()*2,Buttonsize.height());
		SwitchColorButton->setIcon(preview);
		SwitchColorButton->setIconSize(QSize(Buttonsize.width()*2,Buttonsize.height()));

		ActiveLayerLine = new QLabel();
		QString string = QString("Active Layer: %1").arg(paintingArea->getNumberOfActiveLayer() + 1);
		ActiveLayerLine->setText(string);
		ActiveLayerLine->setFixedSize(Buttonsize.width()*2+10,(Buttonsize.height()*2)/3);

		IntelliImage* activePicture = paintingArea->getImageOfActiveLayer();
		if(activePicture) {
				preview = preview.fromImage(activePicture->getImageData());
		}else{
				QImage tmp(1,1,QImage::Format_ARGB32);
				tmp.fill(Qt::transparent);
				preview = preview.fromImage(tmp);
		}

		ActiveLayerImageLabel = new QLabel();
		ActiveLayerImageLabel->setFixedSize(Buttonsize*2);
		ActiveLayerImageLabel->setPixmap(preview.scaled(Buttonsize*2));

		// set gui elements
		mainLayout->addWidget(paintingArea,1,1,20,1);
		mainLayout->addWidget(CircleButton,1,2,1,1);
		mainLayout->addWidget(FloodFillButton,1,3,1,1);
		mainLayout->addWidget(LineButton,2,2,1,1);
		mainLayout->addWidget(PenButton,2,3,1,1);
		mainLayout->addWidget(PlainButton,3,2,1,1);
		mainLayout->addWidget(PolygonButton,3,3,1,1);
		mainLayout->addWidget(RectangleButton,4,2,1,1);
		mainLayout->addWidget(WidthLine,5,2,1,2);
		mainLayout->addWidget(EditLineWidth,6,2,1,2);
		mainLayout->addWidget(innerAlphaLine,7,2,1,2);
		mainLayout->addWidget(EditLineInnerAlpha,8,2,1,2);
		mainLayout->addWidget(FirstColorButton,9,2,1,1);
		mainLayout->addWidget(SecondColorButton,9,3,1,1);
		mainLayout->addWidget(SwitchColorButton,10,2,1,2);
		mainLayout->addWidget(ActiveLayerLine,11,2,1,2);
		mainLayout->addWidget(ActiveLayerImageLabel,12,2,1,2);
		mainLayout->setHorizontalSpacing(0);
}

void IntelliPhotoGui::setIntelliStyle(){
		// Set the title
		setWindowTitle("IntelliPhoto Prototype");
		// Set style sheet
        this->setStyleSheet("color: white;" "background-color: rgb(64, 64, 64);" "selection-color: rgb(200, 10, 10);" "selection-background-color: rgb(64, 64, 64);");

		QString string = QString("background-color: %1").arg(paintingArea->colorPicker.getFirstColor().name());
		FirstColorButton->setStyleSheet(string);
		string = QString("background-color: %1").arg(paintingArea->colorPicker.getSecondColor().name());
		SecondColorButton->setStyleSheet(string);
}

bool IntelliPhotoGui::maybeSave(){
		// Check for changes since last save

		// TODO insert variable for modified status here to make an save exit message
		if (false) {
				QMessageBox::StandardButton ret;

				// Painting is the title of the window
				// Add text and the buttons
				ret = QMessageBox::warning(this, tr("Painting"),
				                           tr("The image has been modified.\n"
				                              "Do you want to save your changes?"),
				                           QMessageBox::Save | QMessageBox::Discard
				                           | QMessageBox::Cancel);

				// If save button clicked call for file to be saved
				if (ret == QMessageBox::Save) {
						return saveFile("png");

						// If cancel do nothing
				} else if (ret == QMessageBox::Cancel) {
						return false;
				}
		}
		return true;
}

bool IntelliPhotoGui::saveFile(const QByteArray &fileFormat){
		// Define path, name and default file type
		QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

		// Get selected file from dialog
		// Add the proper file formats and extensions
		QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
		                                                initialPath,
		                                                tr("%1 Files (*.%2);;All Files (*)")
		                                                .arg(QString::fromLatin1(fileFormat.toUpper()))
		                                                .arg(QString::fromLatin1(fileFormat)), nullptr, QFileDialog::DontUseNativeDialog);

		// If no file do nothing
		if (fileName.isEmpty()) {
				return false;
		} else {
				// Call for the file to be saved
				return paintingArea->save(fileName, fileFormat.constData());
		}
}

void IntelliPhotoGui::setDefaultToolValue(){
        slotEnterPressed();
}

void IntelliPhotoGui::setToolWidth(int value){
		if(value < 1) {
				value = 1;
		}else if(value > 50) {
				value = 50;
		}
		EditLineWidth->setText(QString("%1").arg(value));
}

void IntelliPhotoGui::UpdateGui(){
		QString string = QString("Active Layer: %1").arg(paintingArea->getNumberOfActiveLayer() + 1);
		ActiveLayerLine->setText(string);

		IntelliImage* activePicture = paintingArea->getImageOfActiveLayer();
		if(activePicture) {
				preview = preview.fromImage(activePicture->getImageData());
		}else{
				QImage tmp(1,1,QImage::Format_ARGB32);
				tmp.fill(Qt::transparent);
				preview = preview.fromImage(tmp);
		}
		ActiveLayerImageLabel->setPixmap(preview.scaled(Buttonsize*2));

		string = QString("background-color: %1").arg(paintingArea->colorPicker.getFirstColor().name());
		FirstColorButton->setStyleSheet(string);
		string = QString("background-color: %1").arg(paintingArea->colorPicker.getSecondColor().name());
		SecondColorButton->setStyleSheet(string);
}
