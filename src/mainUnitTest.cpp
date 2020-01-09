#include <QtTest> 
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
    PaintingArea* area;
    IntelliPhotoGui* gui;
    QImage* image;

public:
    UnitTest();
    ~UnitTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();



};

UnitTest::UnitTest()
{

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

void UnitTest::test_case1()
{
    QBENCHMARK {
                QVERIFY(1 == 1);
            }
}

QTEST_APPLESS_MAIN(UnitTest)

#include "tst_unittest.moc"
