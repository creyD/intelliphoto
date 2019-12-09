// ---------- IntelliPhotoGui.cpp ----------

#include <QtWidgets>
#include <QPixmap>

#include "IntelliPhotoGui.h"
#include "Layer/PaintingArea.h"

// IntelliPhotoGui constructor
IntelliPhotoGui::IntelliPhotoGui()
{   
    //create Gui elements and lay them out
    createGui();
    // Create actions
    createActions();
    //create Menus
    createMenus();
    //set style of the gui
    setIntelliStyle();

    // Size the app
    resize(500, 500);
}


// User tried to close the app
void IntelliPhotoGui::closeEvent(QCloseEvent *event)
{
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
void IntelliPhotoGui::open()
{
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
            paintingArea->openImage(fileName);
    }
}

// Called when the user clicks Save As in the menu
void IntelliPhotoGui::save()
{
    // A QAction represents the action of the user clicking
    QAction *action = qobject_cast<QAction *>(sender());

    // Stores the array of bytes of the users data
    QByteArray fileFormat = action->data().toByteArray();

    // Pass it to be saved
    saveFile(fileFormat);
}

// Opens a dialog that allows the user to create a New Layer
void IntelliPhotoGui::newLayer()
{
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
        int layer = paintingArea->addLayer(width,height,100,100);
        paintingArea->activate(layer);
    }
}

// Opens a dialog that allows the user to delete a Layer
void IntelliPhotoGui::deleteLayer()
{
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


void IntelliPhotoGui::onSetAlpha(){
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
        paintingArea->setAlphaToLayer(layer,alpha);
    }
}

void IntelliPhotoGui::onMoveUp(){
    paintingArea->moveActive(0,-2);
    update();
}

void IntelliPhotoGui::onMoveDown(){
    paintingArea->moveActive(0,2);
    update();
}

void IntelliPhotoGui::onMoveLeft(){
    paintingArea->moveActive(-2,0);
    update();
}

void IntelliPhotoGui::onMoveRight(){
    paintingArea->moveActive(2,0);
    update();
}

void IntelliPhotoGui::onMoveLayerUp(){
    paintingArea->moveActiveLayer(1);
    update();
}

void IntelliPhotoGui::onMoveLayerDown(){
    paintingArea->moveActiveLayer(-1);
    update();
}

void IntelliPhotoGui::onClearedPressed(){
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
        paintingArea->clearImage(red, green, blue, alpha);
    }
}

