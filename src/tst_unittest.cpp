#include <QtTest>
#include <QCoreApplication>
// add necessary includes here
#include "GUI/IntelliPhotoGui.h"
#include "Image/IntelliImage.h"
#include "Image/IntelliRasterImage.h"
#include "Image/IntelliShapedImage.h"
#include "IntelliHelper/IntelliColorPicker.h"
#include "IntelliHelper/IntelliRenderSettings.h"
#include "IntelliHelper/IntelliToolsettings.h"
#include "IntelliHelper/IntelliTriangulation.h"
#include "Layer/PaintingArea.h"
#include "Tool/IntelliTool.h"
#include "Tool/IntelliToolCircle.h"
#include "Tool/IntelliToolFloodFill.h"
#include "Tool/IntelliToolLine.h"
#include "Tool/IntelliToolPen.h"
#include "Tool/IntelliToolPlain.h"
#include "Tool/IntelliToolPolygon.h"
#include "Tool/IntelliToolRectangle.h"

class UnitTest : public QObject
{
Q_OBJECT
private:
IntelliPhotoGui* gui;
PaintingArea* area;

public:
UnitTest();
~UnitTest();

private slots:
void initTestCase();
void cleanupTestCase();
//void test_case1();

///Test  here


//test painting area
void test_addLayer();
void test_deleteLayer();
void test_setActive();
void test_setAlpha();
void test_floodFill();
void test_moveActive();
void test_setPolygon();
void test_setLayerUp();
void test_setLayerDown();

void test_createTools();

//test Raster-Image operations
void test_RasterImage_drawPixel();
void test_RasterImage_drawLine();
void test_RasterImage_drawPoint();
void test_RasterImage_getDisplayable();
void test_RasterImage_getPixelColor();
void test_RasterImage_getImageData();
void test_RasterImage_setImageData();

//test Shaped-Image operations
void test_ShapedImage_drawPixel();
void test_ShapedImage_drawLine();
void test_ShapedImage_drawPoint();
void test_ShapedImage_getDisplayable();
void test_ShapedImage_getPixelColor();
void test_ShapedImage_getImageData();
void test_ShapedImage_setImageData();

//test tools
void test_Circle_fullDraw();
void test_Circle_interruptedDraw();

void test_FloodFill_fullDraw();
void test_FloodFill_interruptedDraw();

void test_Line_fullDraw();
void test_Line_interruptedDraw();

void test_Pen_fullDraw();
void test_Pen_interruptedDraw();

void test_Plain_fullDraw();
void test_Plain_interruptedDraw();

void test_Polygon_fullDraw();
void test_Polygon_interruptedDraw();

void test_Rectangle_fullDraw();
void test_Rectangle_interruptedDraw();

//test Triangulation
void test_Triangulation_Coverage();


///Benchmark here

//bench painting area
void bench_addLayer();
void bench_deleteLayer();
void bench_setActive();
void bench_setAlpha();
void bench_floodFill();
void bench_moveActive();
void bench_setPolygon();
void bench_setLayerUp();
void bench_setLayerDown();

void bench_createTools();

//bench Raster-Image operations
void bench_RasterImage_drawPixel();
void bench_RasterImage_drawLine();
void bench_RasterImage_drawPoint();
void bench_RasterImage_getDisplayable();
void bench_RasterImage_getPixelColor();
void bench_RasterImage_getImageData();
void bench_RasterImage_setImageData();

//bench Shaped-Image operations
void bench_ShapedImage_drawPixel();
void bench_ShapedImage_drawLine();
void bench_ShapedImage_drawPoint();
void bench_ShapedImage_getDisplayable();
void bench_ShapedImage_getPixelColor();
void bench_ShapedImage_getImageData();
void bench_ShapedImage_setImageData();

//bench tools
void bench_Circle_fullDraw();
void bench_Circle_interruptedDraw();

void bench_FloodFill_fullDraw();
void bench_FloodFill_interruptedDraw();

void bench_Line_fullDraw();
void bench_Line_interruptedDraw();

void bench_Pen_fullDraw();
void bench_Pen_interruptedDraw();

void bench_Plain_fullDraw();
void bench_Plain_interruptedDraw();

void bench_Polygon_fullDraw();
void bench_Polygon_interruptedDraw();

void bench_Rectangle_fullDraw();
void bench_Rectangle_interruptedDraw();

//bench Triangulation
void bench_Triangulation_Coverage();
};

UnitTest::UnitTest()
{
		gui = new IntelliPhotoGui();
		area = gui->paintingArea;
}

UnitTest::~UnitTest()
{

}

void UnitTest::initTestCase()
{

}

void UnitTest::cleanupTestCase()
{

}

//test painting area
void UnitTest::test_addLayer(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::SHAPEDIMAGE);

		QCOMPARE(area->layerBundle.size(), 1);
		QCOMPARE(area->activeLayer, 0);

		QCOMPARE(area->layerBundle[static_cast<size_t>(area->activeLayer)].width, 200);
		QCOMPARE(area->layerBundle[static_cast<size_t>(area->activeLayer)].widthOffset, 10);

		QCOMPARE(area->layerBundle[static_cast<size_t>(area->activeLayer)].height, 200);
		QCOMPARE(area->layerBundle[static_cast<size_t>(area->activeLayer)].heightOffset, 20);

		area->deleteLayer(0);
}

void UnitTest::test_deleteLayer(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::SHAPEDIMAGE);
		area->addLayer(200,200,10,20,IntelliImage::ImageType::SHAPEDIMAGE);

		area->deleteLayer(3);
		QCOMPARE(area->layerBundle.size(), 2);
		QCOMPARE(area->activeLayer, 1);

		area->deleteLayer(-1);
		QCOMPARE(area->layerBundle.size(), 2);
		QCOMPARE(area->activeLayer, 1);

		area->deleteLayer(1);
		QCOMPARE(area->layerBundle.size(), 1);
		QCOMPARE(area->activeLayer, 0);

		area->deleteLayer(0);
		QCOMPARE(area->layerBundle.size(), 0);
		QCOMPARE(area->activeLayer, -1);

}

void UnitTest::test_setActive(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::SHAPEDIMAGE);
		area->addLayer(200,200,10,20,IntelliImage::ImageType::SHAPEDIMAGE);

		area->setLayerActive(0);
		QCOMPARE(area->activeLayer, 0);
		area->setLayerActive(1);
		QCOMPARE(area->activeLayer, 1);
		area->setLayerActive(-1);
		QCOMPARE(area->activeLayer, 1);
		area->setLayerActive(3);
		QCOMPARE(area->activeLayer, 1);

		area->deleteLayer(0);
		area->deleteLayer(0);
}

void UnitTest::test_setAlpha(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::SHAPEDIMAGE);
		area->addLayer(200,200,10,20,IntelliImage::ImageType::SHAPEDIMAGE);

		area->setLayerAlpha(0,0);
		QCOMPARE(area->layerBundle[0].alpha, 0);

		area->setLayerAlpha(0,255);
		QCOMPARE(area->layerBundle[0].alpha, 255);

		area->setLayerAlpha(1,123);
		QCOMPARE(area->layerBundle[1].alpha, 123);

		area->setLayerAlpha(1,-12);
		QCOMPARE(area->layerBundle[1].alpha, 123);

		area->setLayerAlpha(1,300);
		QCOMPARE(area->layerBundle[1].alpha, 123);

		area->deleteLayer(1);
		area->deleteLayer(0);
}

