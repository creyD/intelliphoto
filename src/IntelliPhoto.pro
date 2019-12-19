QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GUI/IntelliPhotoGui.cpp \
    Image/IntelliImage.cpp \
    Image/IntelliRasterImage.cpp \
    Image/IntelliShapedImage.cpp \
    IntelliHelper/IntelliColorPicker.cpp \
    IntelliHelper/IntelliHelper.cpp \
    Layer/PaintingArea.cpp \
    Tool/IntelliTool.cpp \
    Tool/IntelliToolCircle.cpp \
    Tool/IntelliToolLine.cpp \
    Tool/IntelliToolPen.cpp \
    Tool/IntelliToolPlain.cpp \
    Tool/IntelliToolPolygon.cpp \
    Tool/IntelliToolRectangle.cpp \
    main.cpp

HEADERS += \
    GUI/IntelliPhotoGui.h \
    Image/IntelliImage.h \
    Image/IntelliRasterImage.h \
    Image/IntelliShapedImage.h \
    IntelliHelper/IntelliColorPicker.h \
    IntelliHelper/IntelliHelper.h \
    Layer/PaintingArea.h \
    Tool/IntelliTool.h \
    Tool/IntelliToolCircle.h \
    Tool/IntelliToolLine.h \
    Tool/IntelliToolPen.h \
    Tool/IntelliToolPlain.h \
    Tool/IntelliToolPolygon.h \
    Tool/IntelliToolRectangle.h

FORMS += \
    mainwindow.ui

QMAKE_CXXFLAGS
QMAKE_LFLAGS

RC_ICONS = icon.ico
ICON = icon.icns

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
