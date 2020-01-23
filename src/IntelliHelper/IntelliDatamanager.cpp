#include "IntelliDatamanager.h"
#include "Layer/PaintingArea.h"

bool IntelliDatamanager::saveProject(PaintingArea* Canvas, QString filePath){
    QFile openFile(filePath);

    if(openFile.open(QIODevice::WriteOnly)){
        QTextStream out(&openFile);

        out << "Format: idf\n" <<  "Version: 0.7\n" << endl;
        out << "Resolution: " << Canvas->getMaxWidth() << "x" << Canvas->getMaxHeight() << endl;
        out << "Layers: " << "0" << endl;
        if(false){
            out << "width: " << endl;
            out << "height: " << endl;
            out << "xoffset: " << endl;
            out << "yoffset: " << endl;
            out << "alpha: " << endl;
            out << "imageData: " << endl;
        }

        openFile.close();
        return true;
    }

    return false;
}

bool IntelliDatamanager::loadProject(PaintingArea* Canvas, QString filePath){
    QFile openFile(filePath);

    if(openFile.open(QIODevice::ReadOnly)){
        qDebug() << openFile.readLine();
        openFile.close();
        return true;
    }

    return false;
}
