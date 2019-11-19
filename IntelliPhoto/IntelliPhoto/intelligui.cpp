#include "intelligui.h"
#include "ui_intelligui.h"
#include "LayerManager.h"

IntelliGUI::IntelliGUI(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::IntelliGUI){
    ui->setupUi(this);

    //Setting up basic IntelliPhoto structure
    this->EbenenManager = new LayerManager();

        //Test Layer
        this->EbenenManager->AddLayerAfer(0);
        this->EbenenManager->activateLayer(0);

    //Setting up basic IntelliGui Structure
    this->GUI = new QWidget();
    this->Layout = new QGridLayout(GUI);
    this->setCentralWidget(GUI);

    //setup all gui elements down here
    this->EinKnopf = new QPushButton("Ein Knopf");



    //Merge all gui elements to Layout down here
    this->Layout->addWidget(this->EinKnopf, 0,10);
    this->Layout->addWidget(this->EbenenManager->getDisplayable(),1,1,10,10);
    //this->Layout->addWidget(this->EbenenManager->getDisplayable(),0,0,10,10);
    //Layout is set in here
    this->setLayout(Layout);
}

IntelliGUI::~IntelliGUI(){
    delete ui;
    delete GUI;
    delete Layout;
    delete EbenenManager;

    //delete all Gui elements down here
}


