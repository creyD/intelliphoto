#include "IntelliDatamanager.h"
#include "Layer/PaintingArea.h"


bool IntelliDatamanager::saveProject(PaintingArea* Canvas, QString filePath){
    QFile openFile(filePath);

    if(openFile.open(QIODevice::WriteOnly)){
        qDebug() << "works.";
        openFile.write("Hahaha");
        openFile.close();
        return true;
    }

    return false;
}

bool IntelliDatamanager::loadProject(PaintingArea* Canvas, QString filePath){
    QFile openFile(filePath);

    if(openFile.open(QIODevice::ReadOnly)){
        qDebug() << openFile.readAll();
        openFile.close();
        return true;
    }

    return false;
}
