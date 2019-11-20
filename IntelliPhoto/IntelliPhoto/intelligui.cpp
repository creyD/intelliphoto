#include "intelligui.h"
#include "ui_intelligui.h"
#include "LayerManager.h"

#include<QDebug>

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
    this->Red = new QLineEdit();
    this->Blue = new QLineEdit();
    this->Green = new QLineEdit();

    //Manage signals and slots in here
    QObject::connect(EinKnopf, SIGNAL(clicked()), this, SLOT(on_EinKnopf_clicked()));

    //Merge all gui elements to Layout down here
    this->Layout->addWidget(this->EinKnopf, 0,10);
    this->Layout->addWidget(this->Red, 1,10);
    this->Layout->addWidget(this->Green, 2,10);
    this->Layout->addWidget(this->Blue, 3,10);
    this->Layout->addWidget(this->EbenenManager->getDisplayable(),0,0,10,10);


    //set style here
    this->setStyleSheet("background-color:rgb(60,60,60)");
    this->EinKnopf->setStyleSheet("color:rgb(250,250,250)");
    this->Red->setStyleSheet("color:rgb(250,250,250)");
    this->Green->setStyleSheet("color:rgb(250,250,250)");
    this->Blue->setStyleSheet("color:rgb(250,250,250)");

    //Layout is set in here
    this->setLayout(Layout);
}

IntelliGUI::~IntelliGUI(){
    delete ui;
    delete GUI;
    delete Layout;
    delete EbenenManager;

    //delete all Gui elements down here
    delete EinKnopf;
    delete Red;
    delete Blue;
    delete Green;
}



void IntelliGUI::on_EinKnopf_clicked(){
    int redCol = Red->text().toInt();
    int greCol = Green->text().toInt();
    int bluCol = Blue->text().toInt();
    qDebug() << redCol << " " << greCol << " " << bluCol << '\n';
    EbenenManager->floodFillLayer(redCol, greCol, bluCol);
}
