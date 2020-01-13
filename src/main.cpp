#include "GUI/IntelliPhotoGui.h"
#include "GUI/IntelliInputDialog.h"
#include <QApplication>
#include <QDebug>
#include <vector>

int main(int argc, char*argv[]){
		// The main application
		QApplication app(argc, argv);

		IntelliInputDialog* InputDialog;

		// Create and open the main window
		IntelliPhotoGui window(InputDialog);
		window.show();

		return app.exec();
}
