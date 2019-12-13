// ---------- IntelliPhotoGui.cpp ----------

#include <QtWidgets>
#include <QPixmap>

#include "IntelliPhotoGui.h"
#include "Layer/PaintingArea.h"

// IntelliPhotoGui constructor
IntelliPhotoGui::IntelliPhotoGui(){
    //create Gui elements and lay them out
    createGui();
    // Create actions
    createActions();
    //create Menus
    createMenus();
    //set style of the gui
    setIntelliStyle();

    // Size the app
    showMaximized();
}

// User tried to close the app
void IntelliPhotoGui::closeEvent(QCloseEvent *event){
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
                                   tr("Open File"), QDir::currentPath());

        // If we have a file name load the image and place
        // it in the paintingArea
        if (!fileName.isEmpty())
            paintingArea->open(fileName);
    }
}

// Called when the user clicks Save As in the menu
void IntelliPhotoGui::slotSave(){
    // A QAction represents the action of the user clicking
    QAction *action = qobject_cast<QAction *>(sender());

    // Stores the array of bytes of the users data
    QByteArray fileFormat = action->data().toByteArray();

    // Pass it to be saved
    saveFile(fileFormat);
}

// Opens a dialog that allows the user to create a New Layer
void IntelliPhotoGui::slotCreateNewLayer(){
    // Stores button value
    bool ok1, ok2;

    // tr("New Layer") is the title
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

    // tr("delete Layer") is the title
    // the next tr is the text to display
    // Define the standard Value, min, max, step and ok button
    int layerNumber = QInputDialog::getInt(this, tr("delete Layer"),
                                        tr("Number:"),
                                        1,0, 500, 1, &ok);
    // Create New Layer
    if (ok)
        paintingArea->deleteLayer(layerNumber);
}

void slotCreatePenTool(){

}

void slotCreateFloodFillTool(){

}

