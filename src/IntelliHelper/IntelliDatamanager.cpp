#include "IntelliDatamanager.h"
#include "Layer/PaintingArea.h"

bool IntelliDatamanager::saveProject(PaintingArea* Canvas, QString filePath){
		QFile openFile(filePath);

		if(openFile.open(QIODevice::WriteOnly)) {

				QTextStream out(&openFile);
				std::vector<LayerObject>* layerBundle = Canvas->getLayerBundle();
				size_t numberOfLayers = layerBundle->size();
				out << 7 << endl;                                                        //version tag
				out << Canvas->getRenderSettings() << " ";
				out << Canvas->getMaxWidth() << " " << Canvas->getMaxHeight() << endl;  //dimensions of canvas
				out << numberOfLayers << endl;                                          //number of layers
				for(size_t i = 0; i<numberOfLayers; i++) {
						int width = layerBundle->at(i).width;
						int height = layerBundle->at(i).height;
						out << width << endl;                                           //width
						out << height << endl;                                          //height
						out << layerBundle->at(i).widthOffset << endl;                  //widthOffset
						out << layerBundle->at(i).heightOffset << endl;                 //HeightOffset
						out << layerBundle->at(i).alpha << endl;                        //alpha of layer
						if(layerBundle->at(i).image->getTypeOfImage() == ImageType::RASTERIMAGE) {
								out << 0 << " ";
						}else{
								out << 1 << " ";
						}
						std::vector<QPoint> points = layerBundle->at(i).image->getPolygonData();
						out << points.size() << " ";
						for(size_t j = 0; j<points.size(); j++) {
								out << points.at(j).x() << " " << points.at(j).y() << " ";
						}
						for(int j = 0; j<height; j++) {
								for(int k = 0; k<width; k++) {
										QColor pixColor = layerBundle->at(i).image->getImageData().pixelColor(j,k);
										out << pixColor.red() << " " << pixColor.green() << " " << pixColor.blue() << " " << pixColor.alpha() << " ";
								}
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
		Canvas->deleteAllLayers();
		if(openFile.open(QIODevice::ReadOnly)) {
				QTextStream in(&openFile);

				float version;
				int rendersetting;
				int widthCanvas, heightCanvas, numberOffLayers;
				in >> version;
				in >> rendersetting;
				in >> widthCanvas >> heightCanvas;
				in >> numberOffLayers;

				Canvas->setLayerDimensions(widthCanvas, heightCanvas);
				for(int i = 0; i<numberOffLayers; i++) {
						int width, height, widthOffset, heightOffset, alpha;
						in >> width >> height >> widthOffset >> heightOffset >> alpha;

						int typeFlag;
						size_t numberOfPoints;
						std::vector<QPoint> polyPoints;

						in >> typeFlag >> numberOfPoints;
						if(typeFlag==0) {
								Canvas->addLayer(width, height, widthOffset, heightOffset, alpha, ImageType::RASTERIMAGE);
						}else{
								Canvas->addLayer(width, height, widthOffset, heightOffset, alpha, ImageType::SHAPEDIMAGE);
						}
						polyPoints.reserve(numberOfPoints);
						for(size_t j = 0; j<numberOfPoints; j++) {
								int x, y;
								in >> x >> y;
								polyPoints.push_back(QPoint(x,y));
						}
						Canvas->setPolygonDataToActive(polyPoints);

						for(int j = 0; j<height; j++) {
								for(int k = 0; k<width; k++) {
										int red, green, blue, alpha;
										in >> red >> green >> blue >> alpha;
										Canvas->setPixelToActive(QColor(red, green, blue, alpha), QPoint(j, k));
								}
						}
				}
				Canvas->setRenderSettings(static_cast<bool>(rendersetting));
				openFile.close();
				return true;
		}

		return false;
}