void UnitTest::test_floodFill(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::SHAPEDIMAGE);

		area->layerBundle[0].image->drawPlain(QColor(255, 255, 255, 255));
		QPoint point;
		for(size_t i = 0; i<200; i++) {
				point.setX(static_cast<int>(i));
				for(size_t j = 0; i<200; i++) {
						point.setY(static_cast<int>(j));
						QVERIFY(area->layerBundle[static_cast<size_t>(area->activeLayer)].image->getPixelColor(point)==QColor(255,255,255,255));
				}
		}

		area->layerBundle[0].image->drawPlain(QColor(0, 0, 0, 0));
		for(size_t i = 0; i<200; i++) {
				point.setX(static_cast<int>(i));
				for(size_t j = 0; i<200; i++) {
						point.setY(static_cast<int>(j));
						QVERIFY(area->layerBundle[static_cast<size_t>(area->activeLayer)].image->getPixelColor(point)==QColor(0,0,0,0));
				}
		}

		area->deleteLayer(0);
}

void UnitTest::test_moveActive(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::SHAPEDIMAGE);
		area->addLayer(200,200,10,20,IntelliImage::ImageType::SHAPEDIMAGE);

		area->layerBundle[1].image->drawPlain(QColor(0, 0, 0, 255));
		QPoint point(0,0);

		area->moveActiveLayer(-1);
		QCOMPARE(area->activeLayer, 0);
		QVERIFY(area->layerBundle[static_cast<size_t>(area->activeLayer)].image->getPixelColor(point)==QColor(0,0,0,255));

		area->moveActiveLayer(-1);
		QCOMPARE(area->activeLayer, 0);
		QVERIFY(area->layerBundle[static_cast<size_t>(area->activeLayer)].image->getPixelColor(point)==QColor(0,0,0,255));

		area->moveActiveLayer(1);
		QCOMPARE(area->activeLayer, 1);
		QVERIFY(area->layerBundle[static_cast<size_t>(area->activeLayer)].image->getPixelColor(point)==QColor(0,0,0,255));

		area->moveActiveLayer(1);
		QCOMPARE(area->activeLayer, 1);
		QVERIFY(area->layerBundle[static_cast<size_t>(area->activeLayer)].image->getPixelColor(point)==QColor(0,0,0,255));

		area->deleteLayer(1);
		area->deleteLayer(0);
}

void UnitTest::test_setPolygon(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);
		area->addLayer(200,200,10,20,IntelliImage::ImageType::SHAPEDIMAGE);

		std::vector<QPoint> polygon{
				QPoint(10,00),
				QPoint(00,10),
				QPoint(10,10),
				QPoint(00,10)
		};

		area->layerBundle[1].image->setPolygon(polygon);
		IntelliShapedImage* image = dynamic_cast<IntelliShapedImage*>(area->layerBundle[1].image);
		QCOMPARE(image->polygonData[0], polygon[0]);
		QCOMPARE(image->polygonData[1], polygon[1]);
		QCOMPARE(image->polygonData[2], polygon[2]);
		QCOMPARE(image->polygonData[3], polygon[3]);

		area->deleteLayer(1);
		area->deleteLayer(0);
}

void UnitTest::test_setLayerUp(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);
		area->addLayer(200,200,10,20,IntelliImage::ImageType::SHAPEDIMAGE);

		area->selectLayerUp();
		QCOMPARE(area->activeLayer, 1);

		area->setLayerActive(0);
		QCOMPARE(area->activeLayer, 0);

		area->selectLayerUp();
		QCOMPARE(area->activeLayer, 1);

		area->deleteLayer(1);
		area->deleteLayer(0);
}

void UnitTest::test_setLayerDown(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);
		area->addLayer(200,200,10,20,IntelliImage::ImageType::SHAPEDIMAGE);

		area->selectLayerDown();
		QCOMPARE(area->activeLayer, 0);

		area->selectLayerDown();
		QCOMPARE(area->activeLayer, 0);

		area->deleteLayer(1);
		area->deleteLayer(0);

}

void UnitTest::test_createTools(){
		QVERIFY(area->Tool == nullptr);

		area->createPenTool();
		QVERIFY(dynamic_cast<IntelliToolPen*>(area->Tool) != nullptr);

		area->createLineTool();
		QVERIFY(dynamic_cast<IntelliToolLine*>(area->Tool) != nullptr);

		area->createPlainTool();
		QVERIFY(dynamic_cast<IntelliToolPlainTool*>(area->Tool) != nullptr);

		area->createCircleTool();
		QVERIFY(dynamic_cast<IntelliToolCircle*>(area->Tool) != nullptr);

		area->createPolygonTool();
		QVERIFY(dynamic_cast<IntelliToolPolygon*>(area->Tool) != nullptr);

		area->createFloodFillTool();
		QVERIFY(dynamic_cast<IntelliToolFloodFill*>(area->Tool) != nullptr);

		area->createRectangleTool();
		QVERIFY(dynamic_cast<IntelliToolRectangle*>(area->Tool) != nullptr);
}

//test Raster-Image operations
void UnitTest::test_RasterImage_drawPixel(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);

		QPoint point(0,0);

		area->layerBundle[0].image->drawPlain(QColor(255, 255, 255, 255));
		area->layerBundle[0].image->drawPixel(point, QColor(0,0,0,255));

		QVERIFY(area->layerBundle[0].image->getPixelColor(point) == QColor(0,0,0,255));

		area->deleteLayer(0);
}

void UnitTest::test_RasterImage_drawLine(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);

		QPoint point1(0,0);
		QPoint point2(10,10);
		QPoint point3(5,5);
		QPoint point4(6,5);

		area->layerBundle[0].image->drawPlain(QColor(255, 255, 255, 255));
		area->layerBundle[0].image->drawLine(point1, point2, QColor(0,0,0,255),1);
		QVERIFY(area->layerBundle[0].image->getPixelColor(point1)==QColor(0,0,0,255));
		QVERIFY(area->layerBundle[0].image->getPixelColor(point2)==QColor(0,0,0,255));
		QVERIFY(area->layerBundle[0].image->getPixelColor(point3)==QColor(0,0,0,255));
		QVERIFY(area->layerBundle[0].image->getPixelColor(point4)==QColor(255,255,255,255));

		area->layerBundle[0].image->drawPlain(QColor(255, 255, 255, 255));
		area->layerBundle[0].image->drawLine(point1, point2, QColor(0,0,0,255),3);
		QVERIFY(area->layerBundle[0].image->getPixelColor(point1)==QColor(0,0,0,255));
		QVERIFY(area->layerBundle[0].image->getPixelColor(point2)==QColor(0,0,0,255));
		QVERIFY(area->layerBundle[0].image->getPixelColor(point3)==QColor(0,0,0,255));
		QVERIFY(area->layerBundle[0].image->getPixelColor(point4)==QColor(0,0,0,255));

		area->deleteLayer(0);
}

void UnitTest::test_RasterImage_drawPoint(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);

		QPoint point1(5,5);
		QPoint point2(5,6);

		area->layerBundle[0].image->drawPlain(QColor(255, 255, 255, 255));
		area->layerBundle[0].image->drawPoint(point1, QColor(0,0,0,255),1);
		QVERIFY(area->layerBundle[0].image->getPixelColor(point1) == QColor(0,0,0,255));
		QVERIFY(area->layerBundle[0].image->getPixelColor(point2) == QColor(255,255,255,255));


		area->layerBundle[0].image->drawPlain(QColor(255, 255, 255, 255));
		area->layerBundle[0].image->drawPoint(point1, QColor(0,0,0,255),5);
		QVERIFY(area->layerBundle[0].image->getPixelColor(point1) == QColor(0,0,0,255));
		QVERIFY(area->layerBundle[0].image->getPixelColor(point2) == QColor(0,0,0,255));

		area->deleteLayer(0);
}

void UnitTest::test_RasterImage_getDisplayable(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);

		area->layerBundle[0].image->drawPlain(QColor(255, 255, 255, 255));
		QImage img = area->layerBundle[0].image->getDisplayable(QSize(200,200),255);
		QPoint point;
		for(size_t i = 0; i<200; i++) {
				point.setX(static_cast<int>(i));
				for(size_t j = 0; j<200; j++) {
						point.setY(static_cast<int>(j));
						QVERIFY(img.pixelColor(point) == QColor(255,255,255,255));
				}
		}

		area->deleteLayer(0);
}

