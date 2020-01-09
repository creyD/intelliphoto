#include <QtTest>

// add necessary includes here

class UnitTest : public QObject
{
    Q_OBJECT

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
