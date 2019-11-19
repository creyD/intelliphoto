#include "intelligui.h"

#include <QApplication>
#include<QHBoxLayout>
#include<QLabel>
#include<QPushButton>
#include<QImage>
#include<QPixmap>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    IntelliGUI* win = new IntelliGUI();
    QWidget *window = new QWidget(win);
    win->setCentralWidget(window);

    QGridLayout* Layout = new QGridLayout(window);
    QPushButton* Button= new QPushButton("Button");
    QImage* Canvas = new QImage(200,200, QImage::Format::Format_ARGB32);
    QLabel* imgLabel = new QLabel("");
    imgLabel->setPixmap(QPixmap::fromImage(*Canvas));
    Layout->addWidget(imgLabel,0,0,10,10);
    Layout->addWidget(Button,10,0);
    win->show();
    return application.exec();
}