void UnitTest::test_RasterImage_getPixelColor(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);

		QPoint point(0,0);
		area->layerBundle[0].image->drawPlain(QColor(0, 0, 0, 255));
		QVERIFY(area->layerBundle[0].image->getPixelColor(point)==QColor(0,0,0,255));

		area->deleteLayer(0);
}

void UnitTest::test_RasterImage_getImageData(){
		area->addLayer(2,2,10,20,IntelliImage::ImageType::RASTERIMAGE);

		QImage img(2,2, QImage::Format_ARGB32);
		img.setPixelColor(0,0, Qt::red);
		img.setPixelColor(0,1, Qt::yellow);
		img.setPixelColor(1,0, Qt::blue);
		img.setPixelColor(1,1, Qt::green);

		area->layerBundle[0].image->setImageData(img);
		img = img.convertToFormat(QImage::Format_Indexed8);
		QImage cpy = area->layerBundle[0].image->getImageData();

		QPoint point1(0,0);
		QPoint point2(0,1);
		QPoint point3(1,0);
		QPoint point4(1,1);
		QVERIFY(cpy.pixelColor(point1) == img.pixelColor(point1));
		QVERIFY(cpy.pixelColor(point2) == img.pixelColor(point2));
		QVERIFY(cpy.pixelColor(point3) == img.pixelColor(point3));
		QVERIFY(cpy.pixelColor(point4) == img.pixelColor(point4));

		area->deleteLayer(0);
}

void UnitTest::test_RasterImage_setImageData(){
		area->addLayer(2,2,10,20,IntelliImage::ImageType::RASTERIMAGE);

		QImage img(2,2, QImage::Format_ARGB32);
		img.setPixelColor(0,0, Qt::red);
		img.setPixelColor(0,1, Qt::yellow);
		img.setPixelColor(1,0, Qt::blue);
		img.setPixelColor(1,1, Qt::green);

		area->layerBundle[0].image->setImageData(img);
		img = img.convertToFormat(QImage::Format_Indexed8);

		QPoint point1(0,0);
		QPoint point2(0,1);
		QPoint point3(1,0);
		QPoint point4(1,1);
		QVERIFY(area->layerBundle[0].image->getPixelColor(point1) == img.pixelColor(point1));
		QVERIFY(area->layerBundle[0].image->getPixelColor(point2) == img.pixelColor(point2));
		QVERIFY(area->layerBundle[0].image->getPixelColor(point3) == img.pixelColor(point3));
		QVERIFY(area->layerBundle[0].image->getPixelColor(point4) == img.pixelColor(point4));

		area->deleteLayer(0);
}

//test Shaped-Image operations
void UnitTest::test_ShapedImage_drawPixel(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);

		QPoint point(0,0);

		area->layerBundle[0].image->drawPlain(QColor(255, 255, 255, 255));
		area->layerBundle[0].image->drawPixel(point, QColor(0,0,0,255));

		QVERIFY(area->layerBundle[0].image->getPixelColor(point) == QColor(0,0,0,255));

		area->deleteLayer(0);
}

void UnitTest::test_ShapedImage_drawLine(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);

		QPoint point1(0,0);
		QPoint point2(10,10);
		QPoint point3(5,5);
		QPoint point4(6,5);

		area->layerBundle[0].image->drawPlain(QColor(255, 255, 255, 255));
		area->layerBundle[0].image->drawLine(point1, point2, QColor(0,0,0,255),1);
		QVERIFY(area->layerBundle[0].image->getPixelColor(point1)==QColor(0,0,0,255));
		QVERIFY(area->layerBundle[0].image->getPixelColor(point2)==QColor(0,0,0,255));
		QVERIFY(area->layerBundle[0].image->getPixelColor(point3)==QColor(0,0,0,255));
		QVERIFY(area->layerBundle[0].image->getPixelColor(point4)==QColor(255,255,255,255));

		area->layerBundle[0].image->drawPlain(QColor(255, 255, 255, 255));
		area->layerBundle[0].image->drawLine(point1, point2, QColor(0,0,0,255),3);
		QVERIFY(area->layerBundle[0].image->getPixelColor(point1)==QColor(0,0,0,255));
		QVERIFY(area->layerBundle[0].image->getPixelColor(point2)==QColor(0,0,0,255));
		QVERIFY(area->layerBundle[0].image->getPixelColor(point3)==QColor(0,0,0,255));
		QVERIFY(area->layerBundle[0].image->getPixelColor(point4)==QColor(0,0,0,255));

		area->deleteLayer(0);
}

void UnitTest::test_ShapedImage_drawPoint(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);

		QPoint point1(5,5);
		QPoint point2(5,6);

		area->layerBundle[0].image->drawPlain(QColor(255, 255, 255, 255));
		area->layerBundle[0].image->drawPoint(point1, QColor(0,0,0,255),1);
		QVERIFY(area->layerBundle[0].image->getPixelColor(point1) == QColor(0,0,0,255));
		QVERIFY(area->layerBundle[0].image->getPixelColor(point2) == QColor(255,255,255,255));


		area->layerBundle[0].image->drawPlain(QColor(255, 255, 255, 255));
		area->layerBundle[0].image->drawPoint(point1, QColor(0,0,0,255),5);
		QVERIFY(area->layerBundle[0].image->getPixelColor(point1) == QColor(0,0,0,255));
		QVERIFY(area->layerBundle[0].image->getPixelColor(point2) == QColor(0,0,0,255));

		area->deleteLayer(0);
}

void UnitTest::test_ShapedImage_getDisplayable(){
		area->addLayer(21,21,10,20,IntelliImage::ImageType::SHAPEDIMAGE);
		std::vector<QPoint> points{
				QPoint(10,00),
				QPoint(00,10),
				QPoint(10,20),
				QPoint(20,10)
		};

		std::vector<QPoint> test{
				QPoint(00,00),
				QPoint(00,20),
				QPoint(20,00),
				QPoint(20,20),
				QPoint(10,10)
		};
		area->layerBundle[0].image->drawPlain(QColor(255, 255, 255, 255));
		area->layerBundle[0].image->setPolygon(points);
		QSize size(21,21);
		QImage img = area->layerBundle[0].image->getDisplayable(size,255);

		QCOMPARE(img.pixelColor(points[0]).alpha(), 255);
		QCOMPARE(img.pixelColor(points[1]).alpha(), 255);
		QCOMPARE(img.pixelColor(points[2]).alpha(), 255);
		QCOMPARE(img.pixelColor(points[3]).alpha(), 255);

		QCOMPARE(img.pixelColor(test[4]).alpha(), 255);
		QCOMPARE(img.pixelColor(test[0]).alpha(), 0);
		QCOMPARE(img.pixelColor(test[1]).alpha(), 0);
		QCOMPARE(img.pixelColor(test[2]).alpha(), 0);
		QCOMPARE(img.pixelColor(test[3]).alpha(), 0);

		area->deleteLayer(0);
}

void UnitTest::test_ShapedImage_getPixelColor(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);

		QPoint point(0,0);
		area->layerBundle[0].image->drawPlain(QColor(0, 0, 0, 255));
		QVERIFY(area->layerBundle[0].image->getPixelColor(point)==QColor(0,0,0,255));

		area->deleteLayer(0);
}

