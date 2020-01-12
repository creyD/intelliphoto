#include <QtTest> 
// add necessary includes here
#include<string>

#include "GUI/IntelliPhotoGui.h"


class UnitTest : public QObject
{
    Q_OBJECT
private:
    IntelliPhotoGui* gui;
    PaintingArea* area;
    QApplication* app;

public:
    UnitTest();
    ~UnitTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

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
    void test_RasterImage_setPolygon();
    void test_RasterImage_loadImage();
    void test_RasterImage_getPixelColor();
    void test_RasterImage_getImageData();
    void test_RasterImage_setImageData();

    //test Shaped-Image operations
    void test_ShapedImage_drawPixel();
    void test_ShapedImage_drawLine();
    void test_ShapedImage_drawPoint();
    void test_ShapedImage_getDisplayable();
    void test_ShapedImage_setPolygon();
    void test_ShapedImage_loadImage();
    void test_ShapedImage_getPixelColor();
    void test_ShapedImage_getImageData();
    void test_ShapedImage_setImageData();

    //test painting-area tools
    void test_createTool_Circle();
    void test_createTool_FloodFill();
    void test_createTool_Line();
    void test_createTool_Pen();
    void test_createTool_Plain();
    void test_createTool_Polygon();
    void test_createTool_Rectangle();

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
};

UnitTest::UnitTest()
{
    char arg0[] = "programName";
    char arg1[] = "arg1";
    char arg2[] = "arg2";
    char *argv[] = {arg0, arg1, arg2, nullptr};
    int argc = sizeof(argv) / sizeof(char*) - 1;

    app = new QApplication(argc,argv);
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
    delete gui;
    delete app;
}

void UnitTest::test_case1()
{
    QBENCHMARK {
                QVERIFY(1 == 1);
            }
}

QTEST_APPLESS_MAIN(UnitTest)

#include "tst_unittest.moc"