void IntelliPhotoGui::slotSetActiveAlpha(){
    // Stores button value
    bool ok1, ok2;

    // tr("Layer to set on") is the title
    // the next tr is the text to display
    // Define the standard Value, min, max, step and ok button
    int layer = QInputDialog::getInt(this, tr("Layer to set on"),
                                        tr("Layer:"),
                                        -1,-1,100,1, &ok1);
    // tr("New Alpha") is the title
    int alpha = QInputDialog::getInt(this, tr("New Alpha"),
                                        tr("Alpha:"),
                                        255,0, 255, 1, &ok2);
    if (ok1&&ok2)
    {
        paintingArea->setAlphaOfLayer(layer,alpha);
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

    // tr("Red Input") is the title
    // the next tr is the text to display
    // Define the standard Value, min, max, step and ok button
    int red = QInputDialog::getInt(this, tr("Red Input"),
                                        tr("Red:"),
                                        255,0, 255,1, &ok1);
    // tr("Green Input") is the title
    int green = QInputDialog::getInt(this, tr("Green Input"),
                                        tr("Green:"),
                                        255,0, 255, 1, &ok2);
    // tr("Blue Input") is the title
    int blue = QInputDialog::getInt(this, tr("Blue Input"),
                                        tr("Blue:"),
                                        255,0, 255, 1, &ok3);
    // tr("Alpha Input") is the title
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

    // tr("Layer to set on") is the title
    // the next tr is the text to display
    // Define the standard Value, min, max, step and ok button
    int layer = QInputDialog::getInt(this, tr("Layer to set on"),
                                        tr("Layer:"),
                                        -1,0,255,1, &ok1);
    if (ok1)
    {
        paintingArea->setLayerToActive(layer);
    }
};

void IntelliPhotoGui::slotSetFirstColor(){
    paintingArea->colorPickerSetFirstColor();
}

void IntelliPhotoGui::slotSetSecondColor(){
    paintingArea->colorPickerSetSecondColor();
}

void IntelliPhotoGui::slotSwitchColor(){
    paintingArea->colorPickerSwitchColor();
}

void IntelliPhotoGui::slotCreatePenTool(){
    paintingArea->createPenTool();
}

void IntelliPhotoGui::slotCreatePlainTool(){
    paintingArea->createPlainTool();
}

void IntelliPhotoGui::slotCreateLineTool(){
    paintingArea->createLineTool();
}

// Open an about dialog
void IntelliPhotoGui::slotAboutDialog(){
    // Window title and text to display
    QMessageBox::about(this, tr("About Painting"),
            tr("<p><b>IntelliPhoto</b> Some nice ass looking software</p>"));
}

// Define menu actions that call functions
void IntelliPhotoGui::createActions(){
    // Get a list of the supported file formats
    // QImageWriter is used to write images to files
    foreach (QByteArray format, QImageWriter::supportedImageFormats()) {
        QString text = tr("%1...").arg(QString(format).toUpper());

        // Create an action for each file format
        QAction *action = new QAction(text, this);

        // Set an action for each file format
        action->setData(format);

        // When clicked call IntelliPhotoGui::save()
        connect(action, SIGNAL(triggered()), this, SLOT(slotSave()));

        // Attach each file format option menu item to Save As
        actionSaveAs.append(action);
    }

    //set exporter to actions
    QAction *pngSaveAction = new QAction("PNG-8", this);
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

    actionColorPickerSecondColor = new QAction(tr("&Secondary"), this);
    connect(actionColorPickerSecondColor, SIGNAL(triggered()), this, SLOT(slotSetFirstColor()));

    actionColorSwitch = new QAction(tr("&Switch"), this);
    actionColorSwitch->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_S));
    connect(actionColorSwitch, SIGNAL(triggered()), this, SLOT(slotSwitchColor()));

    //Create Tool actions down here
    actionCreatePlainTool = new QAction(tr("&Plain"), this);
    connect(actionCreatePlainTool, SIGNAL(triggered()), this, SLOT(slotCreatePlainTool()));

    actionCreatePenTool = new QAction(tr("&Pen"),this);
    connect(actionCreatePenTool, SIGNAL(triggered()), this, SLOT(slotCreatePenTool()));

    actionCreateLineTool = new QAction(tr("&Line"), this);
    connect(actionCreateLineTool, SIGNAL(triggered()), this, SLOT(slotCreateLineTool()));

    // Create about action and tie to IntelliPhotoGui::about()
    actionAboutDialog = new QAction(tr("&About"), this);
    connect(actionAboutDialog, SIGNAL(triggered()), this, SLOT(slotAboutDialog()));

    // Create about Qt action and tie to IntelliPhotoGui::aboutQt()
    actionAboutQtDialog = new QAction(tr("About &Qt"), this);
    connect(actionAboutQtDialog, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
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
    colorMenu->addAction(actionColorSwitch);

    //Attach all Tool Options
    toolMenu = new QMenu(tr("&Tools"), this);
    toolMenu->addAction(actionCreatePenTool);
    toolMenu->addAction(actionCreatePlainTool);
    toolMenu->addAction(actionCreateLineTool);
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
    //create a central widget to work on
    centralGuiWidget = new QWidget(this);
    setCentralWidget(centralGuiWidget);

    //create the grid for the layout
    mainLayout = new QGridLayout(centralGuiWidget);
    centralGuiWidget->setLayout(mainLayout);

    //create Gui elements
    paintingArea = new PaintingArea();

    //set gui elements
    mainLayout->addWidget(paintingArea);
}

void IntelliPhotoGui::setIntelliStyle(){
    // Set the title
    setWindowTitle("IntelliPhoto Prototype");
    //set style sheet
    this->setStyleSheet("background-color:rgb(64,64,64)");
    this->centralGuiWidget->setStyleSheet("color:rgb(255,255,255)");
    this->menuBar()->setStyleSheet("color:rgb(255,255,255)");
}

bool IntelliPhotoGui::maybeSave(){
    // Check for changes since last save

    //TODO insert variable for modified status here to make an save exit message
    if (false) {
       QMessageBox::StandardButton ret;

       // Painting is the title
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
                               .arg(QString::fromLatin1(fileFormat)));

    // If no file do nothing
    if (fileName.isEmpty()) {
        return false;
    } else {
        // Call for the file to be saved
        return paintingArea->save(fileName, fileFormat.constData());
    }
}