void UnitTest::test_ShapedImage_getImageData(){
		area->addLayer(2,2,10,20,IntelliImage::ImageType::RASTERIMAGE);

		QImage img(2,2, QImage::Format_ARGB32);
		img.setPixelColor(0,0, Qt::red);
		img.setPixelColor(0,1, Qt::yellow);
		img.setPixelColor(1,0, Qt::blue);
		img.setPixelColor(1,1, Qt::green);

		area->layerBundle[0].image->setImageData(img);
		img = img.convertToFormat(QImage::Format_Indexed8);
		QImage cpy = area->layerBundle[0].image->getImageData();

		QPoint point1(0,0);
		QPoint point2(0,1);
		QPoint point3(1,0);
		QPoint point4(1,1);
		QVERIFY(cpy.pixelColor(point1) == img.pixelColor(point1));
		QVERIFY(cpy.pixelColor(point2) == img.pixelColor(point2));
		QVERIFY(cpy.pixelColor(point3) == img.pixelColor(point3));
		QVERIFY(cpy.pixelColor(point4) == img.pixelColor(point4));

		area->deleteLayer(0);
}

void UnitTest::test_ShapedImage_setImageData(){
		area->addLayer(2,2,10,20,IntelliImage::ImageType::RASTERIMAGE);

		QImage img(2,2, QImage::Format_ARGB32);
		img.setPixelColor(0,0, Qt::red);
		img.setPixelColor(0,1, Qt::yellow);
		img.setPixelColor(1,0, Qt::blue);
		img.setPixelColor(1,1, Qt::green);

		area->layerBundle[0].image->setImageData(img);
		img = img.convertToFormat(QImage::Format_Indexed8);

		QPoint point1(0,0);
		QPoint point2(0,1);
		QPoint point3(1,0);
		QPoint point4(1,1);
		QVERIFY(area->layerBundle[0].image->getPixelColor(point1) == img.pixelColor(point1));
		QVERIFY(area->layerBundle[0].image->getPixelColor(point2) == img.pixelColor(point2));
		QVERIFY(area->layerBundle[0].image->getPixelColor(point3) == img.pixelColor(point3));
		QVERIFY(area->layerBundle[0].image->getPixelColor(point4) == img.pixelColor(point4));

		area->deleteLayer(0);
}

//test tools
void UnitTest::test_Circle_fullDraw(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);
		area->colorPicker.setFirstColor(QColor(255,255,255,255));
		area->colorPicker.setSecondColor(QColor(0,0,0,255));
		area->createCircleTool();
		area->layerBundle[0].image->drawPlain(QColor(255, 0, 0, 255));

		QPoint point1(100,100);
		QPoint point2(150,100);
		area->Tool->onMouseLeftPressed(point1.x(), point1.y());
		area->Tool->onMouseMoved(point2.x(), point2.y());
		area->Tool->onMouseLeftReleased(point2.x(), point2.y());


		QVERIFY(area->layerBundle[0].image->getPixelColor(point1)==area->colorPicker.getSecondColor());
		QVERIFY(area->layerBundle[0].image->getPixelColor(point2)==area->colorPicker.getFirstColor());

		area->deleteLayer(0);
}

void UnitTest::test_Circle_interruptedDraw(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);
		area->colorPicker.setFirstColor(QColor(255,255,255,255));
		area->colorPicker.setSecondColor(QColor(0,0,0,255));
		area->createCircleTool();
		area->layerBundle[0].image->drawPlain(QColor(255, 0, 0, 255));

		QPoint point1(100,100);
		QPoint point2(150,100);
		area->Tool->onMouseLeftPressed(point1.x(), point1.y());
		area->Tool->onMouseMoved(point2.x(), point2.y());
		area->Tool->onMouseRightPressed(point2.x(), point2.y());
		area->Tool->onMouseRightReleased(point2.x(),point2.y());
		area->Tool->onMouseLeftReleased(point2.x(), point2.y());


		QVERIFY(area->layerBundle[0].image->getPixelColor(point1)==QColor(255,0,0,255));
		QVERIFY(area->layerBundle[0].image->getPixelColor(point2)==QColor(255,0,0,255));

		area->deleteLayer(0);

}


void UnitTest::test_FloodFill_fullDraw(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);
		area->colorPicker.setFirstColor(QColor(255,255,255,255));
		area->colorPicker.setSecondColor(QColor(0,0,0,255));
		area->createFloodFillTool();
		area->layerBundle[0].image->drawPlain(QColor(255, 0, 0, 255));

		QPoint point1(100,100);
		QPoint point2(150,100);
		area->Tool->onMouseLeftPressed(point1.x(), point1.y());
		area->Tool->onMouseMoved(point2.x(), point2.y());
		area->Tool->onMouseLeftReleased(point2.x(), point2.y());


		QVERIFY(area->layerBundle[0].image->getPixelColor(point1)==area->colorPicker.getFirstColor());
		QVERIFY(area->layerBundle[0].image->getPixelColor(point2)==area->colorPicker.getFirstColor());

		area->deleteLayer(0);
}

void UnitTest::test_FloodFill_interruptedDraw(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);
		area->colorPicker.setFirstColor(QColor(255,255,255,255));
		area->colorPicker.setSecondColor(QColor(0,0,0,255));
		area->createFloodFillTool();
		area->layerBundle[0].image->drawPlain(QColor(255, 0, 0, 255));

		QPoint point1(100,100);
		QPoint point2(150,100);
		area->Tool->onMouseLeftPressed(point1.x(), point1.y());
		area->Tool->onMouseMoved(point2.x(), point2.y());
		area->Tool->onMouseRightPressed(point2.x(), point2.y());
		area->Tool->onMouseRightReleased(point2.x(),point2.y());
		area->Tool->onMouseLeftReleased(point2.x(), point2.y());


		QVERIFY(area->layerBundle[0].image->getPixelColor(point1)==QColor(255,0,0,255));
		QVERIFY(area->layerBundle[0].image->getPixelColor(point2)==QColor(255,0,0,255));

		area->deleteLayer(0);
}


void UnitTest::test_Line_fullDraw(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);
		area->colorPicker.setFirstColor(QColor(255,255,255,255));
		area->colorPicker.setSecondColor(QColor(0,0,0,255));
		area->createLineTool();
		area->layerBundle[0].image->drawPlain(QColor(255, 0, 0, 255));

		QPoint point1(100,100);
		QPoint point2(150,100);
		area->Tool->onMouseLeftPressed(point1.x(), point1.y());
		area->Tool->onMouseMoved(point2.x(), point2.y());
		area->Tool->onMouseLeftReleased(point2.x(), point2.y());


		QVERIFY(area->layerBundle[0].image->getPixelColor(point1)==area->colorPicker.getFirstColor());
		QVERIFY(area->layerBundle[0].image->getPixelColor(point2)==area->colorPicker.getFirstColor());

		area->deleteLayer(0);
}

void UnitTest::test_Line_interruptedDraw(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);
		area->colorPicker.setFirstColor(QColor(255,255,255,255));
		area->colorPicker.setSecondColor(QColor(0,0,0,255));
		area->createLineTool();
		area->layerBundle[0].image->drawPlain(QColor(255, 0, 0, 255));

		QPoint point1(100,100);
		QPoint point2(150,100);
		area->Tool->onMouseLeftPressed(point1.x(), point1.y());
		area->Tool->onMouseMoved(point2.x(), point2.y());
		area->Tool->onMouseRightPressed(point2.x(), point2.y());
		area->Tool->onMouseRightReleased(point2.x(),point2.y());
		area->Tool->onMouseLeftReleased(point2.x(), point2.y());


		QVERIFY(area->layerBundle[0].image->getPixelColor(point1)==QColor(255,0,0,255));
		QVERIFY(area->layerBundle[0].image->getPixelColor(point2)==QColor(255,0,0,255));

		area->deleteLayer(0);
}

void UnitTest::test_Pen_fullDraw(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);
		area->colorPicker.setFirstColor(QColor(255,255,255,255));
		area->colorPicker.setSecondColor(QColor(0,0,0,255));
		area->createPenTool();
		area->layerBundle[0].image->drawPlain(QColor(255, 0, 0, 255));

		QPoint point1(100,100);
		QPoint point2(150,100);
		area->Tool->onMouseLeftPressed(point1.x(), point1.y());
		area->Tool->onMouseMoved(point2.x(), point2.y());
		area->Tool->onMouseLeftReleased(point2.x(), point2.y());


		QVERIFY(area->layerBundle[0].image->getPixelColor(point1)==area->colorPicker.getFirstColor());
		QVERIFY(area->layerBundle[0].image->getPixelColor(point2)==area->colorPicker.getFirstColor());

		area->deleteLayer(0);
}

