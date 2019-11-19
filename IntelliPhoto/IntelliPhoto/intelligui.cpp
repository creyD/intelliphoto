#include "intelligui.h"
#include "ui_intelligui.h"
#include<QDebug>
#include<QGridLayout>
#include<QLabel>
#include<QColor>

IntelliGUI::IntelliGUI(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::IntelliGUI){
    ui->setupUi(this);
}

IntelliGUI::~IntelliGUI(){
    delete ui;
}

void IntelliGUI::setColor(double R, double G, double B){
    R *= 255;
    G *= 255;
    B *= 255;
    QString color = "rgb(";
    color += QString::number(R)+ ",";
    color += QString::number(G)+ ",";
    color += QString::number(B)+ ")";
    this->setStyleSheet("background-color:"+color);
}

void IntelliGUI::setColor(int R, int G, int B){
    QString color = "rgb(";
    color += QString::number(R)+ ",";
    color += QString::number(G)+ ",";
    color += QString::number(B)+ ")";
    this->setStyleSheet("background-color:"+color);
}