void IntelliPhotoGui::onActivePressed(){
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


// Open an about dialog
void IntelliPhotoGui::about()
{
    // Window title and text to display
    QMessageBox::about(this, tr("About Painting"),
            tr("<p><b>IntelliPhoto</b> Some nice ass looking software</p>"));
}

// Define menu actions that call functions
void IntelliPhotoGui::createActions()
{
    // Create the action tied to the menu
    openAct = new QAction(tr("&Open..."), this);

    // Define the associated shortcut key
    openAct->setShortcuts(QKeySequence::Open);

    // Tie the action to IntelliPhotoGui::open()
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    // Get a list of the supported file formats
    // QImageWriter is used to write images to files
    foreach (QByteArray format, QImageWriter::supportedImageFormats()) {
        QString text = tr("%1...").arg(QString(format).toUpper());

        // Create an action for each file format
        QAction *action = new QAction(text, this);

        // Set an action for each file format
        action->setData(format);

        // When clicked call IntelliPhotoGui::save()
        connect(action, SIGNAL(triggered()), this, SLOT(save()));

        // Attach each file format option menu item to Save As
        saveAsActs.append(action);
    }

    //set exporter to actions
    QAction *pngSaveAction = new QAction("PNG-8", this);
    pngSaveAction->setData("PNG");
    // When clicked call IntelliPhotoGui::save()
    connect(pngSaveAction, SIGNAL(triggered()), this, SLOT(save()));
    // Attach each PNG in save Menu
    saveAsActs.append(pngSaveAction);



    // Create exit action and tie to IntelliPhotoGui::close()
    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    // Create New Layer action and tie to IntelliPhotoGui::newLayer()
    newLayerAct = new QAction(tr("&New Layer..."), this);
    connect(newLayerAct, SIGNAL(triggered()), this, SLOT(newLayer()));


    // Delete New Layer action and tie to IntelliPhotoGui::deleteLayer()
    deleteLayerAct = new QAction(tr("&Delete Layer..."), this);
    connect(deleteLayerAct, SIGNAL(triggered()), this, SLOT(deleteLayer()));

    // Delete Active Layer action and tie to paintingArea::deleteActiveLayerLayer()
    deleteActiveLayerAct = new QAction(tr("&Delete active Layer"), this);
    connect(deleteActiveLayerAct, SIGNAL(triggered()), paintingArea, SLOT(deleteActiveLayer()));

    clearedActions = new QAction(tr("&clear Image"), this);
    connect(clearedActions, SIGNAL(triggered()), this, SLOT(onClearedPressed()));

    setActiveAction = new QAction(tr("&set Active"), this);
    connect(setActiveAction, SIGNAL(triggered()), this, SLOT(onActivePressed()));

    setAlphaAction = new QAction(tr("&set Alpha"), this);
    connect(setAlphaAction, SIGNAL(triggered()), this, SLOT(onSetAlpha()));

    moveUpAction = new QAction(tr("&move Up"), this);
    moveUpAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Up));
    connect(moveUpAction, SIGNAL(triggered()), this, SLOT(onMoveUp()));

    moveDownAction = new QAction(tr("&move Down"), this);
    moveDownAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Down));
    connect(moveDownAction, SIGNAL(triggered()), this, SLOT(onMoveDown()));

    moveLeftAction = new QAction(tr("&move Left"), this);
    moveLeftAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Left));
    connect(moveLeftAction, SIGNAL(triggered()), this, SLOT(onMoveLeft()));

    moveRightAction = new QAction(tr("&move Right"), this);
    moveRightAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Right));
    connect(moveRightAction, SIGNAL(triggered()), this, SLOT(onMoveRight()));

    moveLayerUpAction = new QAction(tr("&move Layer Up"), this);
    moveLayerUpAction->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_Up));
    connect(moveLayerUpAction, SIGNAL(triggered()), this, SLOT(onMoveLayerUp()));

    moveLayerDownAction= new QAction(tr("&move Layer Down"), this);
    moveLayerDownAction->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_Down));
    connect(moveLayerDownAction, SIGNAL(triggered()), this, SLOT(onMoveLayerDown()));

    // Create about action and tie to IntelliPhotoGui::about()
    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    // Create about Qt action and tie to IntelliPhotoGui::aboutQt()
    aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

// Create the menubar
void IntelliPhotoGui::createMenus()
{
    // Create Save As option and the list of file types
    saveAsMenu = new QMenu(tr("&Save As"), this);
    foreach (QAction *action, saveAsActs)
        saveAsMenu->addAction(action);


    // Attach all actions to File
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addMenu(saveAsMenu);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    // Attach all actions to Options
    optionMenu = new QMenu(tr("&Options"), this);
    optionMenu->addAction(clearedActions);
    optionMenu->addAction(setActiveAction);
    optionMenu->addAction(setAlphaAction);
    optionMenu->addAction(moveUpAction);
    optionMenu->addAction(moveDownAction);
    optionMenu->addAction(moveLeftAction);
    optionMenu->addAction(moveRightAction);
    optionMenu->addAction(moveLayerUpAction);
    optionMenu->addAction(moveLayerDownAction);

    // Attach all actions to Layer
    layerMenu = new QMenu(tr("&Layer"), this);
    layerMenu->addAction(newLayerAct);
    layerMenu->addAction(deleteLayerAct);
    layerMenu->addAction(deleteActiveLayerAct);

    //Attach all Tool Options
    toolMenu = new QMenu(tr("&Tools"), this);

    // Attach all actions to Help
    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

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

bool IntelliPhotoGui::maybeSave()
{
    // Check for changes since last save
    if (paintingArea->isModified()) {
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

bool IntelliPhotoGui::saveFile(const QByteArray &fileFormat)
{
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
        return paintingArea->saveImage(fileName, fileFormat.constData());
    }
}