void UnitTest::test_Pen_interruptedDraw(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);
		area->colorPicker.setFirstColor(QColor(255,255,255,255));
		area->colorPicker.setSecondColor(QColor(0,0,0,255));
		area->createPenTool();
		area->layerBundle[0].image->drawPlain(QColor(255, 0, 0, 255));

		QPoint point1(100,100);
		QPoint point2(150,100);
		area->Tool->onMouseLeftPressed(point1.x(), point1.y());
		area->Tool->onMouseMoved(point2.x(), point2.y());
		area->Tool->onMouseRightPressed(point2.x(), point2.y());
		area->Tool->onMouseRightReleased(point2.x(),point2.y());
		area->Tool->onMouseLeftReleased(point2.x(), point2.y());


		QVERIFY(area->layerBundle[0].image->getPixelColor(point1)==QColor(255,0,0,255));
		QVERIFY(area->layerBundle[0].image->getPixelColor(point2)==QColor(255,0,0,255));

		area->deleteLayer(0);
}

void UnitTest::test_Plain_fullDraw(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);
		area->colorPicker.setFirstColor(QColor(255,255,255,255));
		area->colorPicker.setSecondColor(QColor(0,0,0,255));
		area->createPlainTool();
		area->layerBundle[0].image->drawPlain(QColor(255, 0, 0, 255));

		QPoint point1(100,100);
		QPoint point2(150,100);
		area->Tool->onMouseLeftPressed(point1.x(), point1.y());
		area->Tool->onMouseMoved(point2.x(), point2.y());
		area->Tool->onMouseLeftReleased(point2.x(), point2.y());


		QVERIFY(area->layerBundle[0].image->getPixelColor(point1)==area->colorPicker.getFirstColor());
		QVERIFY(area->layerBundle[0].image->getPixelColor(point2)==area->colorPicker.getFirstColor());

		area->deleteLayer(0);
}

void UnitTest::test_Plain_interruptedDraw(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);
		area->colorPicker.setFirstColor(QColor(255,255,255,255));
		area->colorPicker.setSecondColor(QColor(0,0,0,255));
		area->createPlainTool();
		area->layerBundle[0].image->drawPlain(QColor(255, 0, 0, 255));

		QPoint point1(100,100);
		QPoint point2(150,100);
		area->Tool->onMouseLeftPressed(point1.x(), point1.y());
		area->Tool->onMouseMoved(point2.x(), point2.y());
		area->Tool->onMouseRightPressed(point2.x(), point2.y());
		area->Tool->onMouseRightReleased(point2.x(),point2.y());
		area->Tool->onMouseLeftReleased(point2.x(), point2.y());


		QVERIFY(area->layerBundle[0].image->getPixelColor(point1)==QColor(255,0,0,255));
		QVERIFY(area->layerBundle[0].image->getPixelColor(point2)==QColor(255,0,0,255));

		area->deleteLayer(0);
}

void UnitTest::test_Polygon_fullDraw(){
		area->addLayer(21,21,10,20,IntelliImage::ImageType::RASTERIMAGE);
		std::vector<QPoint> points{
				QPoint(10,00),
				QPoint(00,10),
				QPoint(10,20),
				QPoint(20,10)
		};

		std::vector<QPoint> test{
				QPoint(00,00),
				QPoint(00,20),
				QPoint(20,00),
				QPoint(20,20),
				QPoint(10,10)
		};

		area->colorPicker.setFirstColor(QColor(255,255,255,255));
		area->colorPicker.setSecondColor(QColor(0,0,0,255));
		area->createPolygonTool();
		area->layerBundle[0].image->drawPlain(QColor(255, 0, 0, 255));

		area->Tool->onMouseLeftPressed(points[0].x(), points[0].y());
		area->Tool->onMouseLeftReleased(points[0].x(), points[0].y());
		area->Tool->onMouseMoved(points[1].x(), points[1].y());

		area->Tool->onMouseLeftPressed(points[1].x(), points[1].y());
		area->Tool->onMouseLeftReleased(points[1].x(), points[1].y());
		area->Tool->onMouseMoved(points[2].x(), points[2].y());

		area->Tool->onMouseLeftPressed(points[2].x(), points[2].y());
		area->Tool->onMouseLeftReleased(points[2].x(), points[2].y());
		area->Tool->onMouseMoved(points[3].x(), points[3].y());

		area->Tool->onMouseLeftPressed(points[3].x(), points[3].y());
		area->Tool->onMouseLeftReleased(points[3].x(), points[3].y());
		area->Tool->onMouseMoved(points[0].x(), points[0].y());

		area->Tool->onMouseLeftPressed(points[0].x(), points[0].y());
		area->Tool->onMouseLeftReleased(points[0].x(), points[0].y());

		QVERIFY(area->layerBundle[0].image->getPixelColor(points[0])==area->colorPicker.getFirstColor());
		QVERIFY(area->layerBundle[0].image->getPixelColor(points[1])==area->colorPicker.getFirstColor());
		QVERIFY(area->layerBundle[0].image->getPixelColor(points[2])==area->colorPicker.getFirstColor());
		QVERIFY(area->layerBundle[0].image->getPixelColor(points[3])==area->colorPicker.getFirstColor());


		QVERIFY(area->layerBundle[0].image->getPixelColor(test[4])==area->colorPicker.getSecondColor());
		QVERIFY(area->layerBundle[0].image->getPixelColor(test[0])==QColor(255,0,0,255));
		QVERIFY(area->layerBundle[0].image->getPixelColor(test[1])==QColor(255,0,0,255));
		QVERIFY(area->layerBundle[0].image->getPixelColor(test[2])==QColor(255,0,0,255));
		QVERIFY(area->layerBundle[0].image->getPixelColor(test[3])==QColor(255,0,0,255));

		area->deleteLayer(0);
}


void UnitTest::test_Polygon_interruptedDraw(){
		area->addLayer(201,201,10,20,IntelliImage::ImageType::RASTERIMAGE);
		std::vector<QPoint> points{
				QPoint(100,000),
				QPoint(000,100),
				QPoint(100,200),
				QPoint(200,100)
		};

		std::vector<QPoint> test{
				QPoint(000,000),
				QPoint(000,200),
				QPoint(200,000),
				QPoint(200,200),
				QPoint(100,100)
		};

		area->colorPicker.setFirstColor(QColor(255,255,255,255));
		area->colorPicker.setSecondColor(QColor(0,0,0,255));
		area->createPolygonTool();
		area->layerBundle[0].image->drawPlain(QColor(255, 0, 0, 255));

		area->Tool->onMouseLeftPressed(points[0].x(), points[0].y());
		area->Tool->onMouseLeftReleased(points[0].x(), points[0].y());
		area->Tool->onMouseMoved(points[1].x(), points[1].y());

		area->Tool->onMouseLeftPressed(points[1].x(), points[1].y());
		area->Tool->onMouseLeftReleased(points[1].x(), points[1].y());
		area->Tool->onMouseMoved(points[2].x(), points[2].y());

		area->Tool->onMouseLeftPressed(points[2].x(), points[2].y());
		area->Tool->onMouseLeftReleased(points[2].x(), points[2].y());
		area->Tool->onMouseMoved(points[3].x(), points[3].y());

		area->Tool->onMouseLeftPressed(points[3].x(), points[3].y());
		area->Tool->onMouseLeftReleased(points[3].x(), points[3].y());

		area->Tool->onMouseRightPressed(points[0].x(), points[0].y());
		area->Tool->onMouseRightReleased(points[0].x(), points[0].y());


		QVERIFY(area->layerBundle[0].image->getPixelColor(points[0])==QColor(255,0,0,255));
		QVERIFY(area->layerBundle[0].image->getPixelColor(points[1])==QColor(255,0,0,255));
		QVERIFY(area->layerBundle[0].image->getPixelColor(points[2])==QColor(255,0,0,255));
		QVERIFY(area->layerBundle[0].image->getPixelColor(points[3])==QColor(255,0,0,255));

		QVERIFY(area->layerBundle[0].image->getPixelColor(test[4])==QColor(255,0,0,255));
		QVERIFY(area->layerBundle[0].image->getPixelColor(test[0])==QColor(255,0,0,255));
		QVERIFY(area->layerBundle[0].image->getPixelColor(test[1])==QColor(255,0,0,255));
		QVERIFY(area->layerBundle[0].image->getPixelColor(test[2])==QColor(255,0,0,255));
		QVERIFY(area->layerBundle[0].image->getPixelColor(test[3])==QColor(255,0,0,255));

		area->deleteLayer(0);
}


