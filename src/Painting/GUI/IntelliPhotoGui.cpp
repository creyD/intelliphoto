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

// Opens a dialog to change the pen color
void IntelliPhotoGui::penColor()
{
    // Store the chosen color from the dialog
    QColor newColor = QColorDialog::getColor(paintingArea->penColor());

    // If a valid color set it
    if (newColor.isValid())
        paintingArea->setPenColor(newColor);
}

// Opens a dialog that allows the user to change the pen width
void IntelliPhotoGui::penWidth()
{
    // Stores button value
    bool ok;

    // tr("Painting") is the title
    // the next tr is the text to display
    // Get the current pen width
    // Define the min, max, step and ok button
    int newWidth = QInputDialog::getInt(this, tr("Painting"),
                                        tr("Select pen width:"),
                                        paintingArea->penWidth(),
                                        1, 500, 1, &ok);
    // Change the pen width
    if (ok)
        paintingArea->setPenWidth(newWidth);
}

// Opens a dialog that allows the user to create a new Layer
void IntelliPhotoGui::newLayer()
{
    // Stores button value
    bool ok;

    // tr("new Layer") is the title
    // the next tr is the text to display
    // Get the current pen width
    // Define the min, max, step and ok button
    int width = QInputDialog::getInt(this, tr("new Layer"),
                                        tr("Width:"),
                                        200,1, 500, 1, &ok);
    int height = QInputDialog::getInt(this, tr("new Layer"),
                                        tr("Height:"),
                                        200,1, 500, 1, &ok);
    // Change the pen width
    if (ok)
    {
        int layer = paintingArea->addLayer(width,height,100,100);
        paintingArea->activate(layer);
    }
}

// Open an about dialog
void IntelliPhotoGui::about()
{
    // Window title and text to display
    QMessageBox::about(this, tr("About Painting"),
            tr("<p><b>IntelliPhoto</b> Some nice ass looking software</p>"));
}

void IntelliPhotoGui::onSetAlpha(){
    int a = this->setAlphaEdit->text().toInt();
    emit this->sendAlpha(a);
}

void IntelliPhotoGui::onMoveUp(){
    int a = 5;
    emit this->moveUp(a);
}

void IntelliPhotoGui::onMoveDown(){
    int a = 5;
    emit this->moveDown(a);
}

void IntelliPhotoGui::onMoveLeft(){
    int a = 5;
    emit this->moveLeft(a);
}

void IntelliPhotoGui::onMoveRight(){
    int a = 5;
    emit this->moveRight(a);
}

void IntelliPhotoGui::onMoveLayerUp(){
    emit this->moveLayerUp();
}

void IntelliPhotoGui::onMoveLayerDown(){
    emit this->moveLayerDown();
}

void IntelliPhotoGui::onClearedPressed(){
    int r = this->RedEdit->text().toInt();
    int g = this->GreenEdit->text().toInt();
    int b = this->BlueEdit->text().toInt();
    emit this->sendClearColor(r,g,b);
}

void IntelliPhotoGui::onActivePressed(){
    int a = this->selectActiveEdit->text().toInt();
    emit this->sendActiveLayer(a);
};



