#include "GUI/IntelliPhotoGui.h"
#include <QApplication>
#include <QDebug>
#include <vector>
#include <fstream>

int main(int argc, char*argv[]){
		// The main application
		QApplication app(argc, argv);

        std::fstream file("test.txt");
        file << "Hallo welt";
        file.close();

		// Create and open the main window
		IntelliPhotoGui window;
		window.show();

		return app.exec();
}