void UnitTest::test_Rectangle_fullDraw(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);
		area->colorPicker.setFirstColor(QColor(255,255,255,255));
		area->colorPicker.setSecondColor(QColor(0,0,0,255));
		area->createRectangleTool();
		area->layerBundle[0].image->drawPlain(QColor(255, 0, 0, 255));

		QPoint point1(100,100);
		QPoint point2(150,150);
		QPoint point3(125,125);
		area->Tool->onMouseLeftPressed(point1.x(), point1.y());
		area->Tool->onMouseMoved(point2.x(), point2.y());
		area->Tool->onMouseLeftReleased(point2.x(), point2.y());


		QVERIFY(area->layerBundle[0].image->getPixelColor(point1)==area->colorPicker.getFirstColor());
		QVERIFY(area->layerBundle[0].image->getPixelColor(point2)==area->colorPicker.getFirstColor());
		QVERIFY(area->layerBundle[0].image->getPixelColor(point3)==area->colorPicker.getSecondColor());

		area->deleteLayer(0);
}

void UnitTest::test_Rectangle_interruptedDraw(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);
		area->colorPicker.setFirstColor(QColor(255,255,255,255));
		area->colorPicker.setSecondColor(QColor(0,0,0,255));
		area->createRectangleTool();
		area->layerBundle[0].image->drawPlain(QColor(255, 0, 0, 255));

		QPoint point1(100,100);
		QPoint point2(150,150);
		QPoint point3(125,125);
		area->Tool->onMouseLeftPressed(point1.x(), point1.y());
		area->Tool->onMouseMoved(point2.x(), point2.y());
		area->Tool->onMouseRightPressed(point2.x(), point2.y());
		area->Tool->onMouseRightReleased(point2.x(),point2.y());
		area->Tool->onMouseLeftReleased(point2.x(), point2.y());

		QVERIFY(area->layerBundle[0].image->getPixelColor(point1)==QColor(255,0,0,255));
		QVERIFY(area->layerBundle[0].image->getPixelColor(point2)==QColor(255,0,0,255));
		QVERIFY(area->layerBundle[0].image->getPixelColor(point3)==QColor(255,0,0,255));

		area->deleteLayer(0);
}


//test Triangulation
void UnitTest::test_Triangulation_Coverage(){
		std::vector<QPoint> points{
				QPoint(10,00),
				QPoint(00,10),
				QPoint(10,20),
				QPoint(20,10)
		};
		std::vector<QPoint> test{
				QPoint(00,00),
				QPoint(00,20),
				QPoint(20,00),
				QPoint(20,20),
				QPoint(10,10)
		};
		std::vector<Triangle> tria = IntelliTriangulation::calculateTriangles(points);
		QCOMPARE(IntelliTriangulation::isInPolygon(tria, points[0]), true);
		QCOMPARE(IntelliTriangulation::isInPolygon(tria, points[1]), true);
		QCOMPARE(IntelliTriangulation::isInPolygon(tria, points[2]), true);
		QCOMPARE(IntelliTriangulation::isInPolygon(tria, points[3]), true);

		QCOMPARE(IntelliTriangulation::isInPolygon(tria, test[4]), true);
		QCOMPARE(IntelliTriangulation::isInPolygon(tria, test[0]), false);
		QCOMPARE(IntelliTriangulation::isInPolygon(tria, test[1]), false);
		QCOMPARE(IntelliTriangulation::isInPolygon(tria, test[2]), false);
		QCOMPARE(IntelliTriangulation::isInPolygon(tria, test[3]), false);
}


///Benchmarks here

void UnitTest::bench_addLayer(){
		QBENCHMARK{
				area->addLayer(200,200,0,0,IntelliImage::ImageType::RASTERIMAGE);
		}
		area->deleteLayer(0);
}

void UnitTest::bench_deleteLayer(){
		area->addLayer(200,200,0,0,IntelliImage::ImageType::RASTERIMAGE);
		QBENCHMARK{
				area->deleteLayer(0);
		}
}

void UnitTest::bench_setActive(){
		area->addLayer(200,200,0,0,IntelliImage::ImageType::RASTERIMAGE);
		area->addLayer(200,200,0,0,IntelliImage::ImageType::RASTERIMAGE);

		QBENCHMARK{
				area->setLayerActive(0);
		}

		area->deleteLayer(1);
		area->deleteLayer(0);
}

void UnitTest::bench_setAlpha(){
		area->addLayer(200,200,0,0,IntelliImage::ImageType::RASTERIMAGE);

		QBENCHMARK{
				area->setLayerAlpha(0,0);
		}

		area->deleteLayer(0);
}

void UnitTest::bench_floodFill(){
		area->addLayer(200,200,0,0,IntelliImage::ImageType::RASTERIMAGE);

		QBENCHMARK{
				area->layerBundle[0].image->drawPlain(QColor(255, 255, 255, 255));
		}

		area->deleteLayer(0);
}

void UnitTest::bench_moveActive(){
		area->addLayer(200,200,0,0,IntelliImage::ImageType::RASTERIMAGE);
		area->addLayer(200,200,0,0,IntelliImage::ImageType::RASTERIMAGE);

		area->setLayerActive(0);
		QBENCHMARK{
				area->moveActiveLayer(1);
		}

		area->deleteLayer(1);
		area->deleteLayer(0);
}

void UnitTest::bench_setPolygon(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::SHAPEDIMAGE);

		std::vector<QPoint> polygon{
				QPoint(10,00),
				QPoint(00,10),
				QPoint(10,10),
				QPoint(00,10)
		};

		QBENCHMARK{
				area->layerBundle[0].image->setPolygon(polygon);
		}

		area->deleteLayer(0);
}

void UnitTest::bench_setLayerUp(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);

		area->setLayerActive(0);
		QBENCHMARK{
				area->selectLayerUp();
		}

		area->deleteLayer(1);
		area->deleteLayer(0);
}

void UnitTest::bench_setLayerDown(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);

		QBENCHMARK{
				area->selectLayerDown();
		}

		area->deleteLayer(1);
		area->deleteLayer(0);
}

void UnitTest::bench_createTools(){
		QBENCHMARK{
				area->createPenTool();
		}

		QBENCHMARK{
				area->createLineTool();
		}

		QBENCHMARK{
				area->createPlainTool();
		}

		QBENCHMARK{
				area->createCircleTool();
		}

		QBENCHMARK{
				area->createPolygonTool();
		}

		QBENCHMARK{
				area->createFloodFillTool();
		}

		QBENCHMARK{
				area->createRectangleTool();
		}
}

void UnitTest::bench_RasterImage_drawPixel(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);

		QPoint point(0,0);

		QBENCHMARK{
				area->layerBundle[0].image->drawPixel(point, QColor(0,0,0,255));
		}

		area->deleteLayer(0);
}

