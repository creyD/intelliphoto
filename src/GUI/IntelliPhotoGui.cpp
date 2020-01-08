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
		showMaximized();
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
				if (!fileName.isEmpty())
						paintingArea->open(fileName);
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

// Opens a dialog that allows the user to create a New Layer
void IntelliPhotoGui::slotCreateNewLayer(){
		// Stores button value
		bool ok1, ok2;

		// "New Layer" is the title of the window
		// the next tr is the text to display
		// Define the standard Value, min, max, step and ok button
		int width = QInputDialog::getInt(this, tr("New Layer"),
		                                 tr("Width:"),
		                                 200,1, 500, 1, &ok1);
		int height = QInputDialog::getInt(this, tr("New Layer"),
		                                  tr("Height:"),
		                                  200,1, 500, 1, &ok2);
		// Create New Layer
		if (ok1&&ok2)
		{
				int layer = paintingArea->addLayer(width,height,0,0);
				paintingArea->slotActivateLayer(layer);
		}
}

// Opens a dialog that allows the user to delete a Layer
void IntelliPhotoGui::slotDeleteLayer(){
		// Stores button value
		bool ok;

		// "delete Layer" is the title of the window
		// the next tr is the text to display
		// Define the standard Value, min, max, step and ok button
		int layerNumber = QInputDialog::getInt(this, tr("delete Layer"),
		                                       tr("Number:"),
		                                       1,0, 500, 1, &ok);
		// Create New Layer
        if (ok){
				paintingArea->deleteLayer(layerNumber);
                QString string = QString("Active Layer: %1").arg(paintingArea->getNumberOfActiveLayer());
                ActiveLayerLine->setText(string);
        }
}

