	#ifndef INTELLIDATAMANAGER_H
#define INTELLIDATAMANAGER_H

#include <QFile>
#include <QDebug>

class PaintingArea;

namespace IntelliDatamanager {

/*!
 * \brief loadProject loads a project from a file, closes current project.
 * \param Canvas    - Reference to the used Canvas.
 * \param filePath  - Filepath to the project which should be opened.
 * \return True if everything worked, false otherwise.
 */
bool loadProject(PaintingArea* Canvas, QString filePath = "unnamed.idf");

/*!
 * \brief saveProject saves the current project to a file.
 * \param Canvas    - Reference to the used Canvas.
 * \param filePath  - Filepath to the project which should be saved.
 * \return True if everything worked, false otherwise.
 */
bool saveProject(PaintingArea* Canvas, QString filePath = "unnamed.idf");

}

#endif // INTELLIDATAMANAGER_H
