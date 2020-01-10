#ifndef INTELLIINPUTDIALOG_H
#define INTELLIINPUTDIALOG_H

#include <QtWidgets>

#include "IntelliPhotoGui.h"

class IntelliInputDialog
{
public:
    IntelliInputDialog();

    void Input();

private slots:
    void slotCloseEvent();

private:
    IntelliPhotoGui* DummyGui;
    const QSize Buttonsize = QSize(35,35);
    QPalette Palette;
    void setValuesOfPalette();
};

#endif // INTELLIINPUTDIALOG_H