void UnitTest::bench_RasterImage_drawLine(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);

		QPoint point1(000,000);
		QPoint point2(200,200);

		QBENCHMARK{
				area->layerBundle[0].image->drawLine(point1, point2, QColor(0,0,0,255), 1);
		}

		area->deleteLayer(0);
}

void UnitTest::bench_RasterImage_drawPoint(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);

		QPoint point(000,000);

		QBENCHMARK{
				area->layerBundle[0].image->drawPoint(point, QColor(0,0,0,255), 1);
		}

		area->deleteLayer(0);
}

void UnitTest::bench_RasterImage_getDisplayable(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);

		QBENCHMARK{
				area->layerBundle[0].image->getDisplayable(QSize(200,200),255);
		}

		area->deleteLayer(0);
}

void UnitTest::bench_RasterImage_getPixelColor(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);

		QPoint point(000,000);

		QBENCHMARK{
				area->layerBundle[0].image->getPixelColor(point);
		}

		area->deleteLayer(0);
}

void UnitTest::bench_RasterImage_getImageData(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);

		QBENCHMARK{
				area->layerBundle[0].image->getImageData();
		}

		area->deleteLayer(0);
}

void UnitTest::bench_RasterImage_setImageData(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);

		QImage img = area->layerBundle[0].image->getImageData();
		QBENCHMARK{
				area->layerBundle[0].image->setImageData(img);
		}

		area->deleteLayer(0);
}

void UnitTest::bench_ShapedImage_drawPixel(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::SHAPEDIMAGE);

		QPoint point(0,0);

		QBENCHMARK{
				area->layerBundle[0].image->drawPixel(point, QColor(0,0,0,255));
		}

		area->deleteLayer(0);
}

void UnitTest::bench_ShapedImage_drawLine(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::SHAPEDIMAGE);

		QPoint point1(000,000);
		QPoint point2(200,200);

		QBENCHMARK{
				area->layerBundle[0].image->drawLine(point1, point2, QColor(0,0,0,255), 1);
		}

		area->deleteLayer(0);
}

void UnitTest::bench_ShapedImage_drawPoint(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::SHAPEDIMAGE);

		QPoint point(000,000);

		QBENCHMARK{
				area->layerBundle[0].image->drawPoint(point, QColor(0,0,0,255), 1);
		}

		area->deleteLayer(0);
}

void UnitTest::bench_ShapedImage_getDisplayable(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::SHAPEDIMAGE);

		QBENCHMARK{
				area->layerBundle[0].image->getDisplayable(QSize(200,200),255);
		}

		area->deleteLayer(0);
}

void UnitTest::bench_ShapedImage_getPixelColor(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::SHAPEDIMAGE);

		QPoint point(000,000);

		QBENCHMARK{
				area->layerBundle[0].image->getPixelColor(point);
		}

		area->deleteLayer(0);
}

void UnitTest::bench_ShapedImage_getImageData(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::SHAPEDIMAGE);

		QBENCHMARK{
				area->layerBundle[0].image->getImageData();
		}

		area->deleteLayer(0);
}

void UnitTest::bench_ShapedImage_setImageData(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::SHAPEDIMAGE);

		QImage img = area->layerBundle[0].image->getImageData();
		QBENCHMARK{
				area->layerBundle[0].image->setImageData(img);
		}

		area->deleteLayer(0);
}

void UnitTest::bench_Circle_fullDraw(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);
		area->colorPicker.setFirstColor(QColor(255,255,255,255));
		area->colorPicker.setSecondColor(QColor(0,0,0,255));
		area->createCircleTool();
		area->layerBundle[0].image->drawPlain(QColor(255, 0, 0, 255));

		QPoint point1(100,100);
		QPoint point2(150,100);
		QBENCHMARK{
				area->Tool->onMouseLeftPressed(point1.x(), point1.y());
				area->Tool->onMouseMoved(point2.x(), point2.y());
				area->Tool->onMouseLeftReleased(point2.x(), point2.y());
		}

		area->deleteLayer(0);
}

void UnitTest::bench_Circle_interruptedDraw(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);
		area->colorPicker.setFirstColor(QColor(255,255,255,255));
		area->colorPicker.setSecondColor(QColor(0,0,0,255));
		area->createCircleTool();
		area->layerBundle[0].image->drawPlain(QColor(255, 0, 0, 255));

		QPoint point1(100,100);
		QPoint point2(150,100);
		QBENCHMARK{
				area->Tool->onMouseLeftPressed(point1.x(), point1.y());
				area->Tool->onMouseMoved(point2.x(), point2.y());
				area->Tool->onMouseRightPressed(point2.x(), point2.y());
				area->Tool->onMouseRightReleased(point2.x(),point2.y());
				area->Tool->onMouseLeftReleased(point2.x(), point2.y());
		}

		area->deleteLayer(0);
}


void UnitTest::bench_FloodFill_fullDraw(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);
		area->colorPicker.setFirstColor(QColor(255,255,255,255));
		area->colorPicker.setSecondColor(QColor(0,0,0,255));
		area->createFloodFillTool();
		area->layerBundle[0].image->drawPlain(QColor(255, 0, 0, 255));

		QPoint point1(100,100);
		QPoint point2(150,100);
		QBENCHMARK{
				area->Tool->onMouseLeftPressed(point1.x(), point1.y());
				area->Tool->onMouseMoved(point2.x(), point2.y());
				area->Tool->onMouseLeftReleased(point2.x(), point2.y());
		}

		area->deleteLayer(0);
}

void UnitTest::bench_FloodFill_interruptedDraw(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);
		area->colorPicker.setFirstColor(QColor(255,255,255,255));
		area->colorPicker.setSecondColor(QColor(0,0,0,255));
		area->createFloodFillTool();
		area->layerBundle[0].image->drawPlain(QColor(255, 0, 0, 255));

		QPoint point1(100,100);
		QPoint point2(150,100);
		QBENCHMARK{
				area->Tool->onMouseLeftPressed(point1.x(), point1.y());
				area->Tool->onMouseMoved(point2.x(), point2.y());
				area->Tool->onMouseRightPressed(point2.x(), point2.y());
				area->Tool->onMouseRightReleased(point2.x(),point2.y());
				area->Tool->onMouseLeftReleased(point2.x(), point2.y());
		}

		area->deleteLayer(0);
}


void UnitTest::bench_Line_fullDraw(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);
		area->colorPicker.setFirstColor(QColor(255,255,255,255));
		area->colorPicker.setSecondColor(QColor(0,0,0,255));
		area->createLineTool();
		area->layerBundle[0].image->drawPlain(QColor(255, 0, 0, 255));

		QPoint point1(100,100);
		QPoint point2(150,100);
		QBENCHMARK{
				area->Tool->onMouseLeftPressed(point1.x(), point1.y());
				area->Tool->onMouseMoved(point2.x(), point2.y());
				area->Tool->onMouseLeftReleased(point2.x(), point2.y());
		}

		area->deleteLayer(0);
}

void UnitTest::bench_Line_interruptedDraw(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);
		area->colorPicker.setFirstColor(QColor(255,255,255,255));
		area->colorPicker.setSecondColor(QColor(0,0,0,255));
		area->createLineTool();
		area->layerBundle[0].image->drawPlain(QColor(255, 0, 0, 255));

		QPoint point1(100,100);
		QPoint point2(150,100);

		QBENCHMARK{
				area->Tool->onMouseLeftPressed(point1.x(), point1.y());
				area->Tool->onMouseMoved(point2.x(), point2.y());
				area->Tool->onMouseRightPressed(point2.x(), point2.y());
				area->Tool->onMouseRightReleased(point2.x(),point2.y());
				area->Tool->onMouseLeftReleased(point2.x(), point2.y());
		}

		area->deleteLayer(0);
}

