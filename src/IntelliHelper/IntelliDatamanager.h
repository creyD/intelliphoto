#ifndef INTELLIDATAMANAGER_H
#define INTELLIDATAMANAGER_H

#include "Layer/PaintingArea.h"
#include <QFile>

class IntelliDatamanager
{
private:

public:
    void loadProject(PaintingArea* Canvas, QString filePath = "unnamed.idf");
    void saveProject(PaintingArea* Canvas, QString filePath = "unnamed.idf");
    IntelliDatamanager();
};

#endif // INTELLIDATAMANAGER_H
