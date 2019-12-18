#include "GUI/IntelliPhotoGui.h"
#include <QApplication>
#include <QDebug>
#include "IntelliHelper/IntelliHelper.h"
#include<vector>

int main(int argc, char *argv[]){
    // The main application
    QApplication app(argc, argv);

    //some nice ass looking comment
    // Create and open the main window
    IntelliPhotoGui window;
    window.show();

    return app.exec();
}