void IntelliPhotoGui::slotSetActiveAlpha(){
		// Stores button value
		bool ok1, ok2;

		// "Layer to set on" is the title of the window
		// the next tr is the text to display
		// Define the standard Value, min, max, step and ok button
		int layer = QInputDialog::getInt(this, tr("Layer to set on"),
		                                 tr("Layer:"),
		                                 -1,-1,100,1, &ok1);
		// "New Alpha" is the title of the window
		int alpha = QInputDialog::getInt(this, tr("New Alpha"),
		                                 tr("Alpha:"),
		                                 255,0, 255, 1, &ok2);
		if (ok1&&ok2)
		{
				paintingArea->setLayerAlpha(layer,alpha);
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

void IntelliPhotoGui::slotClearActiveLayer(){
		// Stores button value
		bool ok1, ok2, ok3, ok4;

		// "Red Input" is the title of the window
		// the next tr is the text to display
		// Define the standard Value, min, max, step and ok button
		int red = QInputDialog::getInt(this, tr("Red Input"),
		                               tr("Red:"),
		                               255,0, 255,1, &ok1);
		// "Green Input" is the title of the window
		int green = QInputDialog::getInt(this, tr("Green Input"),
		                                 tr("Green:"),
		                                 255,0, 255, 1, &ok2);
		// "Blue Input" is the title of the window
		int blue = QInputDialog::getInt(this, tr("Blue Input"),
		                                tr("Blue:"),
		                                255,0, 255, 1, &ok3);
		// "Alpha Input" is the title of the window
		int alpha = QInputDialog::getInt(this, tr("Alpha Input"),
		                                 tr("Alpha:"),
		                                 255,0, 255, 1, &ok4);
		if (ok1&&ok2&&ok3&&ok4)
		{
				paintingArea->floodFill(red, green, blue, alpha);
		}
}

void IntelliPhotoGui::slotSetActiveLayer(){
		// Stores button value
		bool ok1;

		// "Layer to set on" is the title of the window
		// the next tr is the text to display
		// Define the standard Value, min, max, step and ok button
		int layer = QInputDialog::getInt(this, tr("Layer to set on"),
		                                 tr("Layer:"),
		                                 -1,0,255,1, &ok1);
		if (ok1)
		{
				paintingArea->setLayerActive(layer);
                QString string = QString("Active Layer: %1").arg(paintingArea->getNumberOfActiveLayer());
                ActiveLayerLine->setText(string);
		}
}

void IntelliPhotoGui::slotSetFirstColor(){
		paintingArea->colorPickerSetFirstColor();
        QString string = QString("background-color: %1").arg(paintingArea->colorPicker.getFirstColor().name());
        FirstColorButton->setStyleSheet(string);
}

void IntelliPhotoGui::slotSetSecondColor(){
		paintingArea->colorPickerSetSecondColor();
        QString string = QString("background-color: %1").arg(paintingArea->colorPicker.getSecondColor().name());
        SecondColorButton->setStyleSheet(string);
}

void IntelliPhotoGui::slotSwapColor(){
		paintingArea->colorPickerSwapColors();
        QString string = QString("background-color: %1").arg(paintingArea->colorPicker.getFirstColor().name());
        FirstColorButton->setStyleSheet(string);
        string = QString("background-color: %1").arg(paintingArea->colorPicker.getSecondColor().name());
        SecondColorButton->setStyleSheet(string);
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
		                   tr("<p><b>IntelliPhoto</b>Pretty basic editor.</p>"));
}

void IntelliPhotoGui::slotEnterPressed(){
    QString string = EditLineWidth->text();
    if(string.toInt() > 50){
        EditLineWidth->setText("50");
    }
    paintingArea->Toolsettings.setLineWidth(string.toInt());
    string = EditLineInnerAlpha->text();
    if(string.toInt() > 255){
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

		// Create exit action and tie to IntelliPhotoGui::close()
		actionExit = new QAction(tr("&Exit"), this);
		actionExit->setShortcuts(QKeySequence::Quit);
		connect(actionExit, SIGNAL(triggered()), this, SLOT(close()));

		actionOpen = new QAction(tr("&Open"), this);
		actionOpen->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
		connect(actionOpen, SIGNAL(triggered()), this, SLOT(slotOpen()));

		// Create New Layer action and tie to IntelliPhotoGui::newLayer()
		actionCreateNewLayer = new QAction(tr("&New Layer..."), this);
		actionCreateNewLayer->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
		connect(actionCreateNewLayer, SIGNAL(triggered()), this, SLOT(slotCreateNewLayer()));

		// Delete New Layer action and tie to IntelliPhotoGui::deleteLayer()
		actionDeleteLayer = new QAction(tr("&Delete Layer..."), this);
		connect(actionDeleteLayer, SIGNAL(triggered()), this, SLOT(slotDeleteLayer()));

		actionSetActiveLayer = new QAction(tr("&set Active"), this);
		connect(actionSetActiveLayer, SIGNAL(triggered()), this, SLOT(slotSetActiveLayer()));

		actionSetActiveAlpha = new QAction(tr("&set Alpha"), this);
		connect(actionSetActiveAlpha, SIGNAL(triggered()), this, SLOT(slotSetActiveAlpha()));

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

		//Create Color Actions here
		actionColorPickerFirstColor = new QAction(tr("&Main"), this);
		connect(actionColorPickerFirstColor, SIGNAL(triggered()), this, SLOT(slotSetFirstColor()));
        connect(FirstColorButton, SIGNAL(clicked()), this, SLOT(slotSetFirstColor()));

		actionColorPickerSecondColor = new QAction(tr("&Secondary"), this);
		connect(actionColorPickerSecondColor, SIGNAL(triggered()), this, SLOT(slotSetSecondColor()));
        connect(SecondColorButton, SIGNAL(clicked()), this, SLOT(slotSetSecondColor()));

		actionColorSwap = new QAction(tr("&Switch"), this);
		actionColorSwap->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_S));
		connect(actionColorSwap, SIGNAL(triggered()), this, SLOT(slotSwapColor()));
        connect(SwitchColorButton, SIGNAL(clicked()), this, SLOT(slotSwapColor()));

		//Create Tool actions down here
		actionCreatePlainTool = new QAction(tr("&Plain"), this);
        connect(actionCreatePlainTool, SIGNAL(triggered()), this, SLOT(slotResetTools()));
		connect(actionCreatePlainTool, SIGNAL(triggered()), this, SLOT(slotCreatePlainTool()));


		actionCreatePenTool = new QAction(tr("&Pen"),this);
        connect(actionCreatePenTool, SIGNAL(triggered()), this, SLOT(slotResetTools()));
        connect(actionCreatePenTool, SIGNAL(triggered()), this, SLOT(slotCreatePenTool()));

		actionCreateLineTool = new QAction(tr("&Line"), this);
        connect(actionCreateLineTool, SIGNAL(triggered()), this, SLOT(slotResetTools()));
		connect(actionCreateLineTool, SIGNAL(triggered()), this, SLOT(slotCreateLineTool()));

		actionCreateCircleTool = new QAction(tr("&Circle"), this);
        connect(actionCreateCircleTool, SIGNAL(triggered()), this, SLOT(slotResetTools()));
		connect(actionCreateCircleTool, SIGNAL(triggered()), this, SLOT(slotCreateCircleTool()));

		actionCreateRectangleTool = new QAction(tr("&Rectangle"), this);
        connect(actionCreateRectangleTool, SIGNAL(triggered()), this, SLOT(slotResetTools()));
		connect(actionCreateRectangleTool, SIGNAL(triggered()), this, SLOT(slotCreateRectangleTool()));

		actionCreatePolygonTool = new QAction(tr("&Polygon"), this);
        connect(actionCreatePolygonTool, SIGNAL(triggered()), this, SLOT(slotResetTools()));
		connect(actionCreatePolygonTool, SIGNAL(triggered()), this, SLOT(slotCreatePolygonTool()));

		actionCreateFloodFillTool = new QAction(tr("&FloodFill"), this);
        connect(actionCreateFloodFillTool, SIGNAL(triggered()), this, SLOT(slotResetTools()));
		connect(actionCreateFloodFillTool, SIGNAL(triggered()), this, SLOT(slotCreateFloodFillTool()));

		// Create about action and tie to IntelliPhotoGui::about()
		actionAboutDialog = new QAction(tr("&About"), this);
		connect(actionAboutDialog, SIGNAL(triggered()), this, SLOT(slotAboutDialog()));

		// Create about Qt action and tie to IntelliPhotoGui::aboutQt()
		actionAboutQtDialog = new QAction(tr("About &Qt"), this);
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

		// Attach all actions to Options
		optionMenu = new QMenu(tr("&Options"), this);
		optionMenu->addAction(actionSetActiveLayer);
		optionMenu->addAction(actionSetActiveAlpha);
		optionMenu->addAction(actionMovePositionUp);
		optionMenu->addAction(actionMovePositionDown);
		optionMenu->addAction(actionMovePositionLeft);
		optionMenu->addAction(actionMovePositionRight);
		optionMenu->addAction(actionMoveLayerUp);
		optionMenu->addAction(actionMoveLayerDown);

		// Attach all actions to Layer
		layerMenu = new QMenu(tr("&Layer"), this);
		layerMenu->addAction(actionCreateNewLayer);
		layerMenu->addAction(actionDeleteLayer);

		//Attach all Color Options
		colorMenu = new QMenu(tr("&Color"), this);
		colorMenu->addAction(actionColorPickerFirstColor);
		colorMenu->addAction(actionColorPickerSecondColor);
		colorMenu->addAction(actionColorSwap);

		//Attach all Tool Options
		toolMenu = new QMenu(tr("&Tools"), this);
        toolMenu->addAction(actionCreateCircleTool);
        toolMenu->addAction(actionCreateFloodFillTool);
        toolMenu->addAction(actionCreateLineTool);
		toolMenu->addAction(actionCreatePenTool);
		toolMenu->addAction(actionCreatePlainTool);
        toolMenu->addAction(actionCreatePolygonTool);
		toolMenu->addAction(actionCreateRectangleTool);
		toolMenu->addSeparator();
		toolMenu->addMenu(colorMenu);

		// Attach all actions to Help
		helpMenu = new QMenu(tr("&Help"), this);
		helpMenu->addAction(actionAboutDialog);
		helpMenu->addAction(actionAboutQtDialog);

		// Add menu items to the menubar
		menuBar()->addMenu(fileMenu);
		menuBar()->addMenu(optionMenu);
		menuBar()->addMenu(layerMenu);
		menuBar()->addMenu(toolMenu);
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

        p = QPixmap(":/Icons/Buttons/icons/circle-tool.svg");
        CircleButton = new QPushButton();
        CircleButton->setFixedSize(Buttonsize);
        CircleButton->setIcon(p);
        CircleButton->setIconSize(Buttonsize);
        CircleButton->setCheckable(true);

        p = QPixmap(":/Icons/Buttons/icons/flood-fill-tool.svg");
        FloodFillButton = new QPushButton();
        FloodFillButton->setFixedSize(Buttonsize);
        FloodFillButton->setIcon(p);
        FloodFillButton->setIconSize(Buttonsize);
        FloodFillButton->setCheckable(true);

        p = QPixmap(":/Icons/Buttons/icons/icon.png");
        LineButton = new QPushButton();
        LineButton->setFixedSize(Buttonsize);
        LineButton->setIcon(p);
        LineButton->setIconSize(Buttonsize);
        LineButton->setCheckable(true);

        p = QPixmap(":/Icons/Buttons/icons/pen-tool.svg");
        PenButton = new QPushButton();
        PenButton->setFixedSize(Buttonsize);
        PenButton->setIcon(p);
        PenButton->setIconSize(Buttonsize);
        PenButton->setCheckable(true);

        p = QPixmap(":/Icons/Buttons/icons/icon.png");
        PlainButton = new QPushButton();
        PlainButton->setFixedSize(Buttonsize);
        PlainButton->setIcon(p);
        PlainButton->setIconSize(Buttonsize);
        PlainButton->setCheckable(true);

        p = QPixmap(":/Icons/Buttons/icons/polygon-tool.svg");
        PolygonButton = new QPushButton();
        PolygonButton->setFixedSize(Buttonsize);
        PolygonButton->setIcon(p);
        PolygonButton->setIconSize(Buttonsize);
        PolygonButton->setCheckable(true);

        p = QPixmap(":/Icons/Buttons/icons/rectangle-tool.svg");
        RectangleButton = new QPushButton();
        RectangleButton->setFixedSize(Buttonsize);
        RectangleButton->setIcon(p);
        RectangleButton->setIconSize(Buttonsize);
        RectangleButton->setCheckable(true);

        WidthLine = new QLabel();
        WidthLine->setText("Width");
        WidthLine->setFixedSize(Buttonsize.width(),Buttonsize.height()/3);

        EditLineWidth = new QLineEdit();
        EditLineWidth->setFixedSize(Buttonsize.width(),Buttonsize.height()/3);
        EditLineWidth->setText("5");
        ValidatorLineWidth = new QIntValidator();
        ValidatorLineWidth->setTop(99);
        ValidatorLineWidth->setBottom(1);
        EditLineWidth->setValidator(ValidatorLineWidth);

        innerAlphaLine = new QLabel();
        innerAlphaLine->setText("Inner Alpha");
        innerAlphaLine->setFixedSize(Buttonsize.width(),Buttonsize.height()/3);

        EditLineInnerAlpha = new QLineEdit();
        EditLineInnerAlpha->setFixedSize(Buttonsize.width(),Buttonsize.height()/3);
        EditLineInnerAlpha->setText("255");
        ValidatorInnerAlpha = new QIntValidator();
        ValidatorInnerAlpha->setTop(999);
        ValidatorInnerAlpha->setBottom(0);
        EditLineInnerAlpha->setValidator(ValidatorInnerAlpha);

        FirstColorButton = new QPushButton();
        FirstColorButton->setFixedSize(Buttonsize/2);

        SecondColorButton = new QPushButton();
        SecondColorButton->setFixedSize(Buttonsize/2);

        p = QPixmap(":/Icons/Buttons/icons/Wechselpfeile.png");
        SwitchColorButton = new QPushButton();
        SwitchColorButton->setFixedSize(Buttonsize.width(),Buttonsize.height()/2);
        SwitchColorButton->setIcon(p);
        SwitchColorButton->setIconSize(QSize(Buttonsize.width(),Buttonsize.height()/2));

        ActiveLayerLine = new QLabel();
        QString string = QString("Active Layer: %1").arg(paintingArea->getNumberOfActiveLayer());
        ActiveLayerLine->setText(string);
        ActiveLayerLine->setFixedSize(Buttonsize.width()+10,Buttonsize.height()/3);

		// set gui elements

        mainLayout->addWidget(paintingArea,1,1,20,1);
        mainLayout->addWidget(CircleButton,1,2,1,2);
        mainLayout->addWidget(FloodFillButton,2,2,1,2);
        mainLayout->addWidget(LineButton,3,2,1,2);
        mainLayout->addWidget(PenButton,4,2,1,2);
        mainLayout->addWidget(PlainButton,5,2,1,2);
        mainLayout->addWidget(PolygonButton,6,2,1,2);
        mainLayout->addWidget(RectangleButton,7,2,1,2);
        mainLayout->addWidget(WidthLine,8,2,1,2);
        mainLayout->addWidget(EditLineWidth,9,2,1,2);
        mainLayout->addWidget(innerAlphaLine,10,2,1,2);
        mainLayout->addWidget(EditLineInnerAlpha,11,2,1,2);
        mainLayout->addWidget(FirstColorButton,12,2,1,1);
        mainLayout->addWidget(SecondColorButton,12,3,1,1);
        mainLayout->addWidget(SwitchColorButton,13,2,1,2);
        mainLayout->addWidget(ActiveLayerLine,14,2,1,2);
}

void IntelliPhotoGui::setIntelliStyle(){
		// Set the title
		setWindowTitle("IntelliPhoto Prototype");
		// Set style sheet
        this->setStyleSheet("background-color:rgb(64,64,64)");
        this->centralGuiWidget->setStyleSheet("color:rgb(255,255,255)");
		this->menuBar()->setStyleSheet("color:rgb(255,255,255)");
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
