#ifndef INTELLIDATAMANAGER_H
#define INTELLIDATAMANAGER_H

#include <QFile>
#include <QDebug>

class PaintingArea;

namespace IntelliDatamanager {

bool loadProject(PaintingArea* Canvas, QString filePath = "unnamed.idf");
bool saveProject(PaintingArea* Canvas, QString filePath = "unnamed.idf");

}

#endif // INTELLIDATAMANAGER_H
