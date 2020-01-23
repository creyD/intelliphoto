QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TEMPLATE = app

SOURCES +=  tst_unittest.cpp \
    GUI/IntelliInputDialog.cpp \
    GUI/IntelliPhotoGui.cpp \
    Image/IntelliImage.cpp \
    Image/IntelliRasterImage.cpp \
    Image/IntelliShapedImage.cpp \
    IntelliHelper/IntelliColorPicker.cpp \
    IntelliHelper/IntelliDatamanager.cpp \
    IntelliHelper/IntelliRenderSettings.cpp \
    IntelliHelper/IntelliToolsettings.cpp \
    IntelliHelper/IntelliTriangulation.cpp \
    Layer/PaintingArea.cpp \
    Tool/IntelliTool.cpp \
    Tool/IntelliToolCircle.cpp \
    Tool/IntelliToolFloodFill.cpp \
    Tool/IntelliToolLine.cpp \
    Tool/IntelliToolPen.cpp \
    Tool/IntelliToolPlain.cpp \
    Tool/IntelliToolPolygon.cpp \
    Tool/IntelliToolRectangle.cpp

DISTFILES += \
    icons/Wechselpfeile.png \
    icons/circle-tool.svg \
    icons/eraser-tool.svg \
    icons/flood-fill-tool.svg \
    icons/icon.png \
    icons/line-tool.svg \
    icons/pen-tool.svg \
    icons/plain-tool.svg \
    icons/polygon-tool.svg \
    icons/rectangle-tool.svg

HEADERS += \
    GUI/IntelliInputDialog.h \
    GUI/IntelliPhotoGui.h \
    Image/IntelliImage.h \
    Image/IntelliRasterImage.h \
    Image/IntelliShapedImage.h \
    IntelliHelper/IntelliColorPicker.h \
    IntelliHelper/IntelliDatamanager.h \
    IntelliHelper/IntelliRenderSettings.h \
    IntelliHelper/IntelliToolsettings.h \
    IntelliHelper/IntelliTriangulation.h \
    Layer/PaintingArea.h \
    Tool/IntelliTool.h \
    Tool/IntelliToolCircle.h \
    Tool/IntelliToolFloodFill.h \
    Tool/IntelliToolLine.h \
    Tool/IntelliToolPen.h \
    Tool/IntelliToolPlain.h \
    Tool/IntelliToolPolygon.h \
    Tool/IntelliToolRectangle.h