void UnitTest::bench_Pen_fullDraw(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);
		area->colorPicker.setFirstColor(QColor(255,255,255,255));
		area->colorPicker.setSecondColor(QColor(0,0,0,255));
		area->createPenTool();
		area->layerBundle[0].image->drawPlain(QColor(255, 0, 0, 255));

		QPoint point1(100,100);
		QPoint point2(150,100);
		QBENCHMARK{
				area->Tool->onMouseLeftPressed(point1.x(), point1.y());
				area->Tool->onMouseMoved(point2.x(), point2.y());
				area->Tool->onMouseLeftReleased(point2.x(), point2.y());
		}

		area->deleteLayer(0);
}

void UnitTest::bench_Pen_interruptedDraw(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);
		area->colorPicker.setFirstColor(QColor(255,255,255,255));
		area->colorPicker.setSecondColor(QColor(0,0,0,255));
		area->createPenTool();
		area->layerBundle[0].image->drawPlain(QColor(255, 0, 0, 255));

		QPoint point1(100,100);
		QPoint point2(150,100);
		QBENCHMARK{
				area->Tool->onMouseLeftPressed(point1.x(), point1.y());
				area->Tool->onMouseMoved(point2.x(), point2.y());
				area->Tool->onMouseRightPressed(point2.x(), point2.y());
				area->Tool->onMouseRightReleased(point2.x(),point2.y());
				area->Tool->onMouseLeftReleased(point2.x(), point2.y());
		}

		area->deleteLayer(0);
}

void UnitTest::bench_Plain_fullDraw(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);
		area->colorPicker.setFirstColor(QColor(255,255,255,255));
		area->colorPicker.setSecondColor(QColor(0,0,0,255));
		area->createPlainTool();
		area->layerBundle[0].image->drawPlain(QColor(255, 0, 0, 255));

		QPoint point1(100,100);
		QPoint point2(150,100);
		QBENCHMARK{
				area->Tool->onMouseLeftPressed(point1.x(), point1.y());
				area->Tool->onMouseMoved(point2.x(), point2.y());
				area->Tool->onMouseLeftReleased(point2.x(), point2.y());
		}

		area->deleteLayer(0);
}

void UnitTest::bench_Plain_interruptedDraw(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);
		area->colorPicker.setFirstColor(QColor(255,255,255,255));
		area->colorPicker.setSecondColor(QColor(0,0,0,255));
		area->createPlainTool();
		area->layerBundle[0].image->drawPlain(QColor(255, 0, 0, 255));

		QPoint point1(100,100);
		QPoint point2(150,100);
		QBENCHMARK{
				area->Tool->onMouseLeftPressed(point1.x(), point1.y());
				area->Tool->onMouseMoved(point2.x(), point2.y());
				area->Tool->onMouseRightPressed(point2.x(), point2.y());
				area->Tool->onMouseRightReleased(point2.x(),point2.y());
				area->Tool->onMouseLeftReleased(point2.x(), point2.y());
		}

		area->deleteLayer(0);
}

void UnitTest::bench_Polygon_fullDraw(){
		area->addLayer(21,21,10,20,IntelliImage::ImageType::RASTERIMAGE);
		std::vector<QPoint> points{
				QPoint(10,00),
				QPoint(00,10),
				QPoint(10,20),
				QPoint(20,10)
		};

		area->colorPicker.setFirstColor(QColor(255,255,255,255));
		area->colorPicker.setSecondColor(QColor(0,0,0,255));
		area->createPolygonTool();
		area->layerBundle[0].image->drawPlain(QColor(255, 0, 0, 255));

		QBENCHMARK{
				area->Tool->onMouseLeftPressed(points[0].x(), points[0].y());
				area->Tool->onMouseLeftReleased(points[0].x(), points[0].y());
				area->Tool->onMouseMoved(points[1].x(), points[1].y());

				area->Tool->onMouseLeftPressed(points[1].x(), points[1].y());
				area->Tool->onMouseLeftReleased(points[1].x(), points[1].y());
				area->Tool->onMouseMoved(points[2].x(), points[2].y());

				area->Tool->onMouseLeftPressed(points[2].x(), points[2].y());
				area->Tool->onMouseLeftReleased(points[2].x(), points[2].y());
				area->Tool->onMouseMoved(points[3].x(), points[3].y());

				area->Tool->onMouseLeftPressed(points[3].x(), points[3].y());
				area->Tool->onMouseLeftReleased(points[3].x(), points[3].y());
				area->Tool->onMouseMoved(points[0].x(), points[0].y());

				area->Tool->onMouseLeftPressed(points[0].x(), points[0].y());
				area->Tool->onMouseLeftReleased(points[0].x(), points[0].y());
		}

		area->deleteLayer(0);
}


void UnitTest::bench_Polygon_interruptedDraw(){
		area->addLayer(201,201,10,20,IntelliImage::ImageType::RASTERIMAGE);
		std::vector<QPoint> points{
				QPoint(100,000)
		};


		area->colorPicker.setFirstColor(QColor(255,255,255,255));
		area->colorPicker.setSecondColor(QColor(0,0,0,255));
		area->createPolygonTool();
		area->layerBundle[0].image->drawPlain(QColor(255, 0, 0, 255));

		QBENCHMARK{
				area->Tool->onMouseLeftPressed(points[0].x(), points[0].y());
				area->Tool->onMouseLeftReleased(points[0].x(), points[0].y());

				area->Tool->onMouseRightPressed(points[0].x(), points[0].y());
				area->Tool->onMouseRightReleased(points[0].x(), points[0].y());
		}

		area->deleteLayer(0);
}


void UnitTest::bench_Rectangle_fullDraw(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);
		area->colorPicker.setFirstColor(QColor(255,255,255,255));
		area->colorPicker.setSecondColor(QColor(0,0,0,255));
		area->createRectangleTool();
		area->layerBundle[0].image->drawPlain(QColor(255, 0, 0, 255));

		QPoint point1(100,100);
		QPoint point2(150,150);

		QBENCHMARK{
				area->Tool->onMouseLeftPressed(point1.x(), point1.y());
				area->Tool->onMouseMoved(point2.x(), point2.y());
				area->Tool->onMouseLeftReleased(point2.x(), point2.y());
		}

		area->deleteLayer(0);
}

void UnitTest::bench_Rectangle_interruptedDraw(){
		area->addLayer(200,200,10,20,IntelliImage::ImageType::RASTERIMAGE);
		area->colorPicker.setFirstColor(QColor(255,255,255,255));
		area->colorPicker.setSecondColor(QColor(0,0,0,255));
		area->createRectangleTool();
		area->layerBundle[0].image->drawPlain(QColor(255, 0, 0, 255));

		QPoint point1(100,100);
		QPoint point2(150,150);
		QBENCHMARK{
				area->Tool->onMouseLeftPressed(point1.x(), point1.y());
				area->Tool->onMouseMoved(point2.x(), point2.y());
				area->Tool->onMouseRightPressed(point2.x(), point2.y());
				area->Tool->onMouseRightReleased(point2.x(),point2.y());
				area->Tool->onMouseLeftReleased(point2.x(), point2.y());
		}

		area->deleteLayer(0);
}


void UnitTest::bench_Triangulation_Coverage(){
		std::vector<QPoint> points{
				QPoint(10,00),
				QPoint(00,10),
				QPoint(10,20),
				QPoint(20,10)
		};
		std::vector<QPoint> test{
				QPoint(00,00),
				QPoint(00,20),
				QPoint(20,00),
				QPoint(20,20),
				QPoint(10,10)
		};

		QBENCHMARK{
				std::vector<Triangle> tria = IntelliTriangulation::calculateTriangles(points);
				QPoint point;
				for(int i = 0; i<200; i++) {
						point.setX(i);
						for(int j = 0; j<200; j++) {
								point.setY(j);
								IntelliTriangulation::isInPolygon(tria, point);
						}
				}
		}
}


QTEST_MAIN(UnitTest)

#include "tst_unittest.moc"
