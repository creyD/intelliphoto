#include "GUI/IntelliPhotoGui.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    // The main application
    QApplication app(argc, argv);


    // Create and open the main window
    IntelliPhotoGui window;
    window.show();

    return app.exec();
}