// Define menu actions that call functions
void IntelliPhotoGui::createActions()
{
    //connect signal and slots of gui element
    connect(this->clearButton, SIGNAL(clicked()), this, SLOT(onClearedPressed()));
    connect(this, SIGNAL(sendClearColor(int,int,int)), paintingArea, SLOT(clearImage(int, int, int)));

    connect(this->selectActiveButton, SIGNAL(clicked()), this, SLOT(onActivePressed()));
    connect(this, SIGNAL(sendActiveLayer(int)),paintingArea, SLOT(activate(int)));

    connect(this->setAlphaButton, SIGNAL(clicked()), this, SLOT(onSetAlpha()));
    connect(this, SIGNAL(sendAlpha(int)), paintingArea, SLOT(setAlpha(int)));

    connect(this->moveActiveUpButton, SIGNAL(clicked()), this, SLOT(onMoveUp()));
    connect(this, SIGNAL(moveUp(int)), paintingArea, SLOT(getMoveUp(int)));

    connect(this->moveActiveDownButton, SIGNAL(clicked()), this, SLOT(onMoveDown()));
    connect(this, SIGNAL(moveDown(int)), paintingArea, SLOT(getMoveDown(int)));

    connect(this->moveActiveLeftButton, SIGNAL(clicked()), this, SLOT(onMoveLeft()));
    connect(this, SIGNAL(moveLeft(int)), paintingArea, SLOT(getMoveLeft(int)));

    connect(this->moveActiveRightButton, SIGNAL(clicked()), this, SLOT(onMoveRight()));
    connect(this, SIGNAL(moveRight(int)), paintingArea, SLOT(getMoveRight(int)));

    connect(this->layerMoveActiveDownButton, SIGNAL(clicked()), this, SLOT(onMoveLayerDown()));
    connect(this, SIGNAL(moveLayerDown()), paintingArea, SLOT(getMoveLayerDown()));

    connect(this->layerMoveActiveUpButton, SIGNAL(clicked()), this, SLOT(onMoveLayerUp()));
    connect(this, SIGNAL(moveLayerUp()), paintingArea, SLOT(getMoveLayerUp()));



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

    QAction *action = new QAction("PNG-8", this);

    // Set an action for each file format
    action->setData("PNG");

    // When clicked call IntelliPhotoGui::save()
    connect(action, SIGNAL(triggered()), this, SLOT(save()));

    // Attach each file format option menu item to Save As
    saveAsActs.append(action);


    // Create exit action and tie to IntelliPhotoGui::close()
    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    // Create pen color action and tie to IntelliPhotoGui::penColor()
    penColorAct = new QAction(tr("&Pen Color..."), this);
    connect(penColorAct, SIGNAL(triggered()), this, SLOT(penColor()));

    // Create pen width action and tie to IntelliPhotoGui::penWidth()
    penWidthAct = new QAction(tr("Pen &Width..."), this);
    connect(penWidthAct, SIGNAL(triggered()), this, SLOT(penWidth()));

    // Create clear screen action and tie to IntelliPhotoGui::clearImage()
    clearScreenAct = new QAction(tr("&Clear Screen"), this);
    clearScreenAct->setShortcut(tr("Ctrl+L"));
    connect(clearScreenAct, SIGNAL(triggered()),
            this, SLOT(onClearedPressed()));

    // Create New Layer action and tie to IntelliPhotoGui::newLayer()
    newLayerAct = new QAction(tr("&new Layer..."), this);
    connect(newLayerAct, SIGNAL(triggered()), this, SLOT(newLayer()));

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
    optionMenu->addAction(penColorAct);
    optionMenu->addAction(penWidthAct);
    optionMenu->addSeparator();
    optionMenu->addAction(clearScreenAct);

    // Attach all actions to Layer
    layerMenu = new QMenu(tr("&Layer"), this);
    layerMenu->addAction(newLayerAct);

    // Attach all actions to Help
    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    // Add menu items to the menubar
    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(optionMenu);
    menuBar()->addMenu(layerMenu);
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
    clearButton = new QPushButton("set Color");
    paintingArea = new PaintingArea();


    RedLabel = new QLabel("Red:");
    GreenLabel = new QLabel("Green");
    BlueLabel = new QLabel("Blue:");
    RedEdit = new QLineEdit("255");
    GreenEdit = new QLineEdit("255");
    BlueEdit = new QLineEdit("255");
    RedEdit->setMaximumSize(150,20);
    GreenEdit->setMaximumSize(150,20);
    BlueEdit->setMaximumSize(150,20);

    selectActiveButton = new QPushButton("select Active");
    selectActiveLabel = new QLabel("Active:");
    selectActiveEdit = new QLineEdit("0");
    selectActiveLabel->setMaximumSize(150,20);
    selectActiveEdit->setMaximumSize(150,20);

    setAlphaButton = new QPushButton("set Alpha");
    setAlphaLabel = new QLabel("Alpha:");
    setAlphaEdit = new QLineEdit("255");
    setAlphaEdit->setMaximumSize(150,20);

    moveActiveUpButton = new QPushButton("move 5 Up");
    moveActiveDownButton = new QPushButton("move 5 Down");
    moveActiveLeftButton = new QPushButton("move 5 Left");
    moveActiveRightButton = new QPushButton("move 5 Right");

    layerMoveActiveDownButton = new QPushButton("Active Layer Down");
    layerMoveActiveUpButton = new QPushButton("Active Layer Up");

    //set gui elemtns position
    mainLayout->addWidget(clearButton,0,25,1,1);
    mainLayout->addWidget(paintingArea,0,0,25,25);

    mainLayout->addWidget(RedLabel,1,25,1,1);
    mainLayout->addWidget(RedEdit,2,25,1,1);
    mainLayout->addWidget(GreenLabel,3,25,1,1);
    mainLayout->addWidget(GreenEdit,4,25,1,1);
    mainLayout->addWidget(BlueLabel,5,25,1,1);
    mainLayout->addWidget(BlueEdit,6,25,1,1);

    mainLayout->addWidget(selectActiveButton,7,25,1,1);
    mainLayout->addWidget(selectActiveLabel,8,25,1,1);
    mainLayout->addWidget(selectActiveEdit,9,25,1,1);

    mainLayout->addWidget(setAlphaButton,10,25,1,1);
    mainLayout->addWidget(setAlphaLabel,11,25,1,1);
    mainLayout->addWidget(setAlphaEdit,12,25,1,1);

    mainLayout->addWidget(moveActiveUpButton,13,25,1,1);
    mainLayout->addWidget(moveActiveDownButton,14,25,1,1);
    mainLayout->addWidget(moveActiveLeftButton,15,25,1,1);
    mainLayout->addWidget(moveActiveRightButton,16,25,1,1);

    mainLayout->addWidget(layerMoveActiveDownButton,17,25,1,1);
    mainLayout->addWidget(layerMoveActiveUpButton,18,25,1,1);


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

