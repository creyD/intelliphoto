#include "IntelliDatamanager.h"
#include "Layer/PaintingArea.h"

bool IntelliDatamanager::saveProject(PaintingArea* Canvas, QString filePath){
    QFile openFile(filePath);

    if(openFile.open(QIODevice::WriteOnly)){
        QTextStream out(&openFile);
        std::vector<LayerObject>* layerBundle = Canvas->getLayerBundle();
        size_t numberOfLayers = layerBundle->size();

        out << "Format: idf\n" <<  "Version: 0.7\n" << endl;
        out << "Resolution: " << Canvas->getMaxWidth() << "x" << Canvas->getMaxHeight() << endl;
        out << "Layers: " << numberOfLayers << endl;
        for(size_t i = 0; i<numberOfLayers; i++){
            int width = layerBundle->at(i).width;
            int height = layerBundle->at(i).height;
            out << "width: " << width << endl;
            out << "height: " << height << endl;
            out << "xoffset: " << layerBundle->at(i).widthOffset << endl;
            out << "yoffset: " << layerBundle->at(i).heightOffset << endl;
            out << "alpha: " << layerBundle->at(i).alpha << endl;
            for(int j=0; j<height; j++){
                for(int k = 0; k<width; k++){
                       QColor pixColor = layerBundle->at(i).image->getImageData().pixelColor(j,k);
                       out << pixColor.red() << " " << pixColor.green() << " " << pixColor.blue() << " " << pixColor.alpha() << ":";
                }
                out << endl;
            }

        }
        out << "\nFormat designed and approved by IntelliPhoto Team 7. All rigths reserved.";
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
