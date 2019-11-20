#include<QDebug>

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
    win->show();
    return application.exec();
}
